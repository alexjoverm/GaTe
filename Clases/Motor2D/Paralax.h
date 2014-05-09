/* 
 * File:   Paralax.h
 * Author: jmsm30
 *
 * Created on 7 de mayo de 2014, 18:41
 */

#ifndef PARALAX_H
#define	PARALAX_H

#include "MapLoader/MapLoader.h"
#include "Mapa.h"
#include "../Otros/Time.h"
#include "Camera.h"


class Paralax {
public:
    Paralax(Camera* camReference, Mapa* mapReference);
    Paralax(const Paralax& orig);
    virtual ~Paralax();
    
    void Update(const Time& elapsedTime);
    void Render(float interpolation);
    
private:

    sf::RenderWindow*   window;
    
    Camera*             cam;
    
    sf::View            paralax1,paralax2,paralax3;
    
    Mapa*               map;
    
};

#endif	/* PARALAX_H */

