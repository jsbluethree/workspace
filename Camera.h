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
	
	void set_source(const FloatRect& rect);
	void set_viewport(const FloatRect& rect);
	FloatRect get_source() const;
	FloatRect get_viewport() const;
	void move(float dx, float dy);
	void move(const Vector2f& d);
	void render_scene(const ISceneGraph& scene, RenderTarget& target, const RenderStates& states = RenderStates::Default) const;

private:
	View view;
};

#endif // __CAMERA_H__
