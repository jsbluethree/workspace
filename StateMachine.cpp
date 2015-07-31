// StateMachine.cpp
// Chris Bowers

/**
 *	This implements a state machine - see StateMachine.h
 */

#include "StateMachine.h"

StateEvent::StateEvent(Tag next) : next_state{ next } {}

StateMachine::StateMachine() : state_transition_listener{ *this } {}

StateMachine::OnStateTransition::OnStateTransition(StateMachine& owner) : machine{ owner } {}

void StateMachine::OnStateTransition::operator()(const IEvent& event){
	machine.current_state->exit();
	machine.current_state->events().remove_listener<StateEvent>(*this);
	machine.current_state = machine.state_lookup[static_cast<const StateEvent&>(event).next_state];
	machine.current_state->events().add_listener<StateEvent>(*this);
	machine.current_state->enter();
}
