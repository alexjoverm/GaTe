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
    
    lastRespawnTime = 0.f;
    //respawnTime = rand()%30+25; 
    respawnTime = rand()%5; 
}

PowerUpManager::~PowerUpManager() {
}

void PowerUpManager::Update(const Time& timeElapsed){
    
   //Parte de creacion de objetos powerUps
        time +=  timeElapsed.AsSeconds();
        // Agregamos
        if(time - lastRespawnTime >= respawnTime){
            AddPowerUp();
            lastRespawnTime = time;
        }

}


void PowerUpManager::AddPowerUp(){
    
    //tipo
    int typePower = (int)(std::rand()%5)  ;
    
    //posicion
    Vector *pos = WorldState::Instance()->level->map->GetRandomPowerUpPos();
    //Velocidades
    Vector vel = Vector(0.f,0.f);
    Vector maxVel = Vector(0.f,100.f);    
    
    std::cout << typePower<<" at "<<pos->GetX()<<","<<pos->GetY()<<std::endl;
    
    WorldState::Instance()->AddPowerUp(new PowerUp( (PowerUps::State)typePower , ResourceManager::Instance()->GetTexture("texPower"+StringUtils::ConvertInt(typePower) ) , *pos , vel , maxVel) );
    
}
/*
void PowerUpManager::Power(PowerUps::State st){
    
    switch(st){
    
        case PowerUps::State::Damage :
                // subir el daño del arma
                break;
        case PowerUps::State::Speed :
                // subir la velocidad de movimiento
                break;
        case PowerUps::State::Jump :
                // subir la potencia del salto
                break;
        case PowerUps::State::SpeedShot :
                //bajar la cadencia al arma
                break;
        case PowerUps::State::AngleShoot :
                // Activar disparo angular en jugador
                break;
    
        case PowerUps::State::DoubleJump :
                //Activar doble saltoen jugador
                break;
    
    }
    
    
}*/