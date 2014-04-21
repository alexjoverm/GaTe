/* 
 * File:   PhysicsState.cpp
 * Author: linuxero
 * 
 * Created on March 5, 2014, 8:32 AM
 */
#include "PhysicsState.h"
#include "../Otros/Vector.h"
#include "../Otros/StringUtils.h"
#include <iostream>

PhysicsState::PhysicsState() 
{
	posNext = new Vector();
	posPrev = new Vector();
	maxSpeed = new Vector();
	speed = new Vector();
	speedPrev = new Vector();
	gravity = new Vector();
    

}

PhysicsState::PhysicsState(const Vector& pos, const Vector& vel, const Vector& maxvel, const Vector& grav){
	
	posNext = new Vector(pos.GetX(), pos.GetY());
	posPrev = new Vector(pos.GetX(), pos.GetY());
	maxSpeed = new Vector(maxvel.GetX(), maxvel.GetY());
	
	speed = new Vector(vel.GetX(), vel.GetY());
	speedPrev = new Vector(vel.GetX(), vel.GetY());
	
	gravity = new Vector(grav.GetX(), grav.GetY());
    
}

PhysicsState::PhysicsState(const PhysicsState& orig) {
}
PhysicsState::~PhysicsState() {
	delete posNext;
	delete posPrev;
	delete maxSpeed;
	delete speed;
	delete speedPrev;
	delete gravity;
	
	posNext = NULL;
	posPrev = NULL;
	maxSpeed = NULL;
	speed = NULL;
	speedPrev = NULL;
	gravity = NULL;
}


Vector PhysicsState::GetNextPosition(const Time& elapsedTime) const{
	return Vector(
			posNext->GetX() + ((speedPrev->GetX() + speed->GetX()) * 0.5f * elapsedTime.AsSeconds()) ,
			posNext->GetY() + ((speedPrev->GetY() + speed->GetY()) * 0.5f * elapsedTime.AsSeconds())
		);
}




void PhysicsState::Update(const Time& elapsedTime, bool affectGravity)
{
	*speedPrev = *speed;
	
	
	if(affectGravity)
	{
		// Limitación de velocidades en X
		if(gravity->GetX() > 0){
			if(speed->GetX() < maxSpeed->GetX())
				speed->SetX(speed->GetX()  +  gravity->GetX() * elapsedTime.AsSeconds());
		}

		else if(gravity->GetX() < 0){
			if(speed->GetX() > -maxSpeed->GetX())
				speed->SetX(speed->GetX()  +  gravity->GetX() * elapsedTime.AsSeconds());
		}

		// Limitación de velocidades en Y
		if(gravity->GetY() > 0){
			if(speed->GetY() < maxSpeed->GetY())
				speed->SetY(speed->GetY()  +  gravity->GetY() * elapsedTime.AsSeconds());
		}

		else if(gravity->GetY() < 0){
			if(speed->GetY() > -maxSpeed->GetY())
				speed->SetY(speed->GetY()  +  gravity->GetY() * elapsedTime.AsSeconds());
		}
		
		// Si nos pasamos de velocidades, reigualamos
		if(speed->GetX() > maxSpeed->GetX())
			speed->SetX(maxSpeed->GetX());
		if(speed->GetY() > maxSpeed->GetY())
			speed->SetY(maxSpeed->GetY());
		
	}
    
    *posPrev = *posNext;
    posNext->SetX(posNext->GetX() + ((speed->GetX() + speedPrev->GetX()) * 0.5f * elapsedTime.AsSeconds()));
    posNext->SetY(posNext->GetY() + ((speed->GetY() + speedPrev->GetY()) * 0.5f * elapsedTime.AsSeconds()));
    
            // Limites
    if(hasLimitBottom && posNext->GetY() > limitBottom){
        posNext->SetY(limitBottom);
        posPrev->SetY(limitBottom);
        speed->SetY(0.f);
    }
    if(hasLimitTop && posNext->GetY() < limitTop){
        posNext->SetY(limitTop);
        posPrev->SetY(limitTop);
        speed->SetY(0.f);
    }
    if(hasLimitRight && posNext->GetX() > limitRight){
        posNext->SetX(limitRight);
        posPrev->SetX(limitRight);
    }
        
    if(hasLimitLeft && posNext->GetX() < limitLeft) {   
        posNext->SetX(limitLeft);
        posPrev->SetX(limitLeft);
    }
}
