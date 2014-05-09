/* 
 * File:   PowerUp.h
 * Author: jmsm30
 *
 * Created on 30 de abril de 2014, 1:53
 */

#ifndef POWERUP_H
#define	POWERUP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "EntActive.h"
#include "../MotorPhysics/Colisionable.h"


namespace PowerUps{
    enum State{
        Damage,Speed,Jump,SpeedShot,DoubleJump,AngleShoot
    };
}

class PowerUp : public EntActive, public Colisionable {
public:
    PowerUp(PowerUps::State powerType,const sf::Texture& tex, const Vector& pos, const Vector& vel=Vector(0.f, 0.f), const Vector& maxvel=Vector(600.f, 600.f));
    PowerUp(const PowerUp& orig);
    virtual ~PowerUp();
    
    PowerUps::State GetType(){return powerUpType;}
    bool UpdateBool(const Time& elapsedTime);
    
    void DoRectangleColisions(const Time& elapsedTime);
    void OnColision(Colision::Type type, const Rectangle& rec, const Time& elapsedTime);
    
    
private:
    
    PowerUps::State     powerUpType;
    float               lifeTime;
    float               timeAlive;

};

#endif	/* POWERUP_H */

