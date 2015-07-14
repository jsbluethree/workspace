// VectorHash.h
// Chris Bowers

/**
 *	This defines std::hash specializations for sfml's vector types.
 *	This allows them to be used as keys in hash tables given that the vector elements themselves have std::hash specializations.
 */

#ifndef __VECTORHASH_H__
#define __VECTORHASH_H__

#include <functional>
#include "SFML.h"

template<typename T>
struct std::hash<Vector2<T>>{
	typedef size_t result_type;
	typedef Vector2<T> argument_type;
	size_t operator()(const Vector2<T>& arg);
};

template<typename T>
struct std::hash<Vector3<T>>{
	typedef size_t result_type;
	typedef Vector3<T> argument_type;
	size_t operator()(const Vector3<T>& arg);
};

#endif // __VECTORHASH_H__
