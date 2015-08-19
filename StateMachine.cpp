// StateMachine.cpp
// Chris Bowers

/**
 *	This implements a state machine - see StateMachine.h
 */

#include "StateMachine.h"

StateEvent::StateEvent(Tag next) : next_state{ next } {}

StateMachine::StateMachine() : state_transition_listener{ *this }, current_state{ nullptr } {}

void StateMachine::add_state(Tag name, IState& state) { state_lookup[name] = &state; }

void StateMachine::add_null_state(Tag name) { state_lookup[name] = nullptr; }

void StateMachine::remove_state(Tag name) { state_lookup.erase(name); }

void StateMachine::set_state(Tag state){
	if (current_state){
		current_state->exit();
		current_state->events().remove_listener<StateEvent>(state_transition_listener);
	}
	current_state = state_lookup[state];
	current_state->events().add_listener<StateEvent>(state_transition_listener);
	current_state->enter();
}

IState* StateMachine::get_state(Tag state){
	if (state_lookup.count(state))
		return state_lookup[state];
	else
		return nullptr;
}

IState* StateMachine::get_current_state() { return current_state; }

StateMachine::OnStateTransition::OnStateTransition(StateMachine& owner) : machine{ owner } {}

void StateMachine::OnStateTransition::operator()(const IEvent& event){
	machine.set_state(static_cast<const StateEvent&>(event).next_state);
}
