// Camera.cpp
// Chris Bowers

/**
 *	This is an implementation of a simple camera - see Camera.h
 */

#include "Camera.h"

Camera::Camera(FloatRect init_rect) : cam_rect{ init_rect } {}

void Camera::render_scene(const ISceneGraph& scene, RenderTarget& target, const RenderStates& states) const{
	auto nodes = scene.get_collision(cam_rect);
	for (const auto& node : nodes){
		auto drawable = dynamic_cast<Drawable*>(node);
		if (drawable) target.draw(*drawable, states);
	}
}
