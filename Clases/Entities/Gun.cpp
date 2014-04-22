/* 
 * File:   Gun.cpp
 * Author: linuxero
 * 
 * Created on March 16, 2014, 11:21 AM
 */

#include "Gun.h"
#include "../States/WorldState.h"
#include "Player.h"
#include "../Otros/StringUtils.h"
#include <iostream>

Gun::Gun(const sf::Texture& tex): EntActive(tex) {
	lifeTime = new Time();
	reloadTime = new Time();
	relativePos = new Vector(0.75f, 0.5f);
}

Gun::Gun(const sf::Texture& tex, const Vector& pos, const Vector& vel, const Vector& maxvel): EntActive(tex, pos, vel, maxvel){
	lifeTime = new Time();
	reloadTime = new Time();
	relativePos = new Vector(0.75f, 0.5f);
}


Gun::Gun(const Gun& orig): EntActive(orig) {
}

Gun::~Gun() {
	delete lifeTime;
	lifeTime = NULL;
	
	delete reloadTime;
	reloadTime = NULL;
	
	delete relativePos;
	relativePos = NULL;
}


void Gun::Shot(const Vector& speed, const Vector& pos){
	WorldState* w = WorldState::Instance();
	Bullet* aux = new Bullet(ResourceManager::Instance()->GetTexture("texBullet"), pos, speed);
    aux->SetPosition(aux->GetPosition().GetX()+aux->GetSprite()->getGlobalBounds().GetWidth(), 
                     aux->GetPosition().GetY()-aux->GetSprite()->getGlobalBounds().GetHeight()*0.4);
	w->AddBullet(aux);
}


void Gun::Draw(RenderWindow& window, float inter){
	renderState->Draw(window, physicsState->GetPreviousPosition(), physicsState->GetPosition(), inter, *this->spriteSheet);
}


void Gun::Update(const Time& elapsedTime){
	//physicsState->Update(elapsedTime, false);
}

void Gun::Update(EntActive* ent){
	// Hacemos cambios en las posiciones
	physicsState->SetPreviousPosition(ent->GetPreviousPosition().GetX() + relativePos->GetX(), ent->GetPreviousPosition().GetY() + relativePos->GetY());
	physicsState->SetNextPosition(ent->GetPosition().GetX() + relativePos->GetX(), ent->GetPosition().GetY() + relativePos->GetY());

}