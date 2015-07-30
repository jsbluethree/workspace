// Animation.h
// Chris Bowers

/**
 *	This defines a sprite animation using a spritesheet.
 */

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SFML\Graphics\Rect.hpp"
#include <vector>

namespace sf{
	class Texture;
}

struct Animation{
	Animation();

	void add_frame(sf::IntRect rect);
	const sf::IntRect& get_frame(size_t n) const;
	void clear_frames();
	size_t size() const;
	void set_texture(const sf::Texture& texture);
	const sf::Texture* get_texture() const;

private:
	const sf::Texture* tex;
	std::vector<sf::IntRect> frames;
};

#endif // __ANIMATION_H__
