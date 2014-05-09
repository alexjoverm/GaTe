/* 
 * File:   Gun.cpp
 * Author: linuxero
 * 
 * Created on March 16, 2014, 11:21 AM
 */

#include "Gun.h"
#include <iostream>
#include "../Otros/StringUtils.h"
#include "../Managers/StatusManager.h"

Gun::Gun(float x, float y, float lifeTimeSeconds, float bullSpeed) {
	
    lifeTime = new Time(lifeTimeSeconds);
	relativePos = new Vector(x, y);
    bulletSpeed = bullSpeed;
    
    typeBullet = Bullets::Type::Normal;
    reloadTime = new Time(StatusManager::Instance()->GetGunCadency());
    damage = StatusManager::Instance()->GetGunDamage();
}

Gun::~Gun() {
	delete lifeTime;
	lifeTime = NULL;
	
	delete reloadTime;
	reloadTime = NULL;
	
	delete relativePos;
	relativePos = NULL;
}


Vector  Gun::CalculateAbsolutePosition(Entity* en, bool reverse)
{
    Rectangle rec = en->GetSprite()->getGlobalBounds();
    Vector pos = rec.GetTopLeft();
    
    if(!reverse)
        pos += Vector(rec.GetWidth()*relativePos->GetX(), rec.GetHeight()*relativePos->GetY());
    else
        pos += Vector(rec.GetWidth()*(1-relativePos->GetX()), rec.GetHeight()*relativePos->GetY());
    
    return pos;
}