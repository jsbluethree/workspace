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
	QTSceneGraph(FloatRect bounds);
	
	void add_node(ISceneNode& node);
	void remove_node(ISceneNode& node);
	void update_node(ISceneNode& node, float dx, float dy);
	
	bool check_collision(const FloatRect& r) const;
	virtual bool check_collision(float x, float y) const { return check_collision(FloatRect(x, y, 0, 0)); }
	virtual bool check_collision(const Vector2f& v) const { return check_collision(v.x, v.y); }
	virtual bool check_collision(const ISceneNode& node) const { return check_collision(node.get_rect()); }
	
	std::unordered_set<ISceneNode*> get_collision(const FloatRect& r) const;
	virtual std::unordered_set<ISceneNode*> get_collision(float x, float y) const { return get_collision(FloatRect(x, y, 0, 0)); }
	virtual std::unordered_set<ISceneNode*> get_collision(const Vector2f& v) const { return get_collision(v.x, v.y); }
	virtual std::unordered_set<ISceneNode*> get_collision(const ISceneNode& node) const { return get_collision(node.get_rect()); }
	
private:
	Quadtree qtree;
};

#endif // __QTSCENEGRAPH_H__
