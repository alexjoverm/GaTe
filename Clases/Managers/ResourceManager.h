/* 
 * File:   ResourceManager.h
 * Author: linuxero
 *
 * Created on April 8, 2014, 10:37 AM
 */

#ifndef RESOURCEMANAGER_H
#define	RESOURCEMANAGER_H

#include "ResourceHolder.hpp"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>

class ResourceManager {
	
public:
	static ResourceManager* Instance();

// GETTERS
	ResourceHolder<sf::Font, std::string>*		GetContFonts() const;
	ResourceHolder<sf::SoundBuffer, std::string>*		GetContSoundBuffers() const;
	ResourceHolder<sf::Texture, std::string>*	GetContTextures() const;
	
	const sf::Font&		GetFont(std::string id) const;
	const sf::Texture&	GetTexture(std::string id) const;
	const sf::SoundBuffer&	GetSoundBuffer(std::string id) const;
	
	
// ADDERS
	void AddFont(std::string id, std::string filename);
	void AddTexture(std::string id, std::string filename);
	void AddSoundBuffer(std::string id, std::string filename);
	

protected:
	ResourceManager();
	ResourceManager(const ResourceManager& orig);
	virtual ~ResourceManager();
	
private:
	static ResourceManager* instance;
	
	ResourceHolder<sf::Texture, std::string>	*contTextures;
    ResourceHolder<sf::Font, std::string>		*contFonts;
	ResourceHolder<sf::SoundBuffer, std::string>	*contSoundBuffers;
	
};

#endif	/* RESOURCEMANAGER_H */

