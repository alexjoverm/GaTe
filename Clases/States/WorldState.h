/* 
 * File:   World.h
 * Author: linuxero
 *
 * Created on March 15, 2014, 10:40 AM
 */

#ifndef WORLDSTATE_H
#define	WORLDSTATE_H

#include "../Motor2D/RenderWindow.h"
#include "../Motor2D/Level.h"
#include "../Motor2D/Camera.h"
#include "../Motor2D/Paralax.h"
#include "../Entities/EntActive.h"
#include "../Entities/Player.h"
#include "../Entities/Bullet.h"
#include "../Entities/PowerUp.h"
#include "../Entities/Tower.h"
#include "../Managers/InputManager.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/WaveManager.h"
#include "../Managers/PowerUpManager.h"
#include "../MusicSounds/MusicPlayer.h"
#include "../HUD/HUD.h"
#include "../Otros/Clock.h"
#include "../Otros/TemporalChange.h"
#include "State.h"
#include <SFML/Graphics.hpp>
#include <iostream>



class WorldState: public State {
public:
	static WorldState* Instance(); // Singleton

// Inicialización y Liberación
	void Init();
    void Clean();
    void LoadResources();
    
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
    void AddLevelPlatform(Rectangle* rec){ level->AddPlatform(rec); }
    
    void AddLevelTexture(const std::string tex){ level->AddTextureFile(tex); }
    
    void AddTrace(Vector* ent){ vPath->push_back(ent); }
   Level*		level;
 
// Entities
	void AddStaticEntity(EntPassive* ent){ vEntityStatic->push_back(ent); }
	void AddActiveEntity(EntActive* ent){ vEntityActive->push_back(ent); }
	void AddColisionableEntity(Colisionable* ent){ vEntityColisionable->push_back(ent); }
	void AddBullet(Bullet* ent){ vBullets->push_back(ent); }
    
    void AddTower(Tower* ent){ vTowers->push_back(ent); }
    void AddEnemy(Enemy* ent){ vEnemies->push_back(ent); }
    void AddPowerUp(PowerUp* ent){ vPowers->push_back(ent); }
    void AddTemporalChange(TemporalChange* ent){vChanges->push_back(ent);}
 
    void DeleteEnemy(int i);
    void DeleteBullet(int i);
    void DeletePowerUp(int i);
    void DeleteTemporalChange(int i);


    
    void CleanArrays(Enemy* en);
    

 // HUD
    void SubstractLife(float value){ hud->SubstractLife(value); }
    Camera* GetCamera(){ return cam;}
    

	Player*		player;
	
    std::vector<Vector*>		*vPath;
    std::vector<Tower*>         *vTowers;
    std::vector<PowerUp*>       *vPowers;
    std::deque<Enemy*>          *vEnemies;
    std::vector<TemporalChange*>        *vChanges;
	std::vector<Bullet*>		*vBullets;
	std::deque<EntPassive*>		*vEntityStatic;
	std::deque<EntActive*>		*vEntityActive;
	std::deque<Colisionable*>	*vEntityColisionable;
	
    bool      showTowerRange;
	
    // HUD
    HUD*     hud;
    
    std::string         mapName;
    
    
private:
	
  // Singleton
	WorldState();
	WorldState(const WorldState& orig);
	virtual ~WorldState();
	static WorldState*	instance;

	//Eventos
	std::vector<sf::Event>		*vNonRealEvents;
	std::vector<sf::Event>		*vRealEvents;
    
    // PowerUp Manager
    PowerUpManager*      powerUpManager;
    
    // WaveManager
    WaveManager*    waveManager;
    
    //Players
    MusicPlayer*         musicPlayer;
    SoundPlayer*         soundPlayer;
    
    // Paralax
    Paralax*             paralax;
    
    bool     firstUpdate;
    
    // Camera
    Camera*  cam;
};

#endif	/* WORLD_H */

