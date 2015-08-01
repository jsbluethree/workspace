// Camera.h
// Chris Bowers

/**
 *	This defines a simple camera. It renders all drawables from the given scene that are located within it's own rect.
 */

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "SFML\Graphics\Drawable.hpp"
#include "SFML\Graphics\RenderTarget.hpp"
#include "ISceneGraph.h"

struct Camera{
	explicit Camera(sf::FloatRect source, sf::FloatRect viewport = { 0.0f, 0.0f, 1.0f, 1.0f });
	virtual ~Camera() = default;
	
	void set_source(const sf::FloatRect& rect);
	void set_viewport(const sf::FloatRect& rect);
	sf::FloatRect get_source() const;
	sf::FloatRect get_viewport() const;
	void move(float dx, float dy);
	void move(const sf::Vector2f& d);
	void render_scene(const ISceneGraph& scene, sf::RenderTarget& target, const sf::RenderStates& states = sf::RenderStates::Default) const;
	void render_scene_depth(const ISceneGraph& scene, sf::RenderTarget& target, const sf::RenderStates& states = sf::RenderStates::Default) const;

private:
	sf::View view;
};

#endif // __CAMERA_H__
