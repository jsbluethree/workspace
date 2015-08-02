// StateMachine.h
// Chris Bowers

/**
 *	This defines a state machine and state change events.
 *	The state machine keeps track of the current logic state of some object and handles state changes.
 */

#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__

#include "Dispatcher.h"
#include "ICallback.h"
#include "IEvent.h"
#include "ITickable.h"
#include "IState.h"
#include "Tag.h"
#include <unordered_map>
#include <string>

struct StateEvent : IEvent{
	explicit StateEvent(Tag next);

	Tag next_state;
};

struct StateMachine{
	StateMachine();

	void add_state(Tag name, IState& state);
	void remove_state(Tag name);
	void set_state(Tag state);
	IState* get_state(Tag state);
	IState* get_current_state();

private:
	struct OnStateTransition : ICallback{
		explicit OnStateTransition(StateMachine& owner);
		void operator()(const IEvent& event);
		StateMachine& machine;
	} state_transition_listener;

	std::unordered_map<Tag, IState*> state_lookup;
	IState* current_state;
};

#endif // __STATEMACHINE_H__
