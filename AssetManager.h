// AssetManager.h
// Chris Bowers

/**
 *	This defines a class that loads assets from json files and serves as a global access point for them.
 *	TODO: Add sounds, music
 */

#ifndef __ASSETMANAGER_H__
#define __ASSETMANAGER_H__

#include "json\json.h"
#include "SFML\Audio\Music.hpp"
#include "SFML\Audio\Sound.hpp"
#include "SFML\Audio\SoundBuffer.hpp"
#include "SFML\Graphics\Font.hpp"
#include "SFML\Graphics\Texture.hpp"
#include "Animation.h"
#include <fstream>
#include <string>
#include <unordered_map>

struct AssetManager{
	void load_animations(const std::string& filename);
	void load_config(const std::string& filename);
	void load_fonts(const std::string& filename);
	void load_music(const std::string& filename);
	void load_sounds(const std::string& filename);
	void load_text(const std::string& filename);
	void load_textures(const std::string& filename);

	Animation& get_animation(const std::string& key);
	Json::Value& get_config(const std::string& key);
	sf::Font& get_font(const std::string& key);
	sf::Music& get_music(const std::string& key);
	sf::SoundBuffer& get_sound(const std::string& key);
	std::string& get_text(const std::string& key);
	sf::Texture& get_texture(const std::string& key);

	int get_config_int(const std::string& key) const;
	unsigned int get_config_uint(const std::string& key) const;
	float get_config_float(const std::string& key) const;
	double get_config_double(const std::string& key) const;
	std::string get_config_string(const std::string& key) const;

	Animation& get_animation(const std::string& key, Animation& default);
	sf::Font& get_font(const std::string& key, sf::Font& default);
	sf::Music& get_music(const std::string& key, sf::Music& default);
	sf::SoundBuffer& get_sound(const std::string& key, sf::SoundBuffer& default);
	std::string& get_text(const std::string& key, std::string& default);
	sf::Texture& get_texture(const std::string& key, sf::Texture& default);

	bool has_animation(const std::string& key) const;
	bool has_config(const std::string& key) const;
	bool has_font(const std::string& key) const;
	bool has_music(const std::string& key) const;
	bool has_sound(const std::string& key) const;
	bool has_text(const std::string& key) const;
	bool has_texture(const std::string& key) const;

	size_t anim_count() const;
	size_t font_count() const;
	size_t music_count() const;
	size_t sound_count() const;
	size_t text_count() const;
	size_t texture_count() const;

	void clear_anims();
	void clear_config();
	void clear_fonts();
	void clear_music();
	void clear_sounds();
	void clear_text();
	void clear_textures();

	void clear_assets();

private:
	static sf::IntRect frame_rect(int index, int horiz_size, int tex_width, int tex_height);

	std::unordered_map<std::string, Animation> anims;
	std::unordered_map<std::string, sf::Font> fonts;
	std::unordered_map<std::string, sf::Music> musics;
	std::unordered_map<std::string, sf::SoundBuffer> soundbuffers;
	std::unordered_map<std::string, sf::Texture> texs;
	std::unordered_map<std::string, Json::Value> texdata;
	std::unordered_map<std::string, std::string> strings;
	Json::Value config;
};


#endif // __ASSETMANAGER_H__
