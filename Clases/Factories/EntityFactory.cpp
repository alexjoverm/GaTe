/* 
 * File:   EntityFactory.cpp
 * Author: jc
 * 
 * Created on 8 de mayo de 2014, 16:43
 */

#include "EntityFactory.h"
#include "../Managers/StatusManager.h"

Enemy* EntityFactory::CreateEnemyOne(const Vector& pos, const Vector& vel, const Vector& maxvel){
    Enemy* enemigo= new Enemy(ResourceManager::Instance()->GetTexture("texLevel0"),
                        Vector(140.0f, 103.8f),pos, vel, maxvel);
    
    enemigo->factorSpeed = StatusManager::Instance()->GetEnemyOneSpeed();
    enemigo->factorSpeedIni = enemigo->factorSpeed;
    enemigo->attack = StatusManager::Instance()->GetEnemyOneAttack();
        
    enemigo->SetRectangleColision(15, 8, 105, 95);
    enemigo->InitLifebar();
    enemigo->life->vmax = StatusManager::Instance()->GetEnemyOneLife();
    enemigo->life->valor = enemigo->life->vmax;
    
    enemigo->AddAnimation(new Animation("andarEnemigo", enemigo->GetSprite(), 1, 13, 0.05, false, true));
    enemigo->SetCurrentAnimation("andarEnemigo", enemigo->GetSprite());
    enemigo->PlayAnimation();
    
    return enemigo;
}

Enemy* EntityFactory::CreateEnemyTwo(const Vector& pos, const Vector& vel, const Vector& maxvel){
    Enemy* enemigo= new Enemy(ResourceManager::Instance()->GetTexture("texRobot"),
                        Vector(108.0f, 108.1f),pos, vel, maxvel);
    
    enemigo->factorSpeed = StatusManager::Instance()->GetEnemyTwoSpeed();
    enemigo->factorSpeedIni = enemigo->factorSpeed;
    enemigo->attack = StatusManager::Instance()->GetEnemyTwoAttack();
    
    enemigo->SetRectangleColision(15, 8, 105, 95);
    enemigo->InitLifebar();
    enemigo->life->vmax = StatusManager::Instance()->GetEnemyTwoLife();
    enemigo->life->valor = enemigo->life->vmax;
    
    enemigo->AddAnimation(new Animation("andarEnemigo", enemigo->GetSprite(), 3, 14, 0.05, false, true));
    enemigo->SetCurrentAnimation("andarEnemigo", enemigo->GetSprite());
    enemigo->PlayAnimation();
    
    return enemigo;
    
}

Enemy* EntityFactory::CreateEnemyThree(const Vector& pos, const Vector& vel, const Vector& maxvel){
    return new Enemy(ResourceManager::Instance()->GetTexture("texLevel0"),
                        Vector(140.0f, 103.8f),pos, vel, maxvel);
    
}


Tower* EntityFactory::CreateTowerOne(const Vector& pos){
    Tower* to = new Tower(ResourceManager::Instance()->GetTexture("texTower"), Vector(96.f,122.4f), pos, 0.f);
    to->SetRange(StatusManager::Instance()->GetTowerOneRange());
    to->damage = StatusManager::Instance()->GetTowerOneDamage();
    to->reloadTime->SetSeconds(StatusManager::Instance()->GetTowerOneCadency());
    return to;
}

Tower* EntityFactory::CreateTowerTwo(const Vector& pos){
    Tower* to = new Tower(ResourceManager::Instance()->GetTexture("texTower"), Vector(96.f,122.4f), pos, 0.f);
    to->SetRange(StatusManager::Instance()->GetTowerTwoRange());
    to->damage = StatusManager::Instance()->GetTowerTwoDamage();
    to->reloadTime->SetSeconds(StatusManager::Instance()->GetTowerTwoCadency());
    return to;
}