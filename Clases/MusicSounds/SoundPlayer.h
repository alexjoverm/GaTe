#ifndef SOUNDPLAYER_H
#define	SOUNDPLAYER_H

#include <SFML/System/Vector2.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "../Includes/ResourceHolder.hpp"

#include <list>


namespace SoundEffect
{
    enum ID
    {
        Shot, Laser, 
        Explosion, EnemyDeath,
    };
}

typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID> SoundBufferHolder;

class SoundPlayer : private sf::NonCopyable
{
public:
									SoundPlayer();

                void Play(SoundEffect::ID effect);
                void Play(SoundEffect::ID effect, sf::Vector2f position);

                void RemoveStoppedSounds();
                void SetListenerPosition(sf::Vector2f position);


                sf::Vector2f	GetListenerPosition() const;


private:
		SoundBufferHolder	mSoundBuffers;
		std::list<sf::Sound>    mSounds;
};

#endif	/* SOUNDPLAYER_H */

