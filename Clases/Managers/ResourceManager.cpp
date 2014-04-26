/* 
 * File:   ResourceManager.cpp
 * Author: linuxero
 * 
 * Created on April 8, 2014, 10:37 AM
 */

#include "ResourceManager.h"

ResourceManager* ResourceManager::instance = 0;


ResourceManager* ResourceManager::Instance() {
	if(instance == 0)
		instance = new ResourceManager();
	
	return instance;
}


ResourceManager::ResourceManager() {
	contTextures = new ResourceHolder<sf::Texture, std::string>();
	contFonts = new ResourceHolder<sf::Font, std::string>();
	contSoundBuffers = new ResourceHolder<sf::SoundBuffer, std::string>();
}

ResourceManager::ResourceManager(const ResourceManager& orig) {
}

ResourceManager::~ResourceManager() {
	delete contTextures;
	delete contFonts;
	delete contSoundBuffers;
}

	

// GETTERS
ResourceHolder<sf::Font, std::string>* ResourceManager::GetContFonts() const {
	return contFonts;
}

ResourceHolder<sf::SoundBuffer, std::string>* ResourceManager::GetContSoundBuffers() const {
	return contSoundBuffers;
}

ResourceHolder<sf::Texture, std::string>* ResourceManager::GetContTextures() const {
	return contTextures;
}

const sf::Font& ResourceManager::GetFont(std::string id) const{
	return contFonts->get(id);
}

const sf::Texture& ResourceManager::GetTexture(std::string id) const {
	return contTextures->get(id);
}

const sf::SoundBuffer& ResourceManager::GetSoundBuffer(std::string id) const {
	return contSoundBuffers->get(id);
}



// ADDERS
void ResourceManager::AddFont(std::string id, std::string filename) {
	contFonts->load(id, filename);
}

void ResourceManager::AddTexture(std::string id, std::string filename) {
	contTextures->load(id, filename);
}

void ResourceManager::AddSoundBuffer(std::string id, std::string filename) {
	contSoundBuffers->load(id, filename);
}


void ResourceManager::CleanResources() {
	contFonts->cleanResources();
    contTextures->cleanResources();
}

void ResourceManager::CleanGameSounds() {
	contSoundBuffers->cleanResources();
}

void ResourceManager::EraseFont(std::string id) {
	contFonts->remove(id);
}

void ResourceManager::EraseTexture(std::string id) {
	contTextures->remove(id);
}

void ResourceManager::EraseSoundBuffer(std::string id) {
	contSoundBuffers->remove(id);
}