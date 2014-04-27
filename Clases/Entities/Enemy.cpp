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
    route = 1;

    factorSpeed = 300.f;
}


Enemy::Enemy(const sf::Texture& tex, const Vector& pos, const Vector& vel, const Vector& maxvel): EntActive(tex, pos, vel, maxvel), Colisionable(this){
	canLeft = canRight = true;
	canJump = false;
    route = 1;

    factorSpeed = 300.f;
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
	if(!isInFloor || !colisionado)
		canJump = false;
	else if(isInFloor)
		canJump = true;
        
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


// MOVIMIENTO

void Enemy::routeMove(){

    
    
    // Comprobamos su direccion, si va a la derecha o arriba
    bool right = true, top = true;
    int changeX = 1 , changeY = 1;
    
    //Sacamos direccion en X
    if( this->GetSpeed().GetX() < 0)
        right = false;
    //Sacamos direccion en Y
    if(this->GetSpeed().GetY() > 0)
        top = false;
    
    std::cout <<right<<" , " << top << " , " << route <<std::endl;
    
    Vector* auxRoute = WorldState::Instance()->vPath->at(route);
    
    // Si va a la derecha y tiene que ir a la izquierda cambiamos de direccion en X
    if(auxRoute->GetX() < this->GetPosition().GetX() || (auxRoute->GetX() - this->GetPosition().GetX()) > this->spriteSheet->getGlobalBounds().GetWidth() + 25.f ) 
        changeX = -1;
    
   if(canJump)
       this->SetSpeed( factorSpeed*changeX , GetSpeed().GetY() );
    else
       this->SetSpeed(0.0f , GetSpeed().GetY() );
    
    
    
    // Comprobamos la posicion y si se intersecta con el punto.
    if( this->spriteSheet->getGlobalBounds().IsInside( *auxRoute ) && route < WorldState::Instance()->vPath->size() ) {
        route++;
        // Si el punto es el ultimo
        if(route >= WorldState::Instance()->vPath->size()){
           // Lo eliminamos 
            route--;
            std::cout << " Hemos eliminado este Enemigo por llegar al final, Falta por implementar" << std::endl;
        }
    }

}



void Enemy::Draw(RenderWindow& window, float inter){
	renderState->Draw(window, physicsState->GetPreviousPosition(), physicsState->GetPosition(), inter, *this->spriteSheet);
}


void Enemy::Update(const Time& elapsedTime){
	

        
        // COLISIONES
	ResetCan();
        ResetLimits();
	DoRectangleColisions(elapsedTime);
	
        // Movimiento en el path
        routeMove();
	physicsState->Update(elapsedTime, affectGravity); // Si puede saltar, no se le aplica gravedad (por eso se pone negado)
	//UpdateRectangle(elapsedTime);
}
