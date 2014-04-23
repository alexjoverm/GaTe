/* 
 * File:   StateManager.cpp
 * Author: alejandrojovermorales
 * 
 * Created on April 22, 2014, 3:16 PM
 */

#include <map>
#include "StateManager.h"
#include "../States/MenuState.h"


StateManager* StateManager::instance = 0;

//*********** METODO CREADOR DEL OBJETO ****/
StateManager* StateManager::Instance() {
	if(instance == 0)
		instance = new StateManager();
	
	return instance;
}


StateManager::StateManager() {
    mapStates = new std::map<States::ID, State*>();
    currentState = States::ID::MenuState;
    
    CreateStates();
    GetCurrentState()->Init();
}

StateManager::StateManager(const StateManager& orig) {
}

StateManager::~StateManager() {
    for(std::map<States::ID, State*>::iterator iterator = mapStates->begin(); iterator != mapStates->end(); iterator++) 
        delete iterator->second;
	delete mapStates;
}

void StateManager::CreateStates()
{
    mapStates->insert(std::make_pair(States::ID::MenuState , StateFactory::CreateState(States::ID::MenuState)));
    //mapStates->insert(std::make_pair(States::ID::LevelSelectionState , StateFactory::CreateState(States::ID::LevelSelectionState)));
    //mapStates->insert(std::make_pair(States::ID::SettingsState , StateFactory::CreateState(States::ID::SettingsState)));
    mapStates->insert(std::make_pair(States::ID::WorldState , StateFactory::CreateState(States::ID::WorldState)));
    //mapStates->insert(std::make_pair(States::ID::TowerSelectionState , StateFactory::CreateState(States::ID::TowerSelectionState)));
    //mapStates->insert(std::make_pair(States::ID::CreditsState , StateFactory::CreateState(States::ID::CreditsState)));
    //mapStates->insert(std::make_pair(States::ID::PauseState , StateFactory::CreateState(States::ID::PauseState)));
    
}

State* StateManager::GetCurrentState() const
{
    std::map<States::ID, State*>::iterator par = mapStates->find(currentState);
    return par->second;
}


void StateManager::SetCurrentState(States::ID id)
{
    GetCurrentState()->Clean();
    currentState = id;
    GetCurrentState()->Init();
}