// QTSceneGraph.cpp
// Chris Bowers

/**
 *	This implements a quadtree-based scene graph - see QTSceneGraph.h
 */

#include "QTSceneGraph.h"

QTSceneGraph::QTSceneGraph(FloatRect bounds) : qtree{ 0, bounds } {}

void QTSceneGraph::add_node(ISceneNode* node) { qtree.insert(node); }

void QTSceneGraph::remove_node(ISceneNode* node) { qtree.remove(node); }

void QTSceneGraph::update_node(ISceneNode* node, float dx, float dy){
	qtree.remove(node);
	node->move(dx, dy);
	qtree.insert(node);
}

void QTSceneGraph::update_node(ISceneNode* node, const Vector2f& d) { update_node(node, d.x, d.y); }

bool QTSceneGraph::check_collision(float x, float y) { return !get_collision(x, y).empty(); }

bool QTSceneGraph::check_collision(const Vector2f& v) { return check_collision(v.x, v.y); }

bool QTSceneGraph::check_collision(const FloatRect&r) { return !get_collision(r).empty(); }

bool QTSceneGraph::check_collision(ISceneNode* node) { return check_collision(node->get_rect()); }

std::unordered_set<ISceneNode*> get_collision(float x, float y){
	auto possible = qtree.retrieve(x, y);
	decltype(possible) confirmed;
	
	for (const auto& node : possible){
		if (node->get_rect().contains(x, y)){
			confirmed.insert(node);
		}
	}
	
	return confirmed;
}

std::unordered_set<ISceneNode*> get_collision(const Vector2f& v) { return get_collision(v.x, v.y); }

std::unordered_set<ISceneNode*> get_collision(const FloatRect& r){
	auto possible = qtree.retrieve(r);
	decltype(possible) confirmed;
	
	for (const auto& node : possible) {
		if (node->get_rect().intersects(r)){
			confirmed.insert(node);
		}
	}
	
	return confirmed;
}

std::unordered_set<ISceneNode*> get_collision(ISceneNode* node) { return get_collision(node->get_rect()); }
