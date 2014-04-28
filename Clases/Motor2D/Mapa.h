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

    tmx::MapLoader*                     getMap();
    tmx::MapLayer                       getLayer(std::string layerName);
    std::vector<tmx::MapObject>         getLayerObjects(std::string layerName);
    std::vector<Rectangle*>             getLayerCollitions(std::string layerName);
    
    void                                init();
    
    
    void                                render();
    void                                renderMiniMap();  
    
    Vector*                              getMapSize(){ return new Vector(map.GetMapSize().x,map.GetMapSize().y);}
    
    
private:
    
    
    sf::RenderWindow*           window;
    
    tmx::MapLoader              map;
    
    
};

#endif	/* MAPA_H */

