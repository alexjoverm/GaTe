/* 
 * File:   StateFactory.cpp
 * Author: alejandrojovermorales
 * 
 * Created on April 22, 2014, 3:15 PM
 */

#include "StateFactory.h"
#include "../States/WorldState.h"
#include "../States/MenuState.h"
#include "../States/LoadingState.h"
#include "../States/LevelSelectionState.h"
#include "../States/SettingsState.h"
#include "../States/CreditsState.h"
#include "../States/TutorialState.h"
#include "../States/NewTowerState.h"
#include "../States/ShopState.h"


State* StateFactory::CreateState(States::ID id){
    
    
    if(id == States::ID::WorldState)
        return WorldState::Instance();
    else if(id == States::ID::MenuState)
        return new MenuState();
    else if(id == States::ID::LoadingState)
        return new LoadingState();
    else if(id == States::ID::LevelSelectionState)
        return new LevelSelectionState();
    else if(id == States::ID::SettingsState)
        return new SettingsState();
    else if(id == States::ID::CreditsState)
        return new CreditsState();
    else if(id == States::ID::TutorialState)
        return new TutorialState();
    else if(id == States::ID::TowerSelectionState)
        return new NewTowerState();
    else if(id == States::ID::ShopState)
        return new ShopState();
    /*
    else if(id == States::ID::PauseState)
        return new PauseState();
    
    
    */ 
}