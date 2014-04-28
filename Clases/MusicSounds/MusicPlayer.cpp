/* 
 * File:   MusicPlayer.cpp
 * Author: aba
 * 
 * Created on April 25, 2014, 8:40 AM
 */

#include "MusicPlayer.h"

MusicPlayer* MusicPlayer::instance = 0;

MusicPlayer* MusicPlayer::Instance() {
	if(instance == 0)
		instance = new MusicPlayer();
	
	return instance;
}


MusicPlayer::MusicPlayer()
{
    mMusic = new sf::Music();
    mFilenames = new std::map<Music::ID, std::string>();
    
    mFilenames->insert(std::make_pair(Music::MenuTheme , "Recursos/Music/MenuTheme.ogg"));
    mFilenames->insert(std::make_pair(Music::Level1Theme , "Recursos/Music/Deeper.ogg"));
    
    mMusic->setVolume(90.f);
    currentTheme = Music::MenuTheme;
    isPlaying = false;
}

MusicPlayer::~MusicPlayer()
{
    delete mMusic; mMusic=NULL;
    delete mFilenames; mFilenames=NULL;
}

void MusicPlayer::Load(Music::ID theme){
    currentTheme = theme;
    std::string filename = mFilenames->find(theme)->second;

	if (!mMusic->openFromFile(filename))
		throw std::string("Music " + filename + " could not be loaded.");
}

void MusicPlayer::Play()
{
    if(!isPlaying)
    {
        mMusic->setLoop(true);
        mMusic->play();
        isPlaying = true;
    }
}

void MusicPlayer::Stop()
{
	mMusic->stop();
    isPlaying = false;
}

void MusicPlayer::SetVolume(float volume)
{
    if(volume < 0.f || volume > 100.f)
        throw std::string("Debes introducir un valor entre 0 y 100");
    
    mMusic->setVolume(volume);
}

void MusicPlayer::SetPaused(bool paused)
{
	if (paused){
		mMusic->pause();
        isPlaying = false;
    }
	else{
		mMusic->play();
        isPlaying = true;
    }
}


