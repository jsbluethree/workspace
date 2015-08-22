// SceneNode.h
// Chris Bowers

/**
 *	Defines a template class that wraps around any sf class and supplies ISceneNode functionality
 */

#ifndef __SCENENODE_H__
#define __SCENENODE_H__

#include "ISceneNode.h"

template<class T>
struct SceneNode : public T, ISceneNode{
	void move(float offsetX, float offsetY) { T::move(offsetX, offsetY); }
	void move(const sf::Vector2f& offset) { T::move(offset); }
	sf::FloatRect get_rect() const { return T::getGlobalBounds(); }
	float get_depth() const { return 0.0f; }
};

#endif
