// AssetManager.cpp
// Chris Bowers

/**
 *	Implements an asset manager - see AssetManager.h
 */

#include "AssetManager.h"

void AssetManager::load_animations(const std::string& filename){
	std::ifstream file(filename);
	Json::Value jroot;
	file >> jroot;
	const auto& janims = jroot["animations"];
	for (const auto& key : janims.getMemberNames()){
		anims[key].set_texture(texs[janims[key]["texname"].asString()]);
		anims[key].clear_frames();
		for (int y = 0; y < janims[key]["theight"].asInt(); ++y){
			for (int x = 0; x < janims[key]["twidth"].asInt(); ++x){
				IntRect frame{ x * janims[key]["fwidth"].asInt(), y * janims[key]["fheight"].asInt(),
					janims[key]["fwidth"].asInt(), janims[key]["fheight"].asInt() };
				anims[key].add_frame(frame);
			}
		}
	}
}

void AssetManager::load_textures(const std::string& filename){
	std::ifstream file(filename);
	Json::Value jroot;
	file >> jroot;
	const auto& jtexs = jroot["textures"];
	for (const auto& key : jtexs.getMemberNames()){
		texs[key].loadFromFile(jtexs[key].asString());
	}
}

void AssetManager::set_animation(const std::string& key, const Animation& anim) { anims[key] = anim; }

void AssetManager::set_texture(const std::string& key, const Texture& tex) { texs[key] = tex; }

Animation& AssetManager::get_animation(const std::string& key) { return anims[key]; }

Texture& AssetManager::get_texture(const std::string& key) { return texs[key]; }

bool AssetManager::has_animation(const std::string& key) const { return anims.count(key) == 1; }

bool AssetManager::has_texture(const std::string& key) const { return texs.count(key) == 1; }

size_t AssetManager::anim_count() const { return anims.size(); }

size_t AssetManager::tex_count() const { return texs.size(); }

void AssetManager::clear_anims() { anims.clear(); }

void AssetManager::clear_texs() { texs.clear(); }

void AssetManager::clear_assets() { anims.clear(); texs.clear(); }
