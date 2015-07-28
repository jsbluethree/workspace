// Animation.h
// Chris Bowers

/**
 *	This defines a sprite animation using a spritesheet.
 *
 *	TODO: write function to populate information from json
 */

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SFML.h"
#include <vector>

struct Animation{
	Animation();

	void add_frame(IntRect rect);
	const IntRect& get_frame(size_t n) const;
	void clear_frames();
	size_t size() const;
	void set_texture(const Texture& texture);
	const Texture* get_texture() const;

private:
	const Texture* tex;
	std::vector<IntRect> frames;	
};

#endif // __ANIMATION_H__
