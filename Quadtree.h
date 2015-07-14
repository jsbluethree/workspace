// Quadtree.h
// Chris Bowers

/**
 *	This defines a quadtree of scene nodes.
 *	The quadtree recursively segments a rectangular area into quadrants and stores nodes in those quadrants.
 *	This allows for efficient retrieval of nodes by position.
 */

#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include "ISceneNode.h"
#include "SFML.h"
#include <unordered_set>

struct Quadtree{
	Quadtree(unsigned int node_level, FloatRect node_bounds);
	~Quadtree();
	
	void clear();
	void insert(ISceneNode* node);
	void remove(ISceneNode* node);
	std::unordered_set<ISceneNode*> retrieve(float x, float y);
	std::unordered_set<ISceneNode*> retrieve(const Vector2f& vec);
	std::unordered_set<ISceneNode*> retrieve(const FloatRect& rect);
	std::unordered_set<ISceneNode*> retrieve(ISceneNode* node);
	
private:
	void _retrieve(std::unordered_set<ISceneNode*>& return_list, const FloatRect& rect);
	void split();
	
	int get_index(float x, float y);
	int get_index(const Vector2f& vec);
	int get_index(const FloatRect& rect);
	int get_index(ISceneNode* node);	
	
	unsigned int level;
	std::unordered_set<ISceneNode*> nodes;
	FloatRect bounds;
	Quadtree* subtrees[4];
	
	static unsigned int MAX_NODES;
	static unsigned int MAX_LEVELS;
};

#endif // __QUADTREE_H__
