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
    //void InitMove();
    
    void Move(float numberOfSeconds);
    void Move(Vector velChar, Vector posChar);
    void Move(float velX, float velY, float posCharX, float posCharY);
    void MoveMinimap();
    void MoveMinimap(float x , float y , float charx , float chary);
    
    void Update();
    
    void SetCurrentView(Views::Type view);
    sf::View* GetCurrentView();
    sf::View* GetView(Views::Type view);
    
    void SetToPlayer(Player* player){pl = player;}
    
    sf::RectangleShape* GetMiniback(){return miniback;}
    
    bool minimapActive = true;
    
    sf::View                    fixed;
    sf::View                    standard;
    sf::View                    minimap;
    
private:

    Player*                     pl;
    Vector*                     prevPosPlayer;
    
    Views::Type                 currentView;
    sf::RenderWindow*           window;
   
    Vector                      mapSize;
    
    sf::RectangleShape*         miniback;
    
    sf::FloatRect               topRect;
    sf::FloatRect               leftRect;
    sf::FloatRect               bottomRect;
    sf::FloatRect               rightRect;
    
};

#endif	/* CAMERA_H */

