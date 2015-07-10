// TickGroup.cpp

#include "TickGroup.h"

void TickGroup::tick(float dt) { for (auto tickable : *this) tickable->tick(dt); }