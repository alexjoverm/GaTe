/* 
 * File:   EntityFactory.cpp
 * Author: jc
 * 
 * Created on 8 de mayo de 2014, 16:43
 */

#include "EntityFactory.h"
#include "../Managers/StatusManager.h"

Enemy* EntityFactory::CreateEnemyOne(const Vector& pos, const Vector& vel, const Vector& maxvel){
    Enemy* enemigo= new Enemy(ResourceManager::Instance()->GetTexture("texEnemyOne"),
                        Vector(140.0f, 103.8f),pos, vel, maxvel);
    
    enemigo->factorSpeed = StatusManager::Instance()->GetEnemyOneSpeed();
    enemigo->factorSpeedIni = enemigo->factorSpeed;
    enemigo->attack = StatusManager::Instance()->GetEnemyOneAttack();
        
    enemigo->SetRectangleColision(15, 8, 105, 95);
    enemigo->InitLifebar();
    enemigo->life->vmax = StatusManager::Instance()->GetEnemyOneLife();
    enemigo->life->valor = enemigo->life->vmax;
    
    enemigo->price = StatusManager::Instance()->GetEnemyOnePrice();
    enemigo->type = 1;
    
    enemigo->AddAnimation(new Animation("andarEnemigo", enemigo->GetSprite(), 1, 13, 0.05, false, true));
    enemigo->SetCurrentAnimation("andarEnemigo", enemigo->GetSprite());
    enemigo->PlayAnimation();
    
    return enemigo;
}

Enemy* EntityFactory::CreateEnemyTwo(const Vector& pos, const Vector& vel, const Vector& maxvel){
    Enemy* enemigo= new Enemy(ResourceManager::Instance()->GetTexture("texEnemyTwo"),
                        Vector(108.0f, 108.1f),pos, vel, maxvel);
    
    enemigo->factorSpeed = StatusManager::Instance()->GetEnemyTwoSpeed();
    enemigo->factorSpeedIni = enemigo->factorSpeed;
    enemigo->attack = StatusManager::Instance()->GetEnemyTwoAttack();
    
    enemigo->SetRectangleColision(15, 8, 105, 95);
    enemigo->InitLifebar();
    enemigo->life->vmax = StatusManager::Instance()->GetEnemyTwoLife();
    enemigo->life->valor = enemigo->life->vmax;
    
    enemigo->price = StatusManager::Instance()->GetEnemyTwoPrice();
    enemigo->type = 2;
    
    enemigo->AddAnimation(new Animation("andarEnemigo", enemigo->GetSprite(), 3, 14, 0.05, false, true));
    enemigo->SetCurrentAnimation("andarEnemigo", enemigo->GetSprite());
    enemigo->PlayAnimation();
    
    return enemigo;
    
}

Enemy* EntityFactory::CreateEnemyThree(const Vector& pos, const Vector& vel, const Vector& maxvel){
    Enemy* enemigo= new Enemy(ResourceManager::Instance()->GetTexture("texEnemyThree"),
                        Vector(108.0f, 108.1f),pos, vel, maxvel);
    
    enemigo->factorSpeed = StatusManager::Instance()->GetEnemyThreeSpeed();
    enemigo->factorSpeedIni = enemigo->factorSpeed;
    enemigo->attack = StatusManager::Instance()->GetEnemyThreeAttack();
    
    enemigo->SetRectangleColision(15, 8, 105, 95);
    enemigo->InitLifebar();
    enemigo->life->vmax = StatusManager::Instance()->GetEnemyThreeLife();
    enemigo->life->valor = enemigo->life->vmax;
    
    enemigo->price = StatusManager::Instance()->GetEnemyThreePrice();
    enemigo->type = 3;
    
    enemigo->AddAnimation(new Animation("andarEnemigo", enemigo->GetSprite(), 3, 14, 0.05, false, true));
    enemigo->SetCurrentAnimation("andarEnemigo", enemigo->GetSprite());
    enemigo->PlayAnimation();
    
    return enemigo;
}


Tower* EntityFactory::CreateTowerOne(const Vector& pos){
    Tower* to = new Tower(ResourceManager::Instance()->GetTexture("texTowerOne"), Vector(96.f,122.4f), pos, 0.f);
    to->SetRange(StatusManager::Instance()->GetTowerOneRange());
    to->damage = StatusManager::Instance()->GetTowerOneDamage();
    to->reloadTime->SetSeconds(StatusManager::Instance()->GetTowerOneCadency());
    return to;
}

Tower* EntityFactory::CreateTowerTwo(const Vector& pos){
    Tower* to = new Tower(ResourceManager::Instance()->GetTexture("texTowerTwo"), Vector(96.f,122.4f), pos, 0.f);
    to->SetRange(StatusManager::Instance()->GetTowerTwoRange());
    to->damage = StatusManager::Instance()->GetTowerTwoDamage();
    to->reloadTime->SetSeconds(StatusManager::Instance()->GetTowerTwoCadency());
    return to;
}

Tower* EntityFactory::CreateTowerThree(const Vector& pos){
    Tower* to = new Tower(ResourceManager::Instance()->GetTexture("texTowerThree"), Vector(96.f,122.4f), pos, 0.f);
    to->SetRange(StatusManager::Instance()->GetTowerThreeRange());
    to->damage = StatusManager::Instance()->GetTowerThreeDamage();
    to->reloadTime->SetSeconds(StatusManager::Instance()->GetTowerThreeCadency());
    return to;
}