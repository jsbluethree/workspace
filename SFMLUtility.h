// SFMLUtility.h

/**
 *	This defines various utility functions for SFML types Vector2, Vector3 and Rect.
 */

#ifndef __SFMLUTILITY_H__
#define __SFMLUTILITY_H__

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

template<typename T>
struct std::hash<Rect<T>>{
	typedef size_t result_type;
	typedef Rect<T> argument_type;
	size_t operator()(const Rect<T>& arg);
};

#endif // __SFMLUTILITY_H__
