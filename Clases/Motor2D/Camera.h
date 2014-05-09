/* 
 * File:   Camera.h
 * Author: jmsm30
 *
 * Created on 24 de abril de 2014, 20:43
 */

#ifndef CAMERA_H
#define	CAMERA_H

#include "RenderWindow.h"
#include "../Entities/Player.h"
#include "../Otros/Vector.h"


namespace Views{
	enum Type{
            Standard,Fixed,Minimap
	};
}

class Camera {
public:
    
    Camera(sf::RenderWindow* win);
    Camera(const Camera& orig);
    virtual ~Camera();
    
    void Init(Player* player);

    void Move(float velX, float velY, float posCharX, float posCharY, Player* player);
    void MoveMinimap(float x , float y , float charx , float chary, Player* player);
    
    void Update(Player* pl);
    void Render(Player* pl);
    void Render(float interp, Player* pl);
    
    void SetCurrentView(Views::Type view);
    sf::View* GetCurrentView();
    sf::View* GetView(Views::Type view);
    
    Vector* GetMoved(){ return moved;}
    
    Vector* GetVelCam(){ return pos; }

    sf::RenderWindow* GetRenderWindow(){ return window; }
    
    sf::RectangleShape* GetMiniback(){return miniback;}
    
    bool minimapActive = true;
    
    sf::View                    fixed;
    sf::View                    standard;
    sf::View                    minimap;
    
private:
    Vector                     *posPrev, *posNext, *posRender, *posRenderPrev,*moved, *pos;
    
    Views::Type                 currentView;
    sf::RenderWindow*           window;
   
    Vector*                      mapSize;
    
    sf::RectangleShape*         miniback;
    
    Rectangle*                topRect;
    Rectangle*                leftRect;
    Rectangle*                bottomRect;
    Rectangle*                rightRect;
    
};

#endif	/* CAMERA_H */

