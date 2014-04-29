/* 
 * File:   NewTowerState.h
 * Author: jmsm30
 *
 * Created on 23 de abril de 2014, 20:45
 */

#ifndef NEWTOWERSTATE_H
#define	NEWTOWERSTATE_H

#include "State.h"
#include "../Entities/Tower.h"

class NewTowerState : public State{
public:
    NewTowerState();
    NewTowerState(const NewTowerState& orig);
    virtual ~NewTowerState();
    
        // Inicialización y Liberación
	void Init();
    void Clean();
    
        // 3 bucles principales
	void Update(const Time& timeElapsed);
	void Render(float interp);
    
        // Eventos
	void HandleEvents(); // Le pasa al InputManager los eventos

private:

    void LoadResources();
    void AddTower();
        
    bool        rightPlace;
    
    Vector*      posPlace;
    Tower*      tower;
    sf::RectangleShape*  overlay;
    
    float posY;
        
};

#endif	/* NEWTOWERSTATE_H */

