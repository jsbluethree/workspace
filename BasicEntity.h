// BasicEntity.h
// Chris Bowers

/**
 *	This defines a basic game entity. This basic entity inherits from sf::Sprite and ISceneNode.
 *	This allows the Sprite to be used in an ISceneGraph - see ISceneGraph.h
 */
 
#ifndef __BASICENTITY_H__
#define __BASICENTITY_H__

#include "SFML.h"
#include "ISceneNode.h"

struct BasicEntity : Sprite, ISceneNode{
	void move(float offsetX, float offsetY);
	void move(const Vector2f& offset);
	const FloatRect& get_rect() const;
};

#endif // __BASICENTITY_H__
