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

#include "typedefs.h"
#include "SFML.h"
#include "ISceneNode.h"
#include <unordered_set>

struct ISceneGraph{
	virtual void add_node(ISceneNode* node) = 0;
	virtual void remove_node(ISceneNode* node) = 0;
	virtual void update_node(ISceneNode* node, float dx, float dy) = 0;
	virtual void update_node(ISceneNode* node, const Vector2f& d);

	virtual bool check_collision(const FloatRect& r) = 0;
	virtual bool check_collision(float x, float y);
	virtual bool check_collision(const Vector2f& v);
	virtual bool check_collision(ISceneNode* node);
	
	virtual std::unordered_set<ISceneNode*> get_collision(const FloatRect& r) = 0;
	virtual std::unordered_set<ISceneNode*> get_collision(float x, float y);
	virtual std::unordered_set<ISceneNode*> get_collision(const Vector2f& v);
	virtual std::unordered_set<ISceneNode*> get_collision(ISceneNode* node);
	
	virtual ~ISceneGraph() {}
};

// SOME DEFAULT IMPLEMENTATION HERE

void ISceneGraph::update_node(ISceneNode* node, const Vector2f& d) { update_node(node, d.x, d.y); }

bool ISceneGraph::check_collision(float x, float y) { return check_collision(FloatRect(x, y, 0, 0)); }

bool ISceneGraph::check_collision(const Vector2f& v) { return check_collision(v.x, v.y); }

bool ISceneGraph::check_collision(ISceneNode* node) { return check_collision(node->get_rect()); }

std::unordered_set<ISceneNode*> ISceneGraph::get_collision(float x, float y) { return get_collision(FloatRect(x, y, 0, 0)); }

std::unordered_set<ISceneNode*> ISceneGraph::get_collision(const Vector2f& v) { return get_collision(v.x, v.y); }

std::unordered_set<ISceneNode*> ISceneGraph::get_collision(ISceneNode* node) { return get_collision(node->get_rect()); }

#endif // __ISCENEGRAPH_H__
