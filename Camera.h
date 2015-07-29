// Camera.h
// Chris Bowers

/**
 *	This defines a simple camera. It renders all drawables from the given scene that are located within it's own rect.
 */

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "SFML.h"
#include "ISceneGraph.h"

struct Camera{
	explicit Camera(FloatRect source, FloatRect viewport = { 0.0f, 0.0f, 1.0f, 1.0f });
	virtual ~Camera() = default;
	
	void render_scene(const ISceneGraph& scene, RenderTarget& target, const RenderStates& states = RenderStates::Default) const;

	FloatRect source_rect;
	FloatRect viewport_rect;
};

#endif // __CAMERA_H__
