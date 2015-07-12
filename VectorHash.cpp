// VectorHash.cpp
// Chris Bowers

#include "VectorHash.h"

template<> template<typename T>
size_t std::hash<Vector2<T>>::operator()(const Vector2<T>& arg){
	std::hash<T> hasher;
	return (hasher(arg.x) ^ (hasher(arg.y) >> 1)) << 1;
}

template<> template<typename T>
size_t std::hash<Vector3<T>>::operator()(const Vector3<T>& arg){
	std::hash<T> hasher;
	return (hasher(arg.x) ^ (hasher(arg.y) >> 1) ^ (hasher(arg.z) >> 2)) << 2;
}