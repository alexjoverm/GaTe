/* 
 * File:   PowerUp.cpp
 * Author: jmsm30
 * 
 * Created on 30 de abril de 2014, 1:53
 */

#include "PowerUp.h"
#include "../States/WorldState.h"


PowerUp::PowerUp(PowerUps::State powerType, const sf::Texture& tex, const Vector& pos, const Vector& vel, const Vector& maxvel): EntActive(tex, pos, vel, maxvel), Colisionable(this) {
    std::srand(time(NULL));
    
    timeAlive = 0;
    lifeTime = rand()%5 + 10;
    powerUpType = powerType;
}

PowerUp::PowerUp(const PowerUp& orig): EntActive(orig), Colisionable((EntActive*)this) {
}

PowerUp::~PowerUp() {
}

bool PowerUp::UpdateBool(const Time& elapsedTime){
    
  timeAlive += elapsedTime.AsSeconds();
  
  if(timeAlive >= lifeTime)
      return true;
  
    ResetLimits();
	DoRectangleColisions(elapsedTime);
	
    // Movimiento en el path
	physicsState->Update(elapsedTime, affectGravity); // Si puede saltar, no se le aplica gravedad (por eso se pone negado)

    return false;

}


// On colision hay que llamar a un metodo del manager para que lo elimine y aplique al jugador el efectoClases/Managers/../Entities/PowerUp.h:23:7: nota:   porque las siguientes funciones virtual son pure dentro de ‘PowerUp’:


void PowerUp::DoRectangleColisions(const Time& elapsedTime){
	WorldState* world = WorldState::Instance();
	
	Colision::Type	type;
	bool colisionado = false, isInFloor = false;
	
	for(int i=0; i < world->level->vRectColision->size(); i++){
		if(CheckColision(*world->level->vRectColision->at(i), elapsedTime)){
			
			// Comprobamos tipo de colision, y hacemos lo que debamos
			type = TypeOfColision(*world->level->vRectColision->at(i), elapsedTime);
			OnColision(type,*world->level->vRectColision->at(i), elapsedTime);
			
			if(type==Colision::Type::BOTTOM && GetSpeed().GetY() >= 0.f)
				isInFloor = true;
			
			colisionado = true;
		}
	}
    
    for(int i=0; i < world->level->vPlatforms->size(); i++){
		if(CheckColision(*world->level->vPlatforms->at(i), elapsedTime)){
			
			// Comprobamos tipo de colision, y hacemos lo que debamos
			type = TypeOfColision(*world->level->vPlatforms->at(i), elapsedTime);
            
            if(type==Colision::Type::BOTTOM){
                OnColision(type,*world->level->vPlatforms->at(i), elapsedTime);
				isInFloor = true;
                colisionado = true;
            }
		}
	}
    
        
	affectGravity = !isInFloor;
}

void PowerUp::OnColision(Colision::Type type, const Rectangle& rec, const Time& elapsedTime){
	
	// Movemos al borde
	MoveToEdge(type, rec, elapsedTime);
}