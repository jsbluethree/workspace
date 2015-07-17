// Ticker.h
// Chris Bowers

/**
 *	This defines a ticker. It has a list of tickables that are ticked on each tick.... yeah
 */

#ifndef __TICKER_H__
#define __TICKER_H__

#include "ITickable.h"
#include <vector>

struct Ticker : ITickable{
	Ticker() = default;
	~Ticker() = default;

	Ticker(const Ticker&) = delete;
	Ticker(Ticker&&) = delete;
	Ticker& operator=(const Ticker&) = delete;
	Ticker& operator=(Ticker&&) = delete;

	void add_tickable(ITickable& tickable);
	void remove_tickable(ITickable& tickable);
	void tick(float dt);

private:
	std::vector<ITickable*> tickables;
	std::vector<ITickable*> defer_add;
	std::vector<ITickable*> defer_remove;
};

#endif // __TICKER_H__
