// BasicEntity.cpp
// Chris Bowers

#include "BasicEntity.h"

void BasicEntity::move(float offsetX, float offsetY) { Sprite::move(offsetX, offsetY); }

void BasicEntity::move(const Vector2f& offset) { Sprite::move(offset); }

const FloatRect& BasicEntity::get_rect() const { return m_sprite.getGlobalBounds(); }
