// QTSceneGraph.cpp
// Chris Bowers

/**
 *	This implements a quadtree-based scene graph - see QTSceneGraph.h
 */

#include "QTSceneGraph.h"

QTSceneGraph::QTSceneGraph(sf::FloatRect bounds) : qtree{ 0, bounds } {}

void QTSceneGraph::add_node(ISceneNode& node) {
	qtree.insert(node);
	auto dptr = dynamic_cast<sf::Drawable*>(&node);
	if (dptr) drawables[&node] = dptr;
}

void QTSceneGraph::remove_node(ISceneNode& node) {
	qtree.remove(node);
	drawables.erase(&node);
}

void QTSceneGraph::update_node(ISceneNode& node, float dx, float dy){
	qtree.remove(node);
	node.move(dx, dy);
	qtree.insert(node);
}

const sf::Drawable* QTSceneGraph::get_drawable(const ISceneNode* node) const {
	if (drawables.count(node))
		return drawables.at(node);
	else
		return nullptr;
}

bool QTSceneGraph::check_collision(const sf::FloatRect& r) const{
	auto possible = qtree.retrieve(r);
	for (const auto& node : possible){
		if (node->get_rect().intersects(r)){
			return true;
		}
	}
	return false;
}

bool QTSceneGraph::check_collision(float x, float y) const{
	auto possible = qtree.retrieve(x, y);
	for (const auto& node : possible){
		if (node->get_rect().contains(x, y)){
			return true;
		}
	}
	return false;
}

std::unordered_set<ISceneNode*> QTSceneGraph::get_collision(const sf::FloatRect& r) const{
	auto possible = qtree.retrieve(r);
	decltype(possible) confirmed;
	for (const auto& node : possible) {
		if (node->get_rect().intersects(r)){
			confirmed.insert(node);
		}
	}
	return confirmed;
}

std::unordered_set<ISceneNode*> QTSceneGraph::get_collision(float x, float y) const{
	auto possible = qtree.retrieve(x, y);
	decltype(possible) confirmed;
	for (const auto& node : possible) {
		if (node->get_rect().contains(x, y)){
			confirmed.insert(node);
		}
	}
	return confirmed;
}

std::set<ISceneNode*, std::function<bool(ISceneNode*, ISceneNode*)>> QTSceneGraph::get_coll_by_depth(const sf::FloatRect& r) const{
	std::function<bool(ISceneNode*, ISceneNode*)> depth_sort = [](ISceneNode* a, ISceneNode* b){
		if (!a) return false;
		else if (!b) return true;
		else return a->get_depth() < b->get_depth(); };
	auto possible = qtree.retrieve(r);
	std::set<ISceneNode*, std::function<bool(ISceneNode*, ISceneNode*)>> confirmed(depth_sort);
	for (const auto& node : possible) {
		if (node->get_rect().intersects(r)){
			// TODO: use hints here to get amortized constant insertion time rather than logarithmic
			confirmed.insert(node);
		}
	}
	return confirmed;
}
