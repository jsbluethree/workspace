// QTSceneGraph.h
// Chris Bowers

/**
 *	This defines a quadtree based scenegraph - see Quadtree.h and ISceneGraph.h
 */

#ifndef __QTSCENEGRAPH_H__
#define __QTSCENEGRAPH_H__

#include "SFML.h"
#include "ISceneGraph.h"
#include "ISceneNode.h"
#include "Quadtree.h"

struct QTSceneGraph : ISceneGraph{
	explicit QTSceneGraph(FloatRect bounds);
	
	void add_node(ISceneNode& node);
	void remove_node(ISceneNode& node);
	void update_node(ISceneNode& node, float dx = 0.0f, float dy = 0.0f);
	
	bool check_collision(const FloatRect& r) const;
	bool check_collision(float x, float y) const;
	bool check_collision(const Vector2f& v) const { return check_collision(v.x, v.y); }
	bool check_collision(const ISceneNode& node) const { return check_collision(node.get_rect()); }
	
	std::unordered_set<ISceneNode*> get_collision(const FloatRect& r) const;
	std::unordered_set<ISceneNode*> get_collision(float x, float y) const;
	std::unordered_set<ISceneNode*> get_collision(const Vector2f& v) const { return get_collision(v.x, v.y); }
	std::unordered_set<ISceneNode*> get_collision(const ISceneNode& node) const { return get_collision(node.get_rect()); }
	
private:
	Quadtree qtree;
};

#endif // __QTSCENEGRAPH_H__
