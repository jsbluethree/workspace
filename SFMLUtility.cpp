// SFMLUtility.cpp
// Chris Bowers

/**
 *	Implements various utility functions for SFML types - see SFMLUtility.h
 */

#include "SFMLUtility.h"

template<typename T>
size_t std::hash<sf::Vector2<T>>::operator()(const sf::Vector2<T>& arg){
	std::hash<T> hasher;
	return (hasher(arg.x) ^ (hasher(arg.y) >> 1)) << 1;
}

template<typename T>
size_t std::hash<sf::Vector3<T>>::operator()(const sf::Vector3<T>& arg){
	std::hash<T> hasher;
	return (hasher(arg.x) ^ (hasher(arg.y) >> 1) ^ (hasher(arg.z) >> 2)) << 2;
}

template<typename T>
size_t std::hash<sf::Rect<T>>::operator()(const sf::Rect<T>& arg){
	std::hash<T> hasher;
	return (hasher(arg.left) ^ (hasher(arg.top) >> 1) ^ (hasher(arg.width) >> 2) ^ (hasher(arg.height) >> 3)) << 3;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const sf::Vector2<T>& vec){
	os << '(' << vec.x << ' ' << vec.y << ')';
	return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const sf::Vector3<T>& vec){
	os << '(' << vec.x << ' ' << vec.y << ' ' << vec.z << ')';
	return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const sf::Rect<T>& rect){
	os << '(' << rect.left << ' ' << rect.top << ' ' << rect.width << ' ' << rect.height << ')';
	return os;
}

template<typename T>
sf::Rect<T> operator+(const sf::Rect<T>& lhs, const sf::Vector2<T>& rhs){
	return{ lhs.left + rhs.x, lhs.top + rhs.y, lhs.width, lhs.height };
}

template<typename T>
sf::Rect<T> operator+(const sf::Vector2<T>& lhs, const sf::Rect<T>& rhs){
	return rhs + lhs;
}

template<typename T>
sf::Rect<T> operator-(const sf::Rect<T>& lhs, const sf::Vector2<T>& rhs){
	return lhs + -rhs;
}

template<typename T>
sf::Rect<T>& operator+=(sf::Rect<T>& lhs, const sf::Vector2<T> rhs){
	lhs.left += rhs.x;
	lhs.top += rhs.y;
	return lhs;
}

template<typename T>
sf::Rect<T>& operator-=(sf::Rect<T>& lhs, const sf::Vector2<T> rhs){
	return lhs += -rhs;
}

template<typename T>
T length(const sf::Vector2<T>& vec){
	return sqrt(dot(vec, vec));
}

template<typename T>
T length(const sf::Vector3<T>& vec){
	return sqrt(dot(vec, vec));
}

template<typename T>
T area(const sf::Rect<T>& rect){
	return rect.width * rect.height;
}

template<typename T>
sf::Vector2<T> normalize(const sf::Vector2<T>& vec){
	return vec / length(vec);
}

template<typename T>
sf::Vector3<T> normalize(const sf::Vector3<T>& vec){
	return vec / length(vec);
}

template<typename T>
T dot(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs){
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

template<typename T>
T dot(const sf::Vector3<T>& lhs, const sf::Vector3<T>& rhs){
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

template<typename T>
sf::Vector3<T> cross(const sf::Vector3<T>& lhs, const sf::Vector3<T>& rhs){
	return{ lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.z - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x };
}
