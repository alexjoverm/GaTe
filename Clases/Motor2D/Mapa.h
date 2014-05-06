/* 
 * File:   Mapa.h
 * Author: jmsm30
 *
 * Created on 19 de marzo de 2014, 11:00
 */

#ifndef MAPA_H
#define	MAPA_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "MapLoader/MapLoader.h"
#include "../Otros/Rectangle.h"
#include "../Otros/Vector.h"
#include "../Entities/Player.h"

class Mapa {
    
public:
    Mapa(sf::RenderWindow* win, std::string fileName);
    Mapa(sf::RenderWindow* win, std::string fileName,const Mapa& orig);
    virtual ~Mapa();

    tmx::MapLoader*                     GetMap();
    tmx::MapLayer                       GetLayer(std::string layerName);
    std::vector<tmx::MapObject>         GetLayerObjects(std::string layerName);
    std::vector<Rectangle*>             GetLayerCollitions(std::string layerName);
    
    void                                Init();
    
    void                                Render();
    void                                RenderMiniMap();
    
    void                                LoadPath();
    void                                LoadAnimations();
    
    Vector*                             GetMapSize(){ return new Vector(map.GetMapSize().x,map.GetMapSize().y);}
    std::string                         GetMetadata(std::string dataName);
    std::string                         GetLayerData(std::string layerName , std::string dataName);
    std::string                         GetObjectData(std::string layerName ,int objectNumber , std::string dataName);
    
private:
    
    
    sf::RenderWindow*                   window;
    tmx::MapLoader                      map;    
    
};

#endif	/* MAPA_H */

