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
	
	void add_node(ISceneNode* node);
	void remove_node(ISceneNode* node);
	void update_node(ISceneNode* node, float dx, float dy);
	
	bool check_collision(const FloatRect& r) const;
	
	std::unordered_set<ISceneNode*> get_collision(const FloatRect& r) const;
	
private:
	Quadtree qtree;
};

#endif // __QTSCENEGRAPH_H__
