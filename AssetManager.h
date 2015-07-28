// AssetManager.h
// Chris Bowers

/**
 *	This defines a class that loads assets from json files and serves as a global access point for them.
 */

#ifndef __ASSETMANAGER_H__
#define __ASSETMANAGER_H__

#include "json/json.h"
#include "SFML.h"
#include "Animation.h"
#include <fstream>
#include <string>
#include <unordered_map>

struct AssetManager{
	void load_animations(const std::string& filename);
	void load_textures(const std::string& filename);
	void set_animation(const std::string& key, const Animation& anim);
	void set_texture(const std::string& key, const Texture& tex);
	Animation& get_animation(const std::string& key);
	Texture& get_texture(const std::string& key);
	bool has_animation(const std::string& key) const;
	bool has_texture(const std::string& key) const;
	size_t anim_count() const;
	size_t tex_count() const;
	void clear_anims();
	void clear_texs();
	void clear_assets();

private:
	std::unordered_map<std::string, Animation> anims;
	std::unordered_map<std::string, Texture> texs;

	static Json::Reader reader;
};


#endif // __ASSETMANAGER_H__
