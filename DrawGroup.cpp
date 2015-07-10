// DrawGroup.cpp

#include "DrawGroup.h"

void DrawGroup::draw(RenderTarget& target, RenderStates states) const { for (auto drawable : *this) target.draw(*drawable, states); }