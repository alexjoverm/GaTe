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
    
    lifebarAddWi = 20.f;
    lifebarAddHe = 20.f;
    
    intersects = prevIntersects = win = die = false;
    changeX = changeY = 1;
}


Enemy::Enemy(const sf::Texture& tex, const Vector& pos, const Vector& vel, const Vector& maxvel): EntActive(tex, pos, vel, maxvel), Colisionable(this){
	canLeft = canRight = true;
	canJump = false;
    route = 1;

    factorSpeed = 300.f;
    
    lifebarAddWi = 20.f;
    lifebarAddHe = 20.f;
    
    intersects = prevIntersects = win = die = false;
    changeX = changeY = 1;
}

Enemy::Enemy(const Enemy& orig): EntActive(orig), Colisionable((EntActive*)this) {
}

Enemy::~Enemy() {
    delete life; life=NULL;
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
    
    //Sacamos direccion en X
    if( this->GetSpeed().GetX() < 0)
        right = false;
    //Sacamos direccion en Y
    if(this->GetSpeed().GetY() > 0)
        top = false;
    
    
    Vector* auxRoute = WorldState::Instance()->vPath->at(route);
    
    prevIntersects = intersects;
    
    if(GetRectangleColisionAbsolute().IsInside(*auxRoute))
        intersects = true;
    else
        intersects = false;
    
    
    if(!intersects)
    {
        if(auxRoute->GetX() < GetPosition().GetX())
            changeX = -1;
        else
            changeX = 1;
    }
    
    
   if(canJump)
       this->SetSpeed( factorSpeed*changeX , GetSpeed().GetY() );
    else
       this->SetSpeed(0.0f , GetSpeed().GetY() );
    
    
    
    // Comprobamos la posicion y si se intersecta con el punto.
    if( !intersects && prevIntersects ) {
        route++;
        // Si el punto es el ultimo
        if(route >= WorldState::Instance()->vPath->size()){
            win=true;
        }
    }

}



void Enemy::Draw(RenderWindow& window, float inter){
	renderState->Draw(window, physicsState->GetPreviousPosition(), physicsState->GetPosition(), inter, *this->spriteSheet);
    
    float x = renderState->GetRenderPosition().GetX() - lifebarAddWi/2;
    float y = renderState->GetRenderPosition().GetY() - lifebarHe - lifebarAddWi;
    
    life->SetPosition(x,y);
    life->Draw(window, inter);
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
    
    life->Update(elapsedTime);
}



void Enemy::InitLifebar()
{
    float wi = GetRectangleColisionAbsolute().GetWidth() + lifebarAddWi;
    lifebarHe = 10.f;
    float x = GetRectangleColisionAbsolute().GetTopLeft().GetX() - lifebarAddWi/2;
    float y = GetRectangleColisionAbsolute().GetTopLeft().GetY() - lifebarHe - 20.f;
    
    life = new Lifebar(x, y, wi, lifebarHe, 1);
}

void Enemy::RestarLife(float value){
    life->Restar(value);
    if(life->valor == 0.f)
        die=true;
}