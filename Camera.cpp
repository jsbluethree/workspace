// Camera.cpp
// Chris Bowers

/**
 *	This is an implementation of a simple camera - see Camera.h
 */

#include "Camera.h"

Camera::Camera(sf::FloatRect source, sf::FloatRect viewport) : view{ source } { view.setViewport(viewport); }

void Camera::set_source(const sf::FloatRect& rect) { view.reset(rect); }

void Camera::set_viewport(const sf::FloatRect& rect) { view.setViewport(rect); }

sf::FloatRect Camera::get_source() const { return{ view.getCenter() - view.getSize() / 2.0f, view.getSize() }; }

sf::FloatRect Camera::get_viewport() const { return view.getViewport(); }

void Camera::move(float dx, float dy) { view.move(dx, dy); }

void Camera::move(const sf::Vector2f& d) { move(d.x, d.y); }

void Camera::render_scene(const ISceneGraph& scene, sf::RenderTarget& target, const sf::RenderStates& states) const{
	target.setView(view);
	for (const auto& node : scene.get_collision(get_source())){
		auto drawable = scene.get_drawable(node);
		if (drawable) target.draw(*drawable, states);
	}
}

void Camera::render_scene_depth(const ISceneGraph& scene, sf::RenderTarget& target, const sf::RenderStates& states) const{
	target.setView(view);
	for (const auto& node : scene.get_coll_by_depth(get_source())){
		auto drawable = scene.get_drawable(node);
		if (drawable) target.draw(*drawable, states);
	}
}
