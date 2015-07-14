// Quadtree.cpp
// Chris Bowers

/**
 *	This implements a quadtree of scene nodes - see Quadtree.h
 */

#include "Quadtree.h"

Quadtree::Quadtree(unsigned int node_level, FloatRect node_bounds) : level{ node_level }, bounds{ node_bounds } {
	for (auto& p : subtrees) p = nullptr;
}

Quadtree::~Quadtree() { clear(); }

void Quadtree::clear(){
	nodes.clear();
	for (auto& p : subtrees){
		delete p;
		p = nullptr;
	}
}

void Quadtree::insert(ISceneNode* node){
	if (subtrees[0] != nullptr) {
		auto index = get_index(node);
		if (index != -1){
			subtrees[index]->insert(node);
			return;
		}
	}
	
	nodes.insert(node);
	
	if (nodes.size() > MAX_NODES && level < MAX_LEVELS){
		if (subtrees[0] == nullptr) split();
		decltype(nodes) temp;
		temp.swap(nodes);
		for (const auto& node : temp){
			insert(node);
		}
	}
}

void Quadtree::remove(ISceneNode* node){
	if (subtrees[0] != nullptr) {
		auto index = get_index(node);
		if (index != -1){
			subtrees[index]->remove(node);
			return;
		}
	}
	
	nodes.erase(node);
}

std::unordered_set<ISceneNode*> Quadtree::retrieve(float x, float y) { return retrieve(FloatRect(x, y, 0, 0)); }

std::unordered_set<ISceneNode*> Quadtree::retrieve(const Vector2f& vec) { return retrieve(vec.x, vec.y); }

std::unordered_set<ISceneNode*> Quadtree::retrieve(const FloatRect& rect){
	std::unordered_set<ISceneNode*> return_list;
	_retrieve(return_list, rect);
	return return_list;
}

std::unordered_set<ISceneNode*> Quadtree::retrieve(ISceneNode* node) { return retrieve(node->get_rect()); }

void Quadtree::_retrieve(std::unordered_set<ISceneNode*>& return_list, const FloatRect& rect){
	auto index = get_index(rect);
	if (index != -1 && subtrees[0] != nullptr){
		subtrees[index]->_retrieve(return_list, rect);
	}
	
	return_list.insert(nodes.begin(), nodes.end());
}

void Quadtree::split(){
	float sub_width = bounds.width / 2;
	float sub_height = bounds.height / 2;
	
	subtrees[0] = new Quadtree(level + 1, FloatRect(bounds.left + sub_width, bounds.top, sub_width, sub_height));
	subtrees[1] = new Quadtree(level + 1, FloatRect(bounds.left, bounds.top, sub_width, sub_height));
	subtrees[2] = new Quadtree(level + 1, FloatRect(bounds.left, bounds.top + sub_height, sub_width, sub_height));
	subtrees[3] = new Quadtree(level + 1, FloatRect(bounds.left + sub_width, bounds.top + sub_height, sub_width, sub_height));
}

int Quadtree::get_index(float x, float y) { return get_index(FloatRect(x, y, 0, 0)); }

int Quadtree::get_index(const Vector2f& vec) { return get_index(vec.x, vec.y); }

int Quadtree::get_index(const FloatRect& rect){
	int index = -1;
	float vert_mid = bounds.left + bounds.width / 2;
	float hori_mid = bounds.top + bounds.height / 2;
	
	bool in_top = rect.top < hori_mid && rect.top + rect.height < hori_mid;
	bool in_bot = rect.top > hori_mid;
	
	if (rect.left < vert_mid && rect.left + rect.width < vert_mid){
		if (in_top) index = 1;
		else if (in_bot) index = 2;
	}
	else if (rect.left > vert_mid){
		if (in_top) index = 0;
		else if (in_bot) index = 3;
	}
	
	return index;	
}

int Quadtree::get_index(ISceneNode* node) { return get_index(node->get_rect()); }

unsigned int Quadtree::MAX_NODES = 10;

unsigned int Quadtree::MAX_LEVELS = 10;
