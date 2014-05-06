/* 
 * File:   WaveManager.cpp
 * Author: alejandrojovermorales
 * 
 * Created on May 5, 2014, 3:30 PM
 */

#include "WaveManager.h"
#include "../States/WorldState.h"

WaveManager::WaveManager() 
{
    timeElapsed = new Time();
    timeInBetweenEnemies = new Time();
    timeInBetweenWaves = new Time();
    
    waveCounter = 0;
    enemyCounter = 0;
    state = Wave::State::Waiting;
}


WaveManager::~WaveManager() {
    delete timeElapsed; timeElapsed = NULL;
    delete timeInBetweenEnemies; timeInBetweenEnemies = NULL;
    delete timeInBetweenWaves; timeInBetweenWaves = NULL;
}


void WaveManager::Init(float secondsEnemies, float secondsWaves)
{
    timeInBetweenEnemies->SetSeconds(secondsEnemies);
    timeInBetweenWaves->SetSeconds(secondsWaves);
}


void WaveManager::Update(const Time& tiElapsed)
{
    if(state != Wave::State::Finished)
    {
        // Si no quedan enemigos, se pasa al estado de cargar
        if(WorldState::Instance()->vEnemies->empty())
            state = Wave::State::Loading;

        // Se cuenta el tiempo, excepto cuando se está en espera
        if(state != Wave::State::Waiting)
            *timeElapsed += tiElapsed;

        if(state == Wave::State::Loading) // Estado de espera a comenzar a insertar la oleada 
        {
            if(timeElapsed->AsSeconds() >= timeInBetweenWaves->AsSeconds())
            {
                timeElapsed->SetSeconds(0.f);
                state = Wave::State::Running;
                InsertEnemy();
            }
        }
        else if(state == Wave::State::Running) // Estado de inserción de oleada 
        {
            if(timeElapsed->AsSeconds() >= timeInBetweenEnemies->AsSeconds())
            {
                *timeElapsed -= *timeInBetweenEnemies;
                InsertEnemy();
            }
        }
    }
    
    /*
    if(state == Wave::State::Running)    std::cout << "State: Running" << std::endl;
    else if(state == Wave::State::Waiting)    std::cout << "State: Waiting" << std::endl;
    else if(state == Wave::State::Loading)    std::cout << "State: Loading" << std::endl;
    else if(state == Wave::State::Finished)    std::cout << "State: Finished" << std::endl; */
}


void WaveManager::InsertEnemy()
{
    WorldState* w = WorldState::Instance();
    Enemy* foe;
    
    
    if(vEnemies.at(waveCounter).at(enemyCounter) == 1) // Enemigo tipo 1
    {
        foe = new Enemy(ResourceManager::Instance()->GetTexture("texLevel0"),
                        Vector(108.0f, 108.0f), *w->vPath->at(0),
                        Vector(0.f, 0.f), Vector(500.f, 500.f) 
                    );
        
        foe->SetSpeed(220.f, 0.f);
        foe->SetRectangleColision(10, 8, 100, 95);
        foe->InitLifebar();

        foe->AddAnimation(new Animation("andarEnemigo", foe->GetSprite(), 3, 14, 0.05, false, true));
        foe->AddAnimation(new Animation("andar2Enemigo", foe->GetSprite(), 15, 26, 0.05, false, true));
        foe->SetCurrentAnimation("andarEnemigo", foe->GetSprite());
        foe->PlayAnimation();

        w->AddColisionableEntity(foe);// Añadimos al array de colisionables
        w->AddEnemy(foe);		// Añadimos al array de elementos activos, para que se pinte
    }
    
    
    // Actualizamos contadores y comprobamos la situación
    enemyCounter++; 
    
    if(enemyCounter == vEnemies.at(waveCounter).size()){ // Fin de Racha
        state = Wave::State::Waiting;
        waveCounter++;
        enemyCounter=0;
        
        if(waveCounter == vEnemies.size()) // Fin de Vector de Rachas
            state = Wave::State::Finished;
    }
}