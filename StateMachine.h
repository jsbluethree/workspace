// StateMachine.h
// Chris Bowers

/**
 *	This defines a state machine and state change events.
 *	The state machine keeps track of the current logic state of some object and handles state changes.
 *	The new and delete operators of StateEvent are overloaded to use pool allocation.
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

	EventType type();

	Tag next_state;
};

struct StateMachine{
	StateMachine();

	IState* current_state;
	std::unordered_map<Tag, IState*> state_lookup;

	struct OnStateTransition : ICallback{
		OnStateTransition(StateMachine& owner);
		void execute(IEvent* event);
		StateMachine& machine;
	} state_transition_listener;
};

#endif // __STATEMACHINE_H__
