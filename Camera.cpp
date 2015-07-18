// Camera.cpp
// Chris Bowers

/**
 *	This is an implementation of a simple camera - see Camera.h
 */

#include "Camera.h"

Camera::Camera(FloatRect source) : Camera{ source, FloatRect(0.0f, 0.0f, 1.0f, 1.0f) } {}

Camera::Camera(FloatRect source, FloatRect viewport) : source_rect{ source }, viewport_rect{ viewport } {}

void Camera::render_scene(const ISceneGraph& scene, RenderTarget& target, const RenderStates& states) const{
	View view(source_rect);
	view.setViewport(viewport_rect);
	target.setView(view);
	for (const auto& node : scene.get_collision(source_rect)){
		auto drawable = dynamic_cast<Drawable*>(node);
		if (drawable) target.draw(*drawable, states);
	}
}
