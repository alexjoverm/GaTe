/* 
 * File:   World.h
 * Author: linuxero
 *
 * Created on March 15, 2014, 10:40 AM
 */

#ifndef MENUSTATE_H
#define	MENUSTATE_H

#include "../Motor2D/Level.h"
#include "../Entities/Player.h"
#include "../Entities/Bullet.h"
#include "../Motor2D/RenderWindow.h"
#include "../Otros/Clock.h"
#include "../Entities/EntActive.h"
#include "../Managers/InputManager.h"
#include "../Managers/ResourceManager.h"
#include "State.h"
#include <SFML/Graphics.hpp>
#include <iostream>





class MenuState: public State {
public:
	static MenuState* Instance(); // Singleton

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
 
    sf::Text			textColision;

private:
	
  // Singleton
	MenuState();
	MenuState(const MenuState& orig);
	virtual ~MenuState();
	static MenuState*	instance;
    
  // Funciones
	void LoadResources();	// Carga recursos, se llama desde Init();
    
	//Eventos
	std::vector<sf::Event>		*vNonRealEvents;
	std::vector<sf::Event>		*vRealEvents;
};

#endif	/* WORLD_H */

