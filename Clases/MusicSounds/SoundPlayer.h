#ifndef SOUNDPLAYER_H
#define	SOUNDPLAYER_H

#include <SFML/System/Vector2.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "../Managers/ResourceManager.h"

#include <list>


class SoundPlayer
{
public:
    static SoundPlayer* Instance(); // Singleton

    void Play(std::string so);
    void Play(std::string so, sf::Vector2f position);
    
    void LoadGameSounds();
    void LoadMenuSounds();
    
    void Clean();

    void RemoveStoppedSounds();

    void SetListenerPosition(sf::Vector2f position);
    sf::Vector2f	GetListenerPosition() const;

    bool                       loaded;
    
private:
    SoundPlayer();
    ~SoundPlayer();
    static SoundPlayer*	instance;
    
    std::list<sf::Sound>    *mSounds;
    ResourceManager           *rm;
};

#endif	/* SOUNDPLAYER_H */

