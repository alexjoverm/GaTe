/* 
 * File:   Enemy.h
 * Author: linuxero
 *
 * Created on March 11, 2014, 9:48 AM
 */
#ifndef ENEMY_H
#define	ENEMY_H

#include "EntActive.h"
#include "../MotorPhysics/Colisionable.h"

class Enemy: public EntActive, public Colisionable {
public:
	Enemy(const sf::Texture& tex);
	Enemy(const sf::Texture& tex, const Vector& pos, const Vector& vel=Vector(0.f, 0.f), const Vector& maxvel=Vector(550.f, 550.f));

	Enemy(const Enemy& orig);
	virtual ~Enemy();
	
	virtual const std::string GetClassName() { return "Enemy";}
    
    void InitLifebar();
    void RestarLife(float value);
	
	// Bucle de ciclo de vida
	virtual void Draw(RenderWindow& window, float inter);
	virtual void Update(const Time& elapsedTime);
	
	// Colisiones
	void DoRectangleColisions(const Time& elapsedTime);
	void OnColision(Colision::Type type, const Rectangle& rec, const Time& elapsedTime);
		
	
    
	virtual void ResetCan(){ canLeft = canRight = true; }
        
    void routeMove();
	
	
	float forceJump = 500.f;
    float attack = 10.f;
    
	bool canLeft, canRight, canJump;
    int route, changeX, changeY;
    bool intersects, prevIntersects, die, win;
    
    Lifebar*    life;
	
private:
	void Jump();
    
    
    float lifebarAddWi, lifebarAddHe, lifebarHe, lifebarLessY;
    
        
        
};

#endif	/* ENEMY_H */

