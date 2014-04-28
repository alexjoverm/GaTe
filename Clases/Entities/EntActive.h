/* 
 * File:   EntActive.h
 * Author: linuxero
 *
 * Created on March 11, 2014, 9:44 AM
 */

#ifndef ENTACTIVE_H
#define	ENTACTIVE_H

#include "Entity.h"
#include "../Motor2D/RenderState.h"

#include "../HUD/Lifebar.h"
#include "../MotorPhysics/PhysicsState.h"

class EntActive: public Entity {
public:
	EntActive(const sf::Texture& tex);
	EntActive(const sf::Texture& tex, const Vector& pos, const Vector& vel=Vector(0.f, 0.f), const Vector& maxvel=Vector(550.f, 550.f));
	EntActive(const EntActive& orig);
	virtual ~EntActive();
	
	virtual void Draw(RenderWindow& window, float inter); ///< Realiza un Draw Interpolado
	virtual void Update(const Time& elapsedTime); ///< Realizará un Update de la física, además el propio en las clases hijas
	

	
//******** FISICAS
// Getters
	Vector& GetPosition() const{ return physicsState->GetPosition(); }
    Vector& GetPreviousPosition() const{ return physicsState->GetPreviousPosition(); }
    Vector& GetPreviousSpeed() const{ return physicsState->GetPreviousSpeed(); }
	Vector& GetSpeed() const{ return physicsState->GetSpeed(); }
	Vector& GetMaxSpeed() const{ return physicsState->GetMaxSpeed(); }
	Vector& GetGravity() const{ return physicsState->GetGravity(); }
	

	
// Setters
	void SetPosition(float x, float y){ physicsState->SetPosition(x, y); }
	void SetPosition(const Vector& v){ physicsState->SetPosition(v); }
	void SetNextPosition(float x, float y){ physicsState->SetNextPosition(x, y); }
	void SetNextPosition(const Vector& v){ physicsState->SetNextPosition(v); }
	void SetSpeed(float x, float y){ physicsState->SetSpeed(x, y); }
	void SetSpeed(const Vector& v){ physicsState->SetSpeed(v); }
	void SetMaxSpeed(float x, float y){ physicsState->SetMaxSpeed(x, y); }
	void SetMaxSpeed(const Vector& v){ physicsState->SetMaxSpeed(v); }
	void SetGravity(const Vector& g){ physicsState->SetGravity(g); }
	
    void SetBottomLimited(bool value){ physicsState->hasLimitBottom = value; }
    void SetTopLimited(bool value)   { physicsState->hasLimitTop = value; }
    void SetLeftLimited(bool value)  { physicsState->hasLimitLeft = value; }
    void SetRightLimited(bool value) { physicsState->hasLimitRight = value; }
    
    void SetBottomLimitValue(float value){ physicsState->limitBottom = value; }
    void SetTopLimitValue(float value)   { physicsState->limitTop = value; }
    void SetLeftLimitValue(float value)  { physicsState->limitLeft = value; }
    void SetRightLimitValue(float value) { physicsState->limitRight = value; }
    
    void ResetLimits() { physicsState->ResetLimits(); }
    
 // Render
    Vector& GetRenderPosition() const{ return renderState->GetRenderPosition(); }
    
	float	factorSpeed = 400.f;
	float	factorSpeedIni = factorSpeed;
	float	factorGravity = 1000.f;
	bool	affectGravity = true;
    bool    isReverse = false, isPrevReverse=false;
	
protected:
	PhysicsState*	physicsState;
	RenderState*	renderState;

};

#endif	/* ENTACTIVE_H */

