/* 
 * File:   TemporalChange.cpp
 * Author: jmsm30
 * 
 * Created on 3 de mayo de 2014, 3:41
 */

#include <stddef.h>
#include "TemporalChange.h"
#include "Time.h"
#include "../States/WorldState.h"


TemporalChange::TemporalChange(Changes::State st , float changeLifeTime) {
    
    lifeTime = changeLifeTime;
    timeAlive = 0.f;
    type = st;
    enemy = NULL;
    status = StatusManager::Instance();

    spritesheet = new SpriteSheet( ResourceManager::Instance()->GetTexture("miniPower"+StringUtils::ConvertInt((int)type) ) );
    spritesheet->SetPosition(Vector(1000.f,100.f));
    
    
    AddChange();
    
    
    
}

TemporalChange::TemporalChange(Changes::State st , float changeLifeTime, Enemy* changeEnemy) {

    lifeTime = changeLifeTime;
    timeAlive = 0.f;
    type = st;
    enemy = changeEnemy;
    status = StatusManager::Instance();
    
    spritesheet = new SpriteSheet( ResourceManager::Instance()->GetTexture("miniPower"+StringUtils::ConvertInt((int)type) ) );
    spritesheet->SetPosition(Vector(1000.f,100.f));
    
    
    AddChange();

}

TemporalChange::TemporalChange(const TemporalChange& orig) {
}

TemporalChange::~TemporalChange() {
}

bool TemporalChange::UpdateBool(const Time& timeElapsed){

     timeAlive += timeElapsed.AsSeconds();
  
     if(timeAlive >= lifeTime)
        return true;

    return false;
    
}

void TemporalChange::Draw(RenderWindow* window){
    if(type != Changes::State::Slow){
        
        window->Draw( *spritesheet );
    }
}

void TemporalChange::AddChange(){

    std::cout << type;
    
    switch(type){

            // Mejora el daño del arma del personaje
        case Changes::State::Damage :
                    if(enemy == NULL){
                        WorldState::Instance()->player->GetSelectedGun()->damage += 15.f;
                    }
                break;
                    
        case Changes::State::Speed :
                    if(enemy == NULL){
                            WorldState::Instance()->player->factorSpeed += 150.f;
                    }
                break;

        case Changes::State::SpeedShot :
                    if(enemy == NULL){
                            WorldState::Instance()->player->GetSelectedGun()->reloadTime->SetSeconds(WorldState::Instance()->player->GetSelectedGun()->reloadTime->AsSeconds()-0.25f);
                    }
                break;
        case Changes::State::DoubleJump :
                            WorldState::Instance()->player->doubleJump = true;
                break;
        case Changes::State::AngleShoot :
                            WorldState::Instance()->player->angularShoot = true;
                break;
        case Changes::State::Slow :
                    if(enemy == NULL){
                            WorldState::Instance()->player->SetSpeed( WorldState::Instance()->player->GetSpeed().GetX()-150.f , WorldState::Instance()->player->GetSpeed().GetY() );
                    }
                break;
    }

}
    


void TemporalChange::RemoveChange(){

    
    switch(type){

            // Mejora el daño del arma del personaje
        case Changes::State::Damage :
                    if(enemy == NULL){
                        WorldState::Instance()->player->GetSelectedGun()->damage -= 15.f;
                    }
                break;
                    
        case Changes::State::Speed :
                    if(enemy == NULL){
                            WorldState::Instance()->player->factorSpeed -= 150.f;
                    }
                break;

        case Changes::State::SpeedShot :
                    if(enemy == NULL){
                            WorldState::Instance()->player->GetSelectedGun()->reloadTime->SetSeconds(WorldState::Instance()->player->GetSelectedGun()->reloadTime->AsSeconds()+0.25f);
                    }
                break;
        case Changes::State::DoubleJump :
                            WorldState::Instance()->player->doubleJump = StatusManager::Instance()->GetInt(Parameters::habilityDobleJump);
                break;
        case Changes::State::AngleShoot :
                            WorldState::Instance()->player->angularShoot = StatusManager::Instance()->GetInt(Parameters::habilityAngularShot) ;
                break;
        case Changes::State::Slow :
                    if(enemy == NULL){
                            WorldState::Instance()->player->SetSpeed( WorldState::Instance()->player->GetSpeed().GetX()+150.f , WorldState::Instance()->player->GetSpeed().GetY() );
                    }
                break;
    }

}

