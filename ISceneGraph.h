// ISceneGraph.h
// Chris Bowers

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
	virtual void update_node(ISceneNode* node, const Vector2f& d) = 0;
	
	virtual bool check_collision(float x, float y) = 0;
	virtual bool check_collision(const Vector2f& v) = 0;
	virtual bool check_collision(const FloatRect& r) = 0;
	virtual bool check_collision(ISceneNode* node) = 0;
	
	virtual std::unordered_set<ISceneNode*> get_collision(float x, float y) = 0;
	virtual std::unordered_set<ISceneNode*> get_collision(const Vector2f& v) = 0;
	virtual std::unordered_set<ISceneNode*> get_collision(const FloatRect& r) = 0;
	virtual std::unordered_set<ISceneNode*> get_collision(ISceneNode* node) = 0;
};

#endif // __ISCENEGRAPH_H__
