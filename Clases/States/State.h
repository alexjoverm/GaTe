/* 
 * File:   State.h
 * Author: alejandrojovermorales
 *
 * Created on April 22, 2014, 12:59 PM
 */

#ifndef STATE_H
#define	STATE_H

#include "../Otros/Time.h"

class State {
public:    
    State();
    State(const State& orig);
    virtual ~State();
    
 /*   void HandleEvents() = 0;
	void Update(const Time& timeElapsed) = 0;
	void Render(float interp) = 0;
    
    void Clean() = 0;
    void Init() = 0;*/
};

#endif	/* STATE_H */

