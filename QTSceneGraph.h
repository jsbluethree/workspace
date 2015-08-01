// QTSceneGraph.h
// Chris Bowers

/**
 *	This defines a quadtree based scenegraph - see Quadtree.h and ISceneGraph.h
 *	TODO: Optimize get_coll_by_depth
 */

#ifndef __QTSCENEGRAPH_H__
#define __QTSCENEGRAPH_H__

#include "ISceneGraph.h"
#include "ISceneNode.h"
#include "Quadtree.h"
#include <functional>
#include <set>
#include <unordered_set>
#include <unordered_map>

struct QTSceneGraph : ISceneGraph{
	explicit QTSceneGraph(sf::FloatRect bounds);

	void add_node(ISceneNode& node);
	void remove_node(ISceneNode& node);
	void update_node(ISceneNode& node, float dx = 0.0f, float dy = 0.0f);

	const sf::Drawable* get_drawable(const ISceneNode* node) const;
	
	bool check_collision(const sf::FloatRect& r) const;
	bool check_collision(float x, float y) const;
	bool check_collision(const sf::Vector2f& v) const { return check_collision(v.x, v.y); }
	bool check_collision(const ISceneNode& node) const { return check_collision(node.get_rect()); }
	
	std::unordered_set<ISceneNode*> get_collision(const sf::FloatRect& r) const;
	std::unordered_set<ISceneNode*> get_collision(float x, float y) const;
	std::unordered_set<ISceneNode*> get_collision(const sf::Vector2f& v) const { return get_collision(v.x, v.y); }
	std::unordered_set<ISceneNode*> get_collision(const ISceneNode& node) const { return get_collision(node.get_rect()); }
	
	std::set<ISceneNode*, std::function<bool(ISceneNode*, ISceneNode*)>> get_coll_by_depth(const sf::FloatRect& r) const;
private:
	Quadtree qtree;
	std::unordered_map<const ISceneNode*, sf::Drawable*> drawables;
};

#endif // __QTSCENEGRAPH_H__
