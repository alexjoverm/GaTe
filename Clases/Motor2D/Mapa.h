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
    
    void                                move(float x , float y , float charx , float chary);
    void                                move(sf::Vector2f vf , float charx , float chary);
    void                                moveMiniMap(float x , float y , float charx , float chary);
    
    void                                init();
    void                                initMiniMap(); 
    
    void                                update(Player* pl, float interpolation);
    
    void                                render(bool miniMapEnable = false);
    void                                renderMiniMap();    
    
    
private:
    
    sf::RenderWindow*           window;
    
    tmx::MapLoader              map;
    
    sf::View                    fixed;
    sf::View                    standard;
    sf::View                    minimap;
    
    sf::RectangleShape          miniback;
    
    sf::FloatRect               topRect;
    sf::FloatRect               leftRect;
    sf::FloatRect               bottomRect;
    sf::FloatRect               rightRect;
    
};

#endif	/* MAPA_H */

