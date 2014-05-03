/* 
 * File:   Paralax.cpp
 * Author: jmsm30
 * 
 * Created on 7 de mayo de 2014, 18:41
 */

#include "Paralax.h"
#include "Camera.h"

Paralax::Paralax(Camera* camReference, Mapa* mapReference) {
  
    cam = camReference;
    window = cam->GetRenderWindow();
    paralax1 = paralax2 = paralax3 = cam->standard;
    map = mapReference;

}

Paralax::Paralax(const Paralax& orig) {
}

Paralax::~Paralax() {
}

void Paralax::Update(const Time& elapsedTime){
   
}

void Paralax::Render(float interpolation){


    Vector *aux = cam->GetVelCam();
    Vector *aux2 = cam->GetMoved();

    paralax1.move(aux->GetX()*aux2->GetX(),aux->GetY()*aux2->GetY());
    paralax2.move(0.75*aux->GetX()*aux2->GetX(),aux->GetY()*aux2->GetY());
    paralax3.move(0.5*aux->GetX()*aux2->GetX(),aux->GetY()*aux2->GetY());
    
    window->setView( paralax1 );
    window->draw(map->GetLayer("Fondo"));
    
    window->setView( paralax3 );
    window->draw(map->GetLayer("Paralax3"));
    
    window->setView( paralax2 );
    window->draw(map->GetLayer("Paralax2"));
    
    window->setView( paralax1 );
    window->draw(map->GetLayer("Paralax1"));
    
    
}
