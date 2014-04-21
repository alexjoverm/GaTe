/* 
 * File:   World.h
 * Author: linuxero
 *
 * Created on March 15, 2014, 10:40 AM
 */

#ifndef WORLD_H
#define	WORLD_H

#include "Level.h"
#include "../Entities/Player.h"
#include "../Entities/Bullet.h"
#include "RenderWindow.h"
#include "../Otros/Clock.h"
#include "../Entities/EntActive.h"
#include "../Managers/InputManager.h"
#include "../Managers/ResourceManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>


// ID's para cargar fuentes (usar con Fonts::ID)
namespace Fonts{
	enum ID{
		OpenSans
	};
}


namespace Bullets{
	enum Type{
		Default
	};
}



class World {
public:
	static World* Instance(); // Singleton

// Inicialización
	void Init();
    
// Liberación
	
    
// 3 bucles principales
	void Run();
	void Update(const Time& timeElapsed);
	void Render(float interp);
	
// Eventos
	void MoveEvents(); // Le pasa al InputManager los eventos
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

	Player*		player;
	
	std::vector<Bullet*>		*vBullets;
	std::deque<EntPassive*>		*vEntityStatic;
	std::deque<EntActive*>		*vEntityActive;
	std::deque<Colisionable*>	*vEntityColisionable;
	sf::Text			textColision, textPlayerSpeed;
	
	// Graficos
	RenderWindow*	window;
	
private:
	
  // Singleton
	World();
	World(const World& orig);
	virtual ~World();
	static World*	instance;
    
  // Funciones
	void LoadResources();	// Carga recursos, se llama desde Init();
    
//****** VARIABLES
	Time*       timeUpdate;  //Será 1/15 (15 veces por segundo)

	ResourceManager*    resourceManager;   
    
	//Eventos
	std::vector<sf::Event>		*vNonRealEvents;
	std::vector<sf::Event>		*vRealEvents;
	InputManager*				inputManager;
};

#endif	/* WORLD_H */

