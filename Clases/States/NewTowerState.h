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
#include "../HUD/ImageButton.h"

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
    int         selectedTower=1;
    
    Vector*      posPlace;
    Tower*      tower;
    sf::RectangleShape*  overlay;
    
    float posY;
    
    ImageButton *tower1,*tower2,*tower3;
    sf::Text    *price;
        
};

#endif	/* NEWTOWERSTATE_H */

