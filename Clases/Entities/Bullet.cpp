/* 
 * File:   Bullet.cpp
 * Author: linuxero
 * 
 * Created on March 16, 2014, 11:21 AM
 */

#include "Bullet.h"
#include "../States/WorldState.h"
#include "../Otros/StringUtils.h"

Bullet::Bullet(const sf::Texture& tex): EntActive(tex), Colisionable((EntActive*)this) {
	timeElapsed = new Time();
}

Bullet::Bullet(const sf::Texture& tex, const Vector& pos, const Vector& vel, const Vector& maxvel): EntActive(tex, pos, vel, maxvel), Colisionable(this){
	timeElapsed = new Time();
}


Bullet::Bullet(const Bullet& orig): EntActive(orig), Colisionable((EntActive*)this) {
}

Bullet::~Bullet() {
	delete timeElapsed;
	timeElapsed = NULL;
}

void Bullet::Draw(RenderWindow& window){
	renderState->Draw(window, *this->spriteSheet);
}

void Bullet::Draw(RenderWindow& window, float inter){
	renderState->Draw(window, physicsState->GetPreviousPosition(), physicsState->GetPosition(), inter, *this->spriteSheet);
}


void Bullet::Update(const Time& elapsedTime){
	physicsState->Update(elapsedTime, affectGravity);
}



void Bullet::DoColisions(const Time& elapsedTime, int i){
	WorldState* world = WorldState::Instance();
	
	bool colisionado = false;
	
	AddTimeElapsed(elapsedTime);

	// Con Rectangulos
	for(int j=0; j < world->level->vRectColision->size() && !colisionado; j++){
		if(CheckColision(*world->level->vRectColision->at(j))){
			world->DeleteBullet(i);
            SoundPlayer::Instance()->Play("explosion");
			colisionado = true;
		}
	}
    
    for(int j=0; j < world->level->vPlatforms->size() && !colisionado; j++){
		if(CheckColision(*world->level->vPlatforms->at(j))){
			world->DeleteBullet(i);
            SoundPlayer::Instance()->Play("explosion");
			colisionado = true;
		}
	}
	
	// Con Objetos colisionables
	for(int j=0; j < world->vEntityColisionable->size() && !colisionado; j++){
		if(CheckColision(*world->vEntityColisionable->at(j))){	
			// Comprobamos con que ha chocado y realizamos acción
			if(world->vEntityColisionable->at(j)->GetClassName() == "Enemy"){
				((Enemy*)world->vEntityColisionable->at(j))->RestarLife(this->damage);
                
// AHORA MISMO ESTO ES DE PRUEBA, TENDRÍA QUE SER A UN ENEMIGO
               // WorldState::Instance()->SubstractLife(this->damage);
			}
						
			world->DeleteBullet(i);
            SoundPlayer::Instance()->Play("explosion");
			colisionado = true;
		}
	}
	
	
	// Si se acaba su tiempo de vida, destruimos la bala
	if(!colisionado){
		if(GetTimeElapsed().AsSeconds() >= world->player->GetSelectedGun()->GetLifeTime().AsSeconds()){
			delete world->vBullets->at(i);
			world->vBullets->erase(world->vBullets->begin()+i);
		}
	}
}
