/* 
 * File:   PowerUpManager.cpp
 * Author: jmsm30
 * 
 * Created on 30 de abril de 2014, 3:41
 */

#include "PowerUpManager.h"
#include "../Otros/StringUtils.h"
#include "../States/WorldState.h"
#include "ResourceManager.h"

PowerUpManager::PowerUpManager() {
    srand(std::time(NULL));
    
    respawnTime = rand()%5+0; 
    time = 0.f;

}

PowerUpManager::~PowerUpManager() {
}

void PowerUpManager::Update(const Time& timeElapsed){
    
   //Parte de creacion de objetos powerUps
        time +=  timeElapsed.AsSeconds();
        // Agregamos
        if(time > respawnTime){
            AddPowerUp();
            time = 0.f;
            respawnTime = rand()%5 + 0;

        }

}


void PowerUpManager::AddPowerUp(){
    
    //tipo de momento hay 5 de 0-4
    //int typePower = (int)(std::rand()%4)  ;
    int typePower = 4;
    //posicion
    Vector *pos = WorldState::Instance()->level->map->GetRandomPowerUpPos();
    //Velocidades
    Vector vel = Vector(0.f,0.f);
    Vector maxVel = Vector(0.f,140.f);    
    
    
    PowerUp* aux = new PowerUp( (PowerUps::State)typePower , ResourceManager::Instance()->GetTexture("texPower"+StringUtils::ConvertInt(typePower) ) , *pos , vel , maxVel);
    aux->SetRectangleColision(0,0,aux->GetSprite()->getGlobalBounds().GetWidth(), aux->GetSprite()->getGlobalBounds().GetHeight());
    
    WorldState::Instance()->AddPowerUp( aux );
    
}