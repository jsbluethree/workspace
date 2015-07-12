// VectorHash.h
// Chris Bowers

#ifndef __VECTORHASH_H__
#define __VECTORHASH_H__

#include <functional>
#include "SFML.h"

template<> template<typename T>
struct std::hash<Vector2<T>>{
	typedef size_t result_type;
	typedef Vector2<T> argument_type;
	size_t operator()(const Vector2<T>& arg);
};

template<> template<typename T>
struct std::hash<Vector3<T>>{
	typedef size_t result_type;
	typedef Vector3<T> argument_type;
	size_t operator()(const Vector3<T>& arg);
};

#endif // __VECTORHASH_H__
