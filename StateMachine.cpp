// StateMachine.cpp

#include "StateMachine.h"

StateEvent::StateEvent(Tag next) : next_state{ next } {}

EventType StateEvent::type() { return EventType::STATE; }

void* StateEvent::operator new(size_t n) { return PoolAllocator<StateEvent>().allocate(n / sizeof(StateEvent)); }

void StateEvent::operator delete(void* p) { operator delete(p, sizeof(StateEvent)); }

void StateEvent::operator delete(void* p, size_t n) { PoolAllocator<StateEvent>().deallocate((StateEvent*)p, n / sizeof(StateEvent)); }

StateMachine::StateMachine() : state_transition_listener{ this } {}

StateMachine::OnStateTransition::OnStateTransition(StateMachine* owner) : machine{ owner } {}

void StateMachine::OnStateTransition::execute(IEvent* event){
	machine->current_state->exit();
	machine->current_state->events.remove_listener(EventType::STATE, this);
	machine->current_state = machine->state_lookup[static_cast<StateEvent*>(event)->next_state];
	machine->current_state->events.add_listener(EventType::STATE, this);
	machine->current_state->enter();
}