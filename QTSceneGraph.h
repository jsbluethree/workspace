// QTSceneGraph.h
// Chris Bowers

/**
 *	This defines a quadtree based scenegraph - see Quadtree.h and ISceneGraph.h
 *
 *	TODO: Rewrite check_collision to short circuit on finding a collision rather than checking the whole set
 *	TODO: Rewrite check_ and get_collision to have a single base case on a rect, and all other overloads refer to that algorithm
 */

#ifndef __QTSCENEGRAPH_H__
#define __QTSCENEGRAPH_H__

#include "ISceneGraph.h"
#include "Quadtree.h"

struct QTSceneGraph : ISceneGraph{
	QTSceneGraph(FloatRect bounds);
	
	void add_node(ISceneNode* node);
	void remove_node(ISceneNode* node);
	void update_node(ISceneNode* node, float dx, float dy);
	void update_node(ISceneNode* node, const Vector2f& d);
	
	bool check_collision(float x, float y);
	bool check_collision(const Vector2f& v);
	bool check_collision(const FloatRect& r);
	bool check_collision(ISceneNode* node);
	
	std::unordered_set<ISceneNode*> get_collision(float x, float y);
	std::unordered_set<ISceneNode*> get_collision(const Vector2f& v);
	std::unordered_set<ISceneNode*> get_collision(const FloatRect& r);
	std::unordered_set<ISceneNode*> get_collision(ISceneNode* node);
	
private:
	Quadtree qtree;
};

#endif // __QTSCENEGRAPH_H__
