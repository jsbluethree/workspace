// Tag.cpp
// Chris Bowers

/**
 *	This implements a 7-character tag - see Tag.h
 */

#include "Tag.h"

Tag::Tag() : val{ 0 } {}

Tag::Tag(const Tag& other) : val{ other.val } {}

Tag::Tag(const char* chars){
	u8 i;
	for (i = 0; chars[i] != '\0' && i < 7; i++){
		name[i] = chars[i];
	}
	for (; i < 8; i++){
		name[i] = 0;
	}
}

Tag& Tag::operator=(const Tag& other) { val = other.val; return *this; }

Tag& Tag::operator=(const char* chars){
	u8 i;
	for (i = 0; chars[i] != 0 && i < 7; i++){
		name[i] = chars[i];
	}
	for (; i < 8; i++){
		name[i] = 0;
	}
	return *this;
}

Tag::~Tag() {}

bool operator==(const Tag& lhs, const Tag& rhs) { return lhs.val == rhs.val; }
bool operator!=(const Tag& lhs, const Tag& rhs) { return lhs.val != rhs.val; }
bool operator<(const Tag& lhs, const Tag& rhs) { return lhs.val < rhs.val; }
bool operator<=(const Tag& lhs, const Tag& rhs) { return lhs.val <= rhs.val; }
bool operator>(const Tag& lhs, const Tag& rhs) { return lhs.val > rhs.val; }
bool operator>=(const Tag& lhs, const Tag& rhs) { return lhs.val >= rhs.val; }

std::istream& operator>>(std::istream& is, Tag& tag){
	is.width(8);
	is >> (char*)&tag;
	is.width(0);
	return is;
}

std::ostream& operator<<(std::ostream& os, const Tag& tag){
	for (u8 i = 0; tag.name[i] != '\0' && i < 7; i++){
		os << tag.name[i];
	}
	return os;
}

template<>
size_t std::hash<Tag>::operator()(const Tag& arg){
	return std::hash<u64>()(arg.val);
}
