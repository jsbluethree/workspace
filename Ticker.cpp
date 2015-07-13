// Ticker.cpp
// Chris Bowers

/**
 *	This implements a ticker - see Ticker.h
 */

#include "Ticker.h"

Ticker::Ticker() {}

Ticker::~Ticker() {}

void Ticker::add_tickable(ITickable* tickable) { defer_add.push_back(tickable); }

void Ticker::remove_tickable(ITickable* tickable) { defer_remove.push_back(tickable); }

void Ticker::tick(float dt){
	for (auto tickable : tickables) tickable->tick(dt);

	for (auto tickable : defer_add) tickables.push_back(tickable);
	defer_add.clear();

	for (auto tickable : defer_remove){
		for (auto it = tickables.begin(); it != tickables.end(); ++it){
			if (*it == tickable){
				tickables.erase(it);
				break;
			}
		}
	}
	defer_remove.clear();
}

Ticker::Ticker(const Ticker&) {}

Ticker::Ticker(Ticker&&) {}

Ticker& Ticker::operator=(const Ticker&) { return *this; }

Ticker& Ticker::operator=(Ticker&&) { return *this; }
