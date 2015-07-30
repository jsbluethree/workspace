// SFMLUtility.h
// Chris Bowers

/**
 *	This defines various utility functions for SFML types Vector2, Vector3 and Rect.
 */

#ifndef __SFMLUTILITY_H__
#define __SFMLUTILITY_H__

#include "SFML\Graphics\Rect.hpp"
#include "SFML\System\Vector2.hpp"
#include "SFML\System\Vector3.hpp"
#include <cmath>
#include <functional>
#include <iostream>

template<typename T>
struct std::hash<sf::Vector2<T>>{
	typedef size_t result_type;
	typedef sf::Vector2<T> argument_type;
	size_t operator()(const sf::Vector2<T>& arg);
};

template<typename T>
struct std::hash<sf::Vector3<T>>{
	typedef size_t result_type;
	typedef sf::Vector3<T> argument_type;
	size_t operator()(const sf::Vector3<T>& arg);
};

template<typename T>
struct std::hash<sf::Rect<T>>{
	typedef size_t result_type;
	typedef sf::Rect<T> argument_type;
	size_t operator()(const sf::Rect<T>& arg);
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const sf::Vector2<T>& vec);

template<typename T>
std::ostream& operator<<(std::ostream& os, const sf::Vector3<T>& vec);

template<typename T>
std::ostream& operator<<(std::ostream& os, const sf::Rect<T>& rect);

template<typename T>
sf::Rect<T> operator+(const sf::Rect<T>& lhs, const sf::Vector2<T>& rhs);

template<typename T>
sf::Rect<T> operator+(const sf::Vector2<T>& lhs, const sf::Rect<T>& rhs);

template<typename T>
sf::Rect<T> operator-(const sf::Rect<T>& lhs, const sf::Vector2<T>& rhs);

template<typename T>
sf::Rect<T>& operator+=(sf::Rect<T>& lhs, const sf::Vector2<T> rhs);

template<typename T>
sf::Rect<T>& operator-=(sf::Rect<T>& lhs, const sf::Vector2<T> rhs);

template<typename T>
T length(const sf::Vector2<T>& vec);

template<typename T>
T length(const sf::Vector3<T>& vec);

template<typename T>
T area(const sf::Rect<T>& rect);

template<typename T>
sf::Vector2<T> normalize(const sf::Vector2<T>& vec);

template<typename T>
sf::Vector3<T> normalize(const sf::Vector3<T>& vec);

template<typename T>
T dot(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs);

template<typename T>
T dot(const sf::Vector3<T>& lhs, const sf::Vector3<T>& rhs);

template<typename T>
sf::Vector3<T> cross(const sf::Vector3<T>& lhs, const sf::Vector3<T>& rhs);

#endif // __SFMLUTILITY_H__
