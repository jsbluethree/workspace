// ISceneGraph.h
// Chris Bowers

/**
 *	This defines the interface for a scene graph.
 *	A scene graph manages the position of all objects in a given scene for the purposes of collision detection.
 *	It can also be used for rendering - see Camera.h
 *	std::unordered_set is used for efficient iteration, insertion and removal of nodes in the average case.
 */

#ifndef __ISCENEGRAPH_H__
#define __ISCENEGRAPH_H__

#include "SFML.h"
#include "ISceneNode.h"
#include <unordered_set>

struct ISceneGraph{
	virtual ~ISceneGraph() = default;

	virtual void add_node(ISceneNode& node) = 0;
	virtual void remove_node(ISceneNode& node) = 0;
	virtual void update_node(ISceneNode& node, float dx, float dy) = 0;
	virtual void update_node(ISceneNode& node, const Vector2f& d) { update_node(node, d.x, d.y); }

	virtual bool check_collision(const FloatRect& r) const = 0;
	virtual bool check_collision(float x, float y) const = 0;
	virtual bool check_collision(const Vector2f& v) const { return check_collision(v.x, v.y); }
	virtual bool check_collision(const ISceneNode& node) const { return check_collision(node.get_rect()); }
	
	virtual std::unordered_set<ISceneNode*> get_collision(const FloatRect& r) const = 0;
	virtual std::unordered_set<ISceneNode*> get_collision(float x, float y) const = 0;
	virtual std::unordered_set<ISceneNode*> get_collision(const Vector2f& v) const { return get_collision(v.x, v.y); }
	virtual std::unordered_set<ISceneNode*> get_collision(const ISceneNode& node) const { return get_collision(node.get_rect()); }
};

#endif // __ISCENEGRAPH_H__
