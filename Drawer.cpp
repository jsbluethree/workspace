// Drawer.cpp
// Chris Bowers

/**
 *	This implements a simple drawer - see Drawer.h
 */

#include "Drawer.h"

Drawer::Drawer() : target{ nullptr } {}

Drawer::Drawer(RenderTarget& render_target) : target{ &render_target } {}

Drawer::~Drawer() {}

void Drawer::add_drawable(Drawable& drawable) { defer_add.push_back(&drawable); }

void Drawer::remove_drawable(Drawable& drawable) { defer_remove.push_back(&drawable); }

void Drawer::tick(float){
	for (auto drawable : drawables) target->draw(*drawable);

	for (auto drawable : defer_add) drawables.push_back(drawable);
	defer_add.clear();

	for (auto drawable : defer_remove){
		for (auto it = drawables.begin(); it != drawables.end(); ++it){
			if (*it == drawable){
				drawables.erase(it);
				break;
			}
		}
	}
	defer_remove.clear();
}
