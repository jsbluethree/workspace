// BasicEntity.h
// Chris Bowers

/**
 *	This defines a basic game entity. This basic entity inherits from sf::Sprite and ISceneNode.
 *	This allows the Sprite to be used in an ISceneGraph - see ISceneGraph.h
 */
 
#ifndef __BASICENTITY_H__
#define __BASICENTITY_H__

#include "SFML\Graphics\Sprite.hpp"
#include "ISceneNode.h"

struct BasicEntity : sf::Sprite, ISceneNode{
	void move(float offsetX, float offsetY);
	void move(const sf::Vector2f& offset);
	sf::FloatRect get_rect() const;
	float get_depth() const;
};

#endif // __BASICENTITY_H__
