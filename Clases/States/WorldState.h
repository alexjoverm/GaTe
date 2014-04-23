/* 
 * File:   World.h
 * Author: linuxero
 *
 * Created on March 15, 2014, 10:40 AM
 */

#ifndef WORLDSTATE_H
#define	WORLDSTATE_H

#include "../Motor2D/Level.h"
#include "../Entities/Player.h"
#include "../Entities/Bullet.h"
#include "../Motor2D/RenderWindow.h"
#include "../Otros/Clock.h"
#include "../Entities/EntActive.h"
#include "../Managers/InputManager.h"
#include "../Managers/ResourceManager.h"
#include "../HUD/HUD.h"
#include "State.h"
#include <SFML/Graphics.hpp>
#include <iostream>



class WorldState: public State {
public:
	static WorldState* Instance(); // Singleton

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
	
// Level y Map	
    void AddLevelColision(Rectangle* rec){ level->AddColision(rec); }
    void AddLevelTexture(const std::string tex){ level->AddTextureFile(tex); }
    Level*		level;
 
// Entities
	void AddStaticEntity(EntPassive* ent){ vEntityStatic->push_back(ent); }
	void AddActiveEntity(EntActive* ent){ vEntityActive->push_back(ent); }
	void AddColisionableEntity(Colisionable* ent){ vEntityColisionable->push_back(ent); }
	void AddBullet(Bullet* ent){ vBullets->push_back(ent); }
    
    void DeleteBullet(int i){ delete vBullets->at(i);  vBullets->erase(vBullets->begin()+i); }
    

 // HUD
    void SubstractLife(float value){ hud->SubstractLife(value); }
    
    

	Player*		player;
	
	std::vector<Bullet*>		*vBullets;
	std::deque<EntPassive*>		*vEntityStatic;
	std::deque<EntActive*>		*vEntityActive;
	std::deque<Colisionable*>	*vEntityColisionable;
	
private:
	
  // Singleton
	WorldState();
	WorldState(const WorldState& orig);
	virtual ~WorldState();
	static WorldState*	instance;
    
  // Funciones
	void LoadResources();	// Carga recursos, se llama desde Init();
    
	//Eventos
	std::vector<sf::Event>		*vNonRealEvents;
	std::vector<sf::Event>		*vRealEvents;
    
    // HUD
    HUD*     hud;
};

#endif	/* WORLD_H */

