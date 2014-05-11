/* 
 * File:   Enemy.h
 * Author: linuxero
 *
 * Created on March 11, 2014, 9:48 AM
 */
#ifndef ENEMY_H
#define	ENEMY_H

#include "../Animations/Animable.h"
#include "EntActive.h"
#include "../MotorPhysics/Colisionable.h"

class Enemy: public EntActive, public Colisionable, public Animable {
public:
	Enemy(const sf::Texture& tex, const Vector& size);
	Enemy(const sf::Texture& tex, const Vector& size, const Vector& pos, const Vector& vel=Vector(0.f, 0.f), const Vector& maxvel=Vector(550.f, 550.f));
	Enemy(const Enemy& orig);
	virtual ~Enemy();
	
	virtual const std::string GetClassName() { return "Enemy";}
    
    void InitLifebar();
    void RestarLife(float value);
	
	// Bucle de ciclo de vida
    virtual void Draw(RenderWindow& window);
	virtual void Draw(RenderWindow& window, float inter);
	virtual void Update(const Time& elapsedTime);
	
	// Colisiones
	void DoRectangleColisions(const Time& elapsedTime);
	void OnColision(Colision::Type type, const Rectangle& rec, const Time& elapsedTime);
		
	// Movimientos
        /*void MovementLeft();
        void MovementRight();*/
    
	virtual void ResetCan(){ canLeft = canRight = true; }
        
    void routeMove();
	
    
    
	bool canLeft, canRight, canJump;
    int route, changeX, changeY;
    bool intersects, prevIntersects, die, win;
    bool isMoving;
    
    
    
    // PARAMETROS
    Lifebar*    life;
    float attack;
    float price;
    int   type;
    
	
private:
    
    
    float lifebarAddWi, lifebarAddHe, lifebarHe, lifebarLessY;
    
        
        
};

#endif	/* ENEMY_H */

