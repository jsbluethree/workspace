// StateMachine.h

#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__

#include "ICallback.h"
#include "IEvent.h"
#include "ITickable.h"
#include "IState.h"
#include "PoolAllocator.h"
#include "Tag.h"
#include "typedefs.h"
#include <unordered_map>
#include <string>

struct StateEvent : IEvent{
	Tag next_state;

	StateEvent(Tag next);
	EventType type();
	void* operator new(size_t n);
	void operator delete(void* p);
	void operator delete(void* p, size_t n);
};

struct StateMachine{
	IState* current_state;
	std::unordered_map<Tag, IState*> state_lookup;

	struct OnStateTransition : ICallback{
		StateMachine* machine;
		OnStateTransition(StateMachine* owner);
		void execute(IEvent* event);
	} state_transition_listener;

	StateMachine();
};

#endif