// Grid.h
// Chris Bowers

#ifndef __GRID_H__
#define __GRID_H__

#include "SFML.h"
#include "ISceneGraph.h"
#include "VectorHash.h"
#include <unordered_map>

struct Grid : ISceneGraph{
	std::unordered_map<Vector2i, ISceneNode*> nodes;
}

#endif // __GRID_H__
