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
	FloatRect cam_rect;
	
	Camera(FloatRect init_rect);
	
	void render_scene(ISceneGraph* scene, RenderTarget& target, const RenderStates& states = RenderStates::Default);
};

#endif // _CAMERA_H__
