// Drawer.h
// Chris Bowers

/**
 *	This defines a simple drawer. It keeps a list of drawables and draws them on tick.
 *	Camera + ISceneGraph can probably replace this entirely.
 */

#ifndef __DRAWER_H__
#define __DRAWER_H__

#include "ITickable.h"
#include "SFML.h"
#include <vector>

struct Drawer : ITickable{
	Drawer();
	explicit Drawer(RenderTarget& render_target);

	void add_drawable(Drawable& drawable);
	void remove_drawable(Drawable& drawable);
	void tick(float);

	RenderTarget* target;

private:
	std::vector<Drawable*> drawables;
	std::vector<Drawable*> defer_add;
	std::vector<Drawable*> defer_remove;
};

#endif // __DRAWER_H__
