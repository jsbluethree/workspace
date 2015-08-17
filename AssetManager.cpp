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
	file.close();
	const auto& janims = jroot["animations"];
	for (const auto& key : janims.getMemberNames()){
		anims[key].set_texture(texs[janims[key]["texname"].asString()]);
		anims[key].clear_frames();
		if (janims[key]["frames"].isIntegral()){
			for (int i = 0; i < janims[key]["frames"].asInt(); ++i){
				const auto& tex = texdata[janims[key]["texname"].asString()];
				anims[key].add_frame(frame_rect(i, tex["horiz size"].asInt(),
					tex["tex width"].asInt(), tex["tex height"].asInt()));
			}
		}
		else if (janims[key]["frames"].isArray()){
			for (auto it = janims[key]["frames"].begin(); it != janims[key]["frames"].end(); ++it){
				const auto& tex = texdata[janims[key]["texname"].asString()];
				anims[key].add_frame(frame_rect(it->asInt(), tex["horiz size"].asInt(),
					tex["tex width"].asInt(), tex["tex height"].asInt()));
			}
		}
	}
}

void AssetManager::load_fonts(const std::string& filename){
	std::ifstream file(filename);
	Json::Value jroot;
	file >> jroot;
	file.close();
	const auto& jfonts = jroot["fonts"];
	for (const auto& key : jfonts.getMemberNames()){
		fonts[key].loadFromFile(jfonts[key]["filename"].asString());
	}
}

void AssetManager::load_music(const std::string& filename){
	std::ifstream file(filename);
	Json::Value jroot;
	file >> jroot;
	file.close();
	const auto& jmusic = jroot["music"];
	for (const auto& key : jmusic.getMemberNames()){
		musics[key].openFromFile(jmusic[key]["filename"].asString());
	}
}

void AssetManager::load_sounds(const std::string& filename){
	std::ifstream file(filename);
	Json::Value jroot;
	file >> jroot;
	file.close();
	const auto& jsounds = jroot["sounds"];
	for (const auto& key : jsounds.getMemberNames()){
		soundbuffers[jsounds[key]["filename"].asString()].loadFromFile(jsounds[key]["filename"].asString());
		sounds[key].setBuffer(soundbuffers[jsounds[key]["filename"].asString()]);
	}
}

void AssetManager::load_textures(const std::string& filename){
	std::ifstream file(filename);
	Json::Value jroot;
	file >> jroot;
	file.close();
	const auto& jtexs = jroot["textures"];
	for (const auto& key : jtexs.getMemberNames()){
		texs[key].loadFromFile(jtexs[key]["filename"].asString());
		texdata[key] = jtexs[key];
		if (texdata[key]["spritesheet"].asBool()){
			texdata[key]["tex width"] = texs[key].getSize().x / texdata[key]["horiz size"].asInt();
			texdata[key]["tex height"] = texs[key].getSize().y / texdata[key]["vert size"].asInt();
		}
	}
}

Animation& AssetManager::get_animation(const std::string& key) { return anims[key]; }

sf::Font& AssetManager::get_font(const std::string& key) { return fonts[key]; }

sf::Music& AssetManager::get_music(const std::string& key) { return musics[key]; }

sf::Sound& AssetManager::get_sound(const std::string& key) { return sounds[key]; }

sf::Texture& AssetManager::get_texture(const std::string& key) { return texs[key]; }

bool AssetManager::has_animation(const std::string& key) const { return anims.count(key) > 0; }

bool AssetManager::has_font(const std::string& key) const { return fonts.count(key) > 0; }

bool AssetManager::has_music(const std::string& key) const { return musics.count(key) > 0; }

bool AssetManager::has_sound(const std::string& key) const { return sounds.count(key) > 0; }

bool AssetManager::has_texture(const std::string& key) const { return texs.count(key) > 0; }

size_t AssetManager::anim_count() const { return anims.size(); }

size_t AssetManager::font_count() const { return fonts.size(); }

size_t AssetManager::music_count() const { return musics.size(); }

size_t AssetManager::sound_count() const { return sounds.size(); }

size_t AssetManager::tex_count() const { return texs.size(); }

void AssetManager::clear_anims() { anims.clear(); }

void AssetManager::clear_fonts() { fonts.clear(); }

void AssetManager::clear_musics() { musics.clear(); }

void AssetManager::clear_sounds() { sounds.clear(); }

void AssetManager::clear_texs() { texs.clear(); }

void AssetManager::clear_assets() { anims.clear(); fonts.clear(); musics.clear(); sounds.clear(); texs.clear(); }

sf::IntRect AssetManager::frame_rect(int index, int horiz_size, int tex_width, int tex_height){
	return{ (index % horiz_size) * tex_width, (index / horiz_size) * tex_height, tex_width, tex_height };
}
