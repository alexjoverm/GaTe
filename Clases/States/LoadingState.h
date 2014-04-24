/* 
 * File:   World.h
 * Author: linuxero
 *
 * Created on March 15, 2014, 10:40 AM
 */

#ifndef LOADINGSTATE_H
#define	LOADINGSTATE_H

#include "../Motor2D/RenderWindow.h"
#include "../Managers/InputManager.h"
#include "../Managers/ResourceManager.h"
#include "../Otros/LoadingTask.h"
#include "../Otros/Clock.h"
#include "State.h"
#include <SFML/Graphics.hpp>
#include <iostream>


class LoadingState: public State {
public:
	LoadingState();
	LoadingState(const LoadingState& orig);
	virtual ~LoadingState();

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
    
	//Eventos
	std::vector<sf::Event>		*vNonRealEvents;
	std::vector<sf::Event>		*vRealEvents;
    
    SpriteSheet*    background;
    
    bool requestStateChange;
    LoadingTask*    loadingTask;
    float           seconds;
    bool            loaded;
};

#endif	/* WORLD_H */

