/* 
 * File:   WaveManager.cpp
 * Author: alejandrojovermorales
 * 
 * Created on May 5, 2014, 3:30 PM
 */

#include "WaveManager.h"
#include "../States/WorldState.h"
#include "../Factories/EntityFactory.h"
#include "StatusManager.h"

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
            if(!cambiado){
                waveCounter++;
                StatusManager::Instance()->IncrementInt(Parameters::countingWaves, 1);
                cambiado = true;
            }
            
            if(timeElapsed->AsSeconds() >= timeInBetweenWaves->AsSeconds())
            {
                cambiado = false;
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
    
    
    if(vEnemies.at(waveCounter-1).at(enemyCounter) == 1) // Enemigo tipo 1
        foe= EntityFactory::CreateEnemyOne(*w->vPath->at(0));
    else if(vEnemies.at(waveCounter-1).at(enemyCounter) == 2) // Tipo 2
        foe= EntityFactory::CreateEnemyTwo(*w->vPath->at(0));
    else
        foe= EntityFactory::CreateEnemyThree(*w->vPath->at(0));
        
    w->AddColisionableEntity(foe);
    w->AddEnemy(foe);		
    
    
    
    // Actualizamos contadores y comprobamos la situación
    enemyCounter++; 
    
    if(enemyCounter == vEnemies.at(waveCounter-1).size()){ // Fin de Racha
        state = Wave::State::Waiting;
        
        enemyCounter=0;
        
        if(waveCounter == vEnemies.size()) // Fin de Vector de Rachas
            state = Wave::State::Finished;
    }
}