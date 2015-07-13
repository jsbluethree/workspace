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
	std::vector<ITickable*> tickables;
	std::vector<ITickable*> defer_add;
	std::vector<ITickable*> defer_remove;

	Ticker();
	~Ticker();

	void add_tickable(ITickable* tickable);
	void remove_tickable(ITickable* tickable);
	void tick(float dt);

private:
	Ticker(const Ticker&);
	Ticker(Ticker&&);
	Ticker& operator=(const Ticker&);
	Ticker& operator=(Ticker&&);
};

#endif // __TICKER_H__
