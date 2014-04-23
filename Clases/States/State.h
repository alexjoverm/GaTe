/* 
 * File:   State.h
 * Author: alejandrojovermorales
 *
 * Created on April 22, 2014, 12:59 PM
 */

#ifndef STATE_H
#define	STATE_H

#include "../Otros/Time.h"
#include "../Motor2D/RenderWindow.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/InputManager.h"

class State {
public:    
    virtual void HandleEvents() = 0;
	virtual void Update(const Time& timeElapsed) = 0;
	virtual void Render(float interp) = 0;
    
    virtual void Clean() = 0;
    virtual void Init() = 0;
    
    RenderWindow* window;
    InputManager* inputManager;
    ResourceManager* resourceManager;
};

#endif	/* STATE_H */

