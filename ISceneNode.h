// ISceneNode.h
// Chris Bowers

#ifndef __ISCENENODE_H__
#define __ISCENENODE_H__

#include "typedefs.h"
#include "SFML.h"

struct ISceneNode{
	FloatRect& get_rect() = 0;
	const FloatRect& get_rect() const = 0;
};

#endif // __ISCENENODE_H__
