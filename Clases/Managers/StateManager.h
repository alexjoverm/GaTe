/* 
 * File:   StateManager.h
 * Author: alejandrojovermorales
 *
 * Created on April 22, 2014, 3:16 PM
 */

#ifndef STATEMANAGER_H
#define	STATEMANAGER_H

#include "../States/State.h"
#include "../Factories/StateFactory.h"

class StateManager {
public:
    StateManager();
    StateManager(const StateManager& orig);
    virtual ~StateManager();

    void   CreateStates();
    State* GetCurrentState() const;
    void   SetCurrentState(States::ID id);
    
    States::ID currentState;
    
private:
    std::map<States::ID, State*> *mapStates;
    
    void OnChangeState();
};

#endif	/* STATEMANAGER_H */

