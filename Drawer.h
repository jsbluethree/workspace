// Drawer.h
// Chris Bowers

/**
 *	This defines a simple drawer. It keeps a list of drawables and draws them on tick.
 *	Camera + ISceneGraph can probably replace this entirely.
 */

#ifndef __DRAWER_H__
#define __DRAWER_H__

#include "ITickable.h"
#include "SFML\Graphics\Drawable.hpp"
#include "SFML\Graphics\RenderTarget.hpp"
#include <vector>

struct Drawer : ITickable{
	Drawer();
	explicit Drawer(sf::RenderTarget& render_target);

	void add_drawable(sf::Drawable& drawable);
	void remove_drawable(sf::Drawable& drawable);
	void tick(float);

	sf::RenderTarget* target;

private:
	std::vector<sf::Drawable*> drawables;
	std::vector<sf::Drawable*> defer_add;
	std::vector<sf::Drawable*> defer_remove;
};

#endif // __DRAWER_H__
