// Camera.cpp
// Chris Bowers

/**
 *	This is an implementation of a simple camera - see Camera.h
 */

#include "Camera.h"

Camera::Camera(FloatRect source, FloatRect viewport) : view{ source }{
	view.setViewport(viewport);
}

void Camera::set_source(const FloatRect& rect) { view.reset(rect); }

void Camera::set_viewport(const FloatRect& rect) { view.setViewport(rect); }

FloatRect Camera::get_source() const { return{ view.getCenter() - view.getSize() / 2.0f, view.getSize() }; }

FloatRect Camera::get_viewport() const { return view.getViewport(); }

void Camera::move(float dx, float dy) { view.move(dx, dy); }

void Camera::move(const Vector2f& d) { move(d.x, d.y); }

void Camera::render_scene(const ISceneGraph& scene, RenderTarget& target, const RenderStates& states) const{
	target.setView(view);
	for (const auto& node : scene.get_collision(get_source())){
		auto drawable = dynamic_cast<Drawable*>(node);
		if (drawable) target.draw(*drawable, states);
	}
}
