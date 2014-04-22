/* 
 * File:   Enemy.cpp
 * Author: linuxero
 * 
 * Created on March 11, 2014, 9:48 AM
 */

#include "Enemy.h"
#include "../States/WorldState.h"

Enemy::Enemy(const sf::Texture& tex): EntActive(tex), Colisionable((EntActive*)this) {
	canLeft = canRight = true;
	canJump = false;
}


Enemy::Enemy(const sf::Texture& tex, const Vector& pos, const Vector& vel, const Vector& maxvel): EntActive(tex, pos, vel, maxvel), Colisionable(this){
	canLeft = canRight = true;
	canJump = false;
}

Enemy::Enemy(const Enemy& orig): EntActive(orig), Colisionable((EntActive*)this) {
}

Enemy::~Enemy() {
}


void Enemy::Jump(){
	if(canJump)
	{
		this->SetSpeed(this->GetSpeed().GetX(), -forceJump);
		canJump=false;
	}
}


// ******* COLISIONES

void Enemy::DoRectangleColisions(const Time& elapsedTime){
	WorldState* world = WorldState::Instance();
	
	Colision::Type	type;
	bool colisionado = false, isInFloor = false;
	
	for(int i=0; i < world->level->vRectColision->size(); i++){
		if(CheckColision(*world->level->vRectColision->at(i), elapsedTime)){
			
			// Comprobamos tipo de colision, y hacemos lo que debamos
			type = TypeOfColision(*world->level->vRectColision->at(i), elapsedTime);
			OnColision(type,*world->level->vRectColision->at(i), elapsedTime);
			
			if(type==Colision::Type::BOTTOM)
				isInFloor = true;
			
			colisionado = true;
		}
	}
	if(!isInFloor || !colisionado){
		canJump = false;
	}
	affectGravity = !canJump;
}

void Enemy::OnColision(Colision::Type type, const Rectangle& rec, const Time& elapsedTime){
	
    if(type==Colision::Type::LEFT)
        canRight = false;
    else if(type==Colision::Type::RIGHT)
        canLeft = false;
	
	// Movemos al borde
	MoveToEdge(type, rec, elapsedTime);
}




void Enemy::Draw(RenderWindow& window, float inter){
	renderState->Draw(window, physicsState->GetPreviousPosition(), physicsState->GetPosition(), inter, *this->spriteSheet);
}


void Enemy::Update(const Time& elapsedTime){
	// COLISIONES
	ResetCan();
    ResetLimits();
	DoRectangleColisions(elapsedTime);
	
	physicsState->Update(elapsedTime, affectGravity); // Si puede saltar, no se le aplica gravedad (por eso se pone negado)
	//UpdateRectangle(elapsedTime);
}
