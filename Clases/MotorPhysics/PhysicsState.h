/* 
 * File:   PhysicsState.h
 * Author: linuxero
 *
 * Created on March 5, 2014, 8:32 AM
 */

#ifndef PHYSICSSTATE_H
#define	PHYSICSSTATE_H

#include <SFML/Graphics.hpp>
#include "../Otros/Vector.h"
#include "../Otros/Time.h"

class PhysicsState {
public:
	PhysicsState();
	PhysicsState(const Vector& pos, const Vector& vel, const Vector& maxvel, const Vector& grav);
	PhysicsState(const PhysicsState& orig);
	virtual ~PhysicsState();
	
// GETTERS
	Vector& GetPreviousPosition() const { return *posPrev; }
	Vector& GetPosition() const { return *posNext; }
	Vector GetNextPosition(const Time& elapsedTime) const;
	
	Vector& GetSpeed() const { return *speed; }
	Vector& GetPreviousSpeed() const { return *speedPrev; }
	Vector& GetMaxSpeed() const { return *maxSpeed; }
	
	Vector& GetGravity() const { return *gravity; }
	
// SETTERS
	void SetPosition(float x, float y){ posPrev->Set(x,y);	posNext->Set(x,y);}
	void SetPosition(const Vector& po){ *posPrev = po;		*posNext = po; }
	
	void SetPreviousPosition(float x, float y){ posPrev->Set(x,y);}
	void SetPreviousPosition(const Vector& po){ *posPrev = po;}
	
	void SetNextPosition(float x, float y){ posNext->Set(x,y);}
	void SetNextPosition(const Vector& po){ *posNext = po; }
	
	void SetSpeed(float x, float y){ speed->Set(x, y);	speedPrev->Set(x, y);}
	void SetSpeed(const Vector& sp){ *speed = sp;		*speedPrev = sp; }

	void SetMaxSpeed(float x, float y){ maxSpeed->Set(x,y); }
	void SetMaxSpeed(const Vector& sp){ *maxSpeed = sp; }
	
	void SetGravity(const Vector& gr){ *gravity = gr; }
	
	
// Función que se encarga de realizar las operaciones
	void Update(const Time& elapsedTime, bool affectGravity);
	
 // Limites
    void ResetLimits(){ hasLimitLeft = hasLimitRight = hasLimitBottom = hasLimitTop = false; }   
    

    
private:
	Vector*		posPrev;
	Vector*		posNext;
	
	Vector*		speed;
	Vector*		speedPrev;
	Vector*		maxSpeed;
	
	Vector*		gravity;

public:
    bool hasLimitLeft=false, hasLimitRight=false, hasLimitBottom=false, hasLimitTop=false;
    float limitLeft=0.f, limitRight=0.f, limitBottom=0.f, limitTop=0.f;

};



#endif	/* PHYSICSSTATE_H */

