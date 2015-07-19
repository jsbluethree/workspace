// SFMLUtility.h
// Chris Bowers

/**
 *	This defines various utility functions for SFML types Vector2, Vector3 and Rect.
 */

#ifndef __SFMLUTILITY_H__
#define __SFMLUTILITY_H__

#include <cmath>
#include <functional>
#include <iostream>
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

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector2<T>& vec);

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector3<T>& vec);

template<typename T>
std::ostream& operator<<(std::ostream& os, const Rect<T>& rect);

template<typename T>
Rect<T> operator+(const Rect<T>& lhs, const Vector2<T>& rhs);

template<typename T>
Rect<T> operator+(const Vector2<T>& lhs, const Rect<T>& rhs);

template<typename T>
Rect<T> operator-(const Rect<T>& lhs, const Vector2<T>& rhs);

template<typename T>
Rect<T>& operator+=(Rect<T>& lhs, const Vector2<T> rhs);

template<typename T>
Rect<T>& operator-=(Rect<T>& lhs, const Vector2<T> rhs);

template<typename T>
T length(const Vector2<T>& vec);

template<typename T>
T length(const Vector3<T>& vec);

template<typename T>
T area(const Rect<T>& rect);

template<typename T>
Vector2<T> normalize(const Vector2<T>& vec);

template<typename T>
Vector3<T> normalize(const Vector3<T>& vec);

template<typename T>
T dot(const Vector2<T>& lhs, const Vector2<T>& rhs);

template<typename T>
T dot(const Vector3<T>& lhs, const Vector3<T>& rhs);

template<typename T>
Vector3<T> cross(const Vector3<T>& lhs, const Vector3<T>& rhs);

#endif // __SFMLUTILITY_H__
