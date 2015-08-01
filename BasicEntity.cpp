// BasicEntity.cpp
// Chris Bowers

/**
 *	This is an implementation of a basic game entity - see BasicEntity.h
 */
 
#include "BasicEntity.h"

void BasicEntity::move(float offsetX, float offsetY) { Sprite::move(offsetX, offsetY); }

void BasicEntity::move(const sf::Vector2f& offset) { Sprite::move(offset); }

sf::FloatRect BasicEntity::get_rect() const { return getGlobalBounds(); }

float BasicEntity::get_depth() const { return 0.0f; }
