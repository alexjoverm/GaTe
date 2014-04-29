/* 
 * File:   EntActive.cpp
 * Author: linuxero
 * 
 * Created on March 11, 2014, 9:44 AM
 */
#include <iostream>
#include "EntActive.h"

EntActive::EntActive(const sf::Texture& tex): Entity(tex) {
	renderState = new RenderState();
	physicsState = new PhysicsState();
}

EntActive::EntActive(const sf::Texture& tex, const Vector& pos, const Vector& vel, const Vector& maxvel): Entity(tex) {
	renderState = new RenderState();
	physicsState = new PhysicsState(pos, vel, maxvel, Vector(0.f, factorGravity));
}

EntActive::EntActive(const EntActive& orig): Entity(orig) {
}

EntActive::~EntActive() {
	delete renderState;
	renderState = NULL;
	
	delete physicsState;
	physicsState = NULL;
	
}


/// Dibujado con interpolacion
void EntActive::Draw(RenderWindow& window){
     renderState->Draw(window, *this->spriteSheet);
}

void EntActive::Draw(RenderWindow& window, float inter){
	renderState->Draw(window, physicsState->GetPreviousPosition(), physicsState->GetPosition(), inter, *this->spriteSheet);
}


void EntActive::Update(const Time& elapsedTime){
	//physicsState->Update(elapsedTime, affectGravity);
}
