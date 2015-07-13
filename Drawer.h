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
	std::vector<Drawable*> drawables;
	std::vector<Drawable*> defer_add;
	std::vector<Drawable*> defer_remove;
	RenderTarget* target;

	Drawer();
	Drawer(RenderTarget* render_target);
	~Drawer();

	void add_drawable(Drawable* drawable);
	void remove_drawable(Drawable* drawable);
	void tick(float);

private:
	Drawer(const Drawer&);
	Drawer(Drawer&&);
	Drawer& operator=(const Drawer&);
	Drawer& operator=(Drawer&&);
};

#endif // __DRAWER_H__
