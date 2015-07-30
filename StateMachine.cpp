// StateMachine.cpp
// Chris Bowers

/**
 *	This implements a state machine - see StateMachine.h
 */

#include "StateMachine.h"

StateEvent::StateEvent(Tag next) : next_state{ next } {}

EventType StateEvent::type() { return EventType::STATE; }

StateMachine::StateMachine() : state_transition_listener{ *this } {}

StateMachine::OnStateTransition::OnStateTransition(StateMachine& owner) : machine{ owner } {}

void StateMachine::OnStateTransition::operator()(IEvent* event){
	machine.current_state->exit();
	machine.current_state->events().remove_listener(EventType::STATE, *this);
	machine.current_state = machine.state_lookup[static_cast<StateEvent*>(event)->next_state];
	machine.current_state->events().add_listener(EventType::STATE, *this);
	machine.current_state->enter();
}
