// AnimatedSprite.h
// Chris Bowers

/**
 *	This defines an animated sprite - see Animation.h and SFML/Graphics/Sprite.hpp
 */

#ifndef __ANIMATEDSPRITE_H__
#define __ANIMATEDSPRITE_H__

#include "SFML\Graphics\Sprite.hpp"
#include "SFML\System\Time.hpp"
#include "Animation.h"

struct AnimatedSprite : sf::Sprite{
	explicit AnimatedSprite(sf::Time frame_time = default_frame_time, bool paused = false, bool looped = true);

	void update(sf::Time dt);
	void set_animation(const Animation& anim);
	void set_frame_time(sf::Time time);
	void play();
	void play(const Animation& anim);
	void pause();
	void stop();
	void set_looped(bool loop);
	const Animation* get_animation() const;
	bool is_looped() const;
	bool is_playing() const;
	sf::Time get_frame_time() const;
	void set_frame(size_t new_frame, bool reset_time = true);

	static const sf::Time default_frame_time;
private:
	const Animation* current_anim;
	sf::Time frame_time;
	sf::Time current_time;
	size_t current_frame;
	bool paused;
	bool looped;
};

#endif // __ANIMATEDSPRITE_H__
