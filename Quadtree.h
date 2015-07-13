// Quadtree.h
// Chris Bowers

#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include "SceneNode.h"
#include "SFML.h"
#include "typedefs.h"
#include <list>

struct Quadtree{
	Quadtree(u32 node_level, FloatRect node_bounds);
	~Quadtree();
	
	void clear();
	void insert(ISceneNode* node);
	void remove(ISceneNode* node);
	std::list<ISceneNode*> retrieve(float x, float y);
	std::list<ISceneNode*> retrieve(const Vector2f& vec);
	std::list<ISceneNode*> retrieve(const FloatRect& rect);
	std::list<ISceneNode*> retrieve(ISceneNode* node);
	
private:
	void split();
	
	i8 get_index(float x, float y);
	i8 get_index(const Vector2f& vec);
	i8 get_index(const FloatRect& rect);
	i8 get_index(ISceneNode* node);
	
	void _retrieve(std::list<ISceneNode*>& return_list, const FloatRect& rect);
	
	u32 level;
	std::list<ISceneNode*> nodes;
	FloatRect bounds;
	Quadtree* subtrees[4];
	
	static u32 MAX_NODES;
	static u32 MAX_LEVELS;
};

#endif // __QUADTREE_H__
