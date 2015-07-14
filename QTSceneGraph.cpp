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

bool QTSceneGraph::check_collision(const FloatRect&r) {
	auto possible = qtree.retrieve(r);
	for (const auto& node : possible){
		if (node->get_rect.intersects(r)){
			return true;
		}
	}
	
	return false;
}

std::unordered_set<ISceneNode*> QTSceneGraph::get_collision(const FloatRect& r){
	auto possible = qtree.retrieve(r);
	decltype(possible) confirmed;
	
	for (const auto& node : possible) {
		if (node->get_rect().intersects(r)){
			confirmed.insert(node);
		}
	}
	
	return confirmed;
}
