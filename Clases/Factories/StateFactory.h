/* 
 * File:   StateFactory.h
 * Author: alejandrojovermorales
 *
 * Created on April 22, 2014, 3:15 PM
 */

#ifndef STATEFACTORY_H
#define	STATEFACTORY_H
#include "../States/State.h"

class StateFactory {
    
public:
    static State* CreateState(States::ID id);
    
};

#endif	/* STATEFACTORY_H */

