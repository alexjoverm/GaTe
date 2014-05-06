#ifndef MUSICPLAYER_H
#define	MUSICPLAYER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>

#include <map>
#include <string>


namespace Music
{
        enum ID
        {
                MenuTheme, Level1Theme, Level2Theme, Level3Theme
        };
}

//template <typename Resource, typename Identifier>
class MusicPlayer : private sf::NonCopyable
{
public:
        static MusicPlayer* Instance(); // Singleton

        void Load(Music::ID theme);
        void Play();
        void Stop();
        void SetPaused(bool paused);
        
        bool IsPaused(){ bool a =mMusic->Playing; return !mMusic->Playing; }
        
        void SetVolume(float volume);
        float GetVolume() const{ return mMusic->getVolume(); }
        
        Music::ID      currentTheme;
        bool           isPlaying;   
        
        bool Activate(){ SetVolume((ultVol <= 4.f ? 60.f : ultVol)); }
        bool DeActivate(){ ultVol = GetVolume(); SetVolume(0.f); }
        
        float ultVol;

private:
    MusicPlayer();
    ~MusicPlayer();
    static MusicPlayer*	instance;
    
	sf::Music*			   mMusic;
	std::map<Music::ID, std::string>*   mFilenames;
};


#endif	/* MUSICPLAYER_H */