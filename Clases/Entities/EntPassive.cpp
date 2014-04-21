/* 
 * File:   EntPassive.cpp
 * Author: linuxero
 * 
 * Created on March 11, 2014, 9:44 AM
 */

#include "EntPassive.h"

EntPassive::EntPassive(const sf::Texture& tex): Entity(tex){
}

EntPassive::EntPassive(const EntPassive& orig) : Entity(orig){
}

EntPassive::~EntPassive() {
}



void EntPassive::Draw(RenderWindow& window){
	window.Draw(*(this->spriteSheet));
}

void EntPassive::Update(const Time& elapsedTime)
{
	
}


