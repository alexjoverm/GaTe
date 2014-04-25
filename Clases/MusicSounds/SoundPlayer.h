/*#ifndef BOOK_SOUNDPLAYER_HPP
#define BOOK_SOUNDPLAYER_HPP



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
                Disparo,
                Disparo2,
                Explosion,
                MuerteEnemigo,
        };
}

typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID>
SoundBufferHolder;

class SoundPlayer : private sf::NonCopyable
{
	public:
									SoundPlayer();

		void						play(SoundEffect::ID effect);
		void						play(SoundEffect::ID effect, sf::Vector2f position);

		void						removeStoppedSounds();
		void						setListenerPosition(sf::Vector2f position);
		sf::Vector2f				getListenerPosition() const;


	private:
		SoundBufferHolder			mSoundBuffers;
		std::list<sf::Sound>                    mSounds;
};

#endif // BOOK_SOUNDPLAYER_HPP
*/