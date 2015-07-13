// TickGroup.cpp
// Chris Bowers

/**
 *	This implements a tickgroup - see TickGroup.h
 */
 
#include "TickGroup.h"

void TickGroup::tick(float dt) { for (auto tickable : *this) tickable->tick(dt); }
