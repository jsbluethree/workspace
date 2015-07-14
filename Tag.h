// Tag.h
// Chris Bowers

/**
 *	This defines a 7-character tag. The tag uses a union of u64 and char[8] for more efficient comparison than std::string or c-strings.
 */

#ifndef __TAG_H__
#define __TAG_H__

#include "typedefs.h"
#include <functional>
#include <iostream>

struct Tag{
	union {
		char name[8];
		u64 val;
	};

	Tag();
	Tag(const Tag& other);
	Tag(const char* chars);
	Tag& operator=(const Tag& other);
	Tag& operator=(const char* chars);
	~Tag();
};

bool operator==(const Tag& lhs, const Tag& rhs);
bool operator!=(const Tag& lhs, const Tag& rhs);
bool operator<(const Tag& lhs, const Tag& rhs);
bool operator<=(const Tag& lhs, const Tag& rhs);
bool operator>(const Tag& lhs, const Tag& rhs);
bool operator>=(const Tag& lhs, const Tag& rhs);

std::istream& operator>>(std::istream& is, Tag& tag);
std::ostream& operator<<(std::ostream& os, const Tag& tag);

template<>
struct std::hash<Tag>{
	typedef size_t result_type;
	typedef Tag argument_type;
	size_t operator()(const Tag& arg);
};

#endif // __TAG_H__
