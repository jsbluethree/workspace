// BasicEntity.cpp
// Chris Bowers

/**
 *	This is an implementation of a basic game entity - see BasicEntity.h
 */
 
#include "BasicEntity.h"

void BasicEntity::move(float offsetX, float offsetY) { Sprite::move(offsetX, offsetY); }

void BasicEntity::move(const Vector2f& offset) { Sprite::move(offset); }

FloatRect BasicEntity::get_rect() const { return getGlobalBounds(); }
