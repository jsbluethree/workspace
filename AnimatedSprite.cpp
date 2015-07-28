// AnimatedSprite.cpp
// Chris Bowers

/**
 *	This implements an animated sprite - see AnimatedSprite.h
 */

#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(Time frame_time, bool paused, bool looped)
: Sprite{}, current_anim{ nullptr }, frame_time{ frame_time }, current_frame{ 0 }, paused{ paused }, looped{ looped } {}

void AnimatedSprite::update(Time dt){
	if (!paused && current_anim){
		current_time += dt;
		if (current_time >= frame_time){
			current_time = microseconds(current_time.asMicroseconds() % frame_time.asMicroseconds());
			if (++current_frame >= current_anim->size()){
				current_frame = 0;
				if (!looped){
					paused = true;
				}
			}
			set_frame(current_frame, false);
		}
	}
}

void AnimatedSprite::set_animation(const Animation& anim){
	current_anim = &anim;
	setTexture(*anim.get_texture());
	current_frame = 0;
	set_frame(current_frame);
}

void AnimatedSprite::set_frame_time(Time time) { frame_time = time; }

void AnimatedSprite::play() { paused = false; }

void AnimatedSprite::play(const Animation& anim){
	if (get_animation() != &anim)
		set_animation(anim);
	paused = false;
}

void AnimatedSprite::pause() { paused = true; }

void AnimatedSprite::stop(){
	paused = true;
	current_frame = 0;
	set_frame(current_frame);
}

void AnimatedSprite::set_looped(bool loop) { looped = loop; }

const Animation* AnimatedSprite::get_animation() const { return current_anim; }

bool AnimatedSprite::is_looped() const { return looped; }

bool AnimatedSprite::is_playing() const { return !paused; }

Time AnimatedSprite::get_frame_time() const { return frame_time; }

void AnimatedSprite::set_frame(size_t new_frame, bool reset_time){
	if (current_anim) setTextureRect(current_anim->get_frame(new_frame));
	if (reset_time) current_time = Time::Zero;
}

const Time AnimatedSprite::default_frame_time = seconds(1.0f / 30.0f);
