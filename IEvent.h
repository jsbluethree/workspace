// IEvent.h
// Chris Bowers

/**
 *	This defines the base class for all events to be used with the event dispatcher - see Dispatcher.h
 *	TODO: Pool allocation
 */

#ifndef __IEVENT_H__
#define __IEVENT_H__

#ifdef EVENT_POOL_ALLOCATION
#include "PoolAllocator.h"
#endif // EVENT_POOL_ALLOCATION

struct IEvent{
	virtual ~IEvent() = default;

#ifdef EVENT_POOL_ALLOCATION

	void* operator new(size_t){ PoolAllocator<IEvent>().allocate(1); }
	void* operator new[](size_t n) { PoolAllocator<IEvent>().allocate(n / sizeof(IEvent)); }
	void operator delete(void* p){ PoolAllocator<IEvent>().deallocate((IEvent*)p, 1); }
	void operator delete[](void* p, size_t n){ PoolAllocator<IEvent>().deallocate((IEvent*)p, n / sizeof(IEvent)); }

#endif // EVENT_POOL_ALLOCATION
};

#endif // __IEVENT_H__
