/* 
 * File:   Level.h
 * Author: linuxero
 *
 * Created on March 15, 2014, 9:20 AM
 */

#ifndef LEVEL_H
#define	LEVEL_H

#include "../Otros/Rectangle.h"
#include "../Entities/Enemy.h"
#include "../Entities/EntPassive.h"
#include <deque>
#include <SFML/Graphics.hpp>
#include "Mapa.h"

class Level {
public:
	Level();
	Level(const Level& orig);
	virtual ~Level();
	
	void AddColision(Rectangle* rec){ vRectColision->push_back(rec); };
	void AddEnemy(Enemy* ene){ vEnemies->push_back(ene); };
	void AddTextureFile(const std::string& tex){ vTextures->push_back(tex); };
	void AddEntPassive(EntPassive* ent){ vEntPassive->push_back(ent); };
    
    void LoadMap(std::string mapName);
	
//Variables public para que sean accesibles
public:
	// metodos para deque : at(i), pop/push_back() , pop/push_front(), size(), clear(), empty()
	std::deque<Rectangle*>		*vRectColision;
	std::deque<Enemy*>			*vEnemies;
	std::deque<EntPassive*>		*vEntPassive;
	std::deque<std::string>		*vTextures;
    Mapa                        *map;
};

#endif	/* LEVEL_H */

