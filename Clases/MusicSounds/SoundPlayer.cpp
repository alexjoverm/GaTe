#include "SoundPlayer.h"
#include "MusicPlayer.h"


#include <SFML/Audio/Listener.hpp>

#include <cmath>



// Sistema de coordenadas para el listener del player
const float ListenerZ = 300.f;
const float Attenuation = 8.f;
const float MinDistance2D = 200.f;
const float MinDistance3D = std::sqrt(MinDistance2D*MinDistance2D + ListenerZ*ListenerZ);

const float volumeLess = 0.15f;


SoundPlayer* SoundPlayer::instance = 0;

SoundPlayer* SoundPlayer::Instance() {
	if(instance == 0)
		instance = new SoundPlayer();
	
	return instance;
}

SoundPlayer::SoundPlayer()
{
    mSounds = new std::list<sf::Sound>();
    loaded = false;
    active = true;
    rm = ResourceManager::Instance();
    
	// Listener apunta hacia afuera de la pantalla
	sf::Listener::setDirection(0.f, 0.f, -1.f);
    
}

void SoundPlayer::Play(std::string so)
{
    if(active)
        Play(so, GetListenerPosition());
}

void SoundPlayer::Play(std::string so, sf::Vector2f position)
{
	mSounds->push_back(sf::Sound());
	sf::Sound& sound = mSounds->back();

	sound.setBuffer(rm->GetSoundBuffer(so));
	sound.setPosition(position.x, -position.y, 0.f);
	sound.setAttenuation(Attenuation);
	sound.setMinDistance(MinDistance3D);
    
    // El volumen será un 15% menos que el de la música
    sound.setVolume(MusicPlayer::Instance()->GetVolume() - MusicPlayer::Instance()->GetVolume()*volumeLess);

	sound.play();
}

void SoundPlayer::LoadMenuSounds()
{
    // FALTA AÑADIR MENU SOUNDS 
    
	loaded = true;
}

void SoundPlayer::LoadGameSounds()
{
	rm->AddSoundBuffer("shot",			"Recursos/Sounds/disparo_player.wav");
    rm->AddSoundBuffer("shot_torreta",	"Recursos/Sounds/disparo_torreta.wav");
    rm->AddSoundBuffer("laser",			"Recursos/Sounds/laser.wav");
    rm->AddSoundBuffer("explosion",		"Recursos/Sounds/explosion.wav");
    rm->AddSoundBuffer("enemyDeath",    "Recursos/Sounds/aliendeath.wav");
}



void SoundPlayer::RemoveStoppedSounds()
{
	mSounds->remove_if([] (const sf::Sound& s)
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