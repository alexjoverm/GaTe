/* 
 * File:   State.h
 * Author: alejandrojovermorales
 *
 * Created on April 22, 2014, 12:59 PM
 */

#ifndef STATE_H
#define	STATE_H

#include "../Otros/Time.h"
#include "../Motor2D/RenderWindow.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/InputManager.h"
#include "../MusicSounds/SoundPlayer.h"

namespace States{
	enum ID{
		MenuState, SettingsState, LevelSelectionState, WorldState, PauseState, 
        CreditsState, TowerSelectionState, LoadingState, TutorialState
	};
}


class State {
public:    
    virtual void HandleEvents() = 0;
	virtual void Update(const Time& timeElapsed) = 0;
	virtual void Render(float interp) = 0;
    
    virtual void Clean() = 0;
    virtual void Init() = 0;
    
    virtual void AddNonRealEvent(sf::Event e) = 0;
	virtual void AddRealEvent(sf::Event e) = 0;
    
    RenderWindow* window;
    InputManager* inputManager;
    ResourceManager* resourceManager;
    
    States::ID  id;
};

#endif	/* STATE_H */

