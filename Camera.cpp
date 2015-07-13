// Camera.cpp
// Chris Bowers

#include "Camera.h"

Camera::Camera(FloatRect init_rect) : cam_rect{ init_rect } {}

void Camera::render_scene(ISceneGraph* scene, RenderTarget& target, const RenderStates& states){
	auto nodes = scene->get_collision(cam_rect);
	for (const auto& node : nodes){
		auto drawable = dynamic_cast<Drawable*>(node);
		if (drawable) target.draw(*drawable, states);
	}
}