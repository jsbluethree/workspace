// Animation.cpp
// Chris Bowers

/**
 *	This implements a sprite animation - see Animation.h
 */

#include "Animation.h"

Animation::Animation() : tex{ nullptr } {}

void Animation::add_frame(sf::IntRect rect) { frames.push_back(rect); }

const sf::IntRect& Animation::get_frame(size_t n) const { return frames[n]; }

void Animation::clear_frames() { frames.clear(); }

size_t Animation::size() const { return frames.size(); }

void Animation::set_texture(const sf::Texture& texture) { tex = &texture; }

const sf::Texture* Animation::get_texture() const { return tex; }
