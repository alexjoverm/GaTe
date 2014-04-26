#include "SoundPlayer.h"


#include <SFML/Audio/Listener.hpp>

#include <cmath>


namespace
{
	// Sistema de coordenadas para el player
	const float ListenerZ = 300.f;
	const float Attenuation = 8.f;
	const float MinDistance2D = 200.f;
	const float MinDistance3D = std::sqrt(MinDistance2D*MinDistance2D + ListenerZ*ListenerZ);
}

SoundPlayer::SoundPlayer()
: mSoundBuffers()
, mSounds()
{

    
	mSoundBuffers.load(SoundEffect::Shot,			"Recursos/Sounds/smash.wav");
    mSoundBuffers.load(SoundEffect::Laser,			"Recursos/Sounds/laser.wav");
    mSoundBuffers.load(SoundEffect::Explosion,		"Recursos/Sounds/explosion.wav");
    mSoundBuffers.load(SoundEffect::EnemyDeath,		"Recursos/Sounds/aliendeath.wav");

	// Listener apunta hacia afuera de la pantalla
	sf::Listener::setDirection(0.f, 0.f, -1.f);
}

void SoundPlayer::Play(SoundEffect::ID effect)
{
	Play(effect, GetListenerPosition());
}

void SoundPlayer::Play(SoundEffect::ID effect, sf::Vector2f position)
{
	mSounds.push_back(sf::Sound());
	sf::Sound& sound = mSounds.back();

	sound.setBuffer(mSoundBuffers.get(effect));
	sound.setPosition(position.x, -position.y, 0.f);
	sound.setAttenuation(Attenuation);
	sound.setMinDistance(MinDistance3D);

	sound.play();
}

void SoundPlayer::RemoveStoppedSounds()
{
	mSounds.remove_if([] (const sf::Sound& s)
	{
		return s.getStatus() == sf::Sound::Stopped;
	});
}

void SoundPlayer::SetListenerPosition(sf::Vector2f position)
{
	sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}

sf::Vector2f SoundPlayer::GetListenerPosition() const
{
	sf::Vector3f position = sf::Listener::getPosition();
	return sf::Vector2f(position.x, -position.y);
}