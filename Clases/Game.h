/* 
 * File:   Game.h
 * Author: alejandrojovermorales
 *
 * Created on April 22, 2014, 1:04 PM
 */

#ifndef GAME_H
#define	GAME_H

#include "Otros/Time.h"
#include "Otros/Clock.h"
#include "Motor2D/RenderWindow.h"
#include "Managers/StateManager.h"

class Game {
public:
    Game();
    Game(const Game& orig);
    virtual ~Game();
    
    void Run();
    void HandleEvents();
	void Update(const Time& timeElapsed);
	void Render(float interp);
    
    
private:
    Time*           timeUpdate;  //Será 1/15 (15 veces por segundo)
	RenderWindow*	window;
    
    StateManager*   stateManager;
};

#endif	/* GAME_H */

