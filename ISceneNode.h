// ISceneNode.h
// Chris Bowers

#ifndef __ISCENENODE_H__
#define __ISCENENODE_H__

#include "typedefs.h"
#include "SFML.h"

struct ISceneNode{
	virtual FloatRect& get_rect() = 0;
	virtual const FloatRect& get_rect() const = 0;
};

#endif // __ISCENENODE_H__
