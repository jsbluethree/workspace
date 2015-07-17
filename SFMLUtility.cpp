// SFMLUtility.cpp

/**
 *	Implements various utility functions for SFML types - see SFMLUtility.h
 */

#include "SFMLUtility.h"

template<typename T>
size_t std::hash<Vector2<T>>::operator()(const Vector2<T>& arg){
	std::hash<T> hasher;
	return (hasher(arg.x) ^ (hasher(arg.y) >> 1)) << 1;
}

template<typename T>
size_t std::hash<Vector3<T>>::operator()(const Vector3<T>& arg){
	std::hash<T> hasher;
	return (hasher(arg.x) ^ (hasher(arg.y) >> 1) ^ (hasher(arg.z) >> 2)) << 2;
}

template<typename T>
size_t std::hash<Rect<T>>::operator()(const Rect<T>& arg){
	std::hash<T> hasher;
	return (hasher(arg.left) ^ (hasher(arg.top) >> 1) ^ (hasher(arg.width) >> 2) ^ (hasher(arg.height) >> 3)) << 3;
}