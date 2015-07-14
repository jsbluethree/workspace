// ISceneNode.h
// Chris Bowers

/**
 *	This defines the interface for a scene node. A scene node is generally defined by a rectangle.
 *	May be expanded in the future if necessary.
 */

#ifndef __ISCENENODE_H__
#define __ISCENENODE_H__

struct Vector2f;
struct FloatRect;

struct ISceneNode{
	virtual void move(float offsetX, float offsetY) = 0;
	virtual void move(const Vector2f& offset) = 0;
	virtual const FloatRect& get_rect() const = 0;
	
	virtual ~ISceneNode() {}
};

#endif // __ISCENENODE_H__
