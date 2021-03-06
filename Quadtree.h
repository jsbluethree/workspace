// Quadtree.h
// Chris Bowers

/**
 *	This defines a quadtree of scene nodes.
 *	The quadtree recursively segments a rectangular area into quadrants and stores nodes in those quadrants.
 *	This allows for efficient retrieval of nodes by position.
 */

#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\Rect.hpp"
#include "ISceneNode.h"
#include "Log.h"
#include <unordered_set>

struct Quadtree{
	Quadtree(unsigned int node_level, sf::FloatRect node_bounds);
	Quadtree(const Quadtree& other);
	Quadtree& operator=(const Quadtree& other);
	Quadtree(Quadtree&& other);
	Quadtree& operator=(Quadtree&& other);
	virtual ~Quadtree();
	
	void clear();
	void insert(ISceneNode& node);
	void remove(ISceneNode& node);
	std::unordered_set<ISceneNode*> retrieve(float x, float y) const;
	std::unordered_set<ISceneNode*> retrieve(const sf::Vector2f& vec) const;
	std::unordered_set<ISceneNode*> retrieve(const sf::FloatRect& rect) const;
	std::unordered_set<ISceneNode*> retrieve(const ISceneNode& node) const;
	
private:
	void split();
	
	int get_index(float x, float y) const;
	int get_index(const sf::Vector2f& vec) const;
	int get_index(const sf::FloatRect& rect) const;
	int get_index(const ISceneNode& node) const;
	
	unsigned int level;
	std::unordered_set<ISceneNode*> nodes;
	sf::FloatRect bounds;
	Quadtree* subtrees[4];
	
	static unsigned int MAX_NODES;
	static unsigned int MAX_LEVELS;
};

#endif // __QUADTREE_H__
