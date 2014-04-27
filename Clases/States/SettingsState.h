/* 
 * File:   World.h
 * Author: linuxero
 *
 * Created on March 15, 2014, 10:40 AM
 */

#ifndef SETTINGSSTATE_H
#define	SETTINGSSTATE_H

#include "../Motor2D/RenderWindow.h"
#include "../Managers/InputManager.h"
#include "../Managers/ResourceManager.h"
#include "../HUD/ImageButton.h"
#include "../Otros/Time.h"
#include "../MusicSounds/MusicPlayer.h"
#include "../MusicSounds/SoundPlayer.h"
#include "State.h"
#include <SFML/Graphics.hpp>
#include <iostream>





class SettingsState: public State {
public:
	SettingsState();
	SettingsState(const SettingsState& orig);
	virtual ~SettingsState();

// Inicialización y Liberación
	void Init();
    void Clean();
    
// 3 bucles principales
	void Update(const Time& timeElapsed);
	void Render(float interp);
    
// Eventos
	void HandleEvents(); // Le pasa al InputManager los eventos
	void AddNonRealEvent(sf::Event e){ vNonRealEvents->push_back(e); }
	void AddRealEvent(sf::Event e){ vRealEvents->push_back(e); }
	void ProcessRealEvent();
    //void ProcessNonRealEvent();
 

private:
    
  // Funciones
	void LoadResources();	// Carga recursos, se llama desde Init();
    
    void SetFrameMusicButton(int frame);
    void SetFrameSoundButton(int frame);
    
    void ToogleSoundButton();
    void ToogleMusicButton();
    
	//Eventos
	std::vector<sf::Event>		*vNonRealEvents;
	std::vector<sf::Event>		*vRealEvents;
    
    SpriteSheet*    background;
    std::vector<sf::Text*>   *vTexts;
    
    ImageButton         *soundEffects, *music, *returnButton; //*shotAng;
    
    //Players
    MusicPlayer*         musicPlayer;
    SoundPlayer*         soundPlayer;
    
};

#endif	/* WORLD_H */

