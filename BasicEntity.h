// BasicEntity.h
// Chris Bowers

#ifndef __BASICENTITY_H__
#define __BASICENTITY_H__

#include "SFML.h"
#include "ISceneNode.h"

struct BasicEntity : Sprite, ISceneNode{
	void move(float offsetX, float offsetY);
	void move(const Vector2f& offset);
	const FloatRect& get_rect() const;
};

#endif
