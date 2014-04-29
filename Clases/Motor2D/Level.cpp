/* 
 * File:   Level.cpp
 * Author: linuxero
 * 
 * Created on March 15, 2014, 9:20 AM
 */

#include "Level.h"
#include "../States/WorldState.h"


Level::Level() {
	vRectColision = new std::deque<Rectangle*>();
    vPlatforms = new std::deque<Rectangle*>();
	vEnemies = new std::deque<Enemy*>();
	vEntPassive = new std::deque<EntPassive*>();
	vTextures = new std::deque<std::string>();
}

Level::Level(const Level& orig) {
}

Level::~Level() {
    while(!vRectColision->empty()) 
		delete vRectColision->back(), vRectColision->pop_back();
	delete vRectColision;
    
    while(!vPlatforms->empty()) 
		delete vPlatforms->back(), vPlatforms->pop_back();
	delete vPlatforms;
    
    while(!vEnemies->empty()) 
		delete vEnemies->back(), vEnemies->pop_back();
	delete vEnemies;
    
    vTextures->clear();
	delete vTextures;
    
    while(!vEntPassive->empty()) 
		delete vEntPassive->back(), vEntPassive->pop_back();
	delete vEntPassive;
    
    delete map;
	
	vRectColision = NULL;
    vPlatforms = NULL;
	vEnemies = NULL;
	vEntPassive = NULL;
	vTextures = NULL;
    map = NULL;
}

void Level::LoadMap(std::string mapName){
    map = new Mapa(WorldState::Instance()->window->renderWindow, mapName);
    map->init();
}