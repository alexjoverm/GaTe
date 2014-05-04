/* 
 * File:   PauseState.h
 * Author: aba
 *
 * Created on May 8, 2014, 11:15 AM
 */

#ifndef PAUSESTATE_H
#define	PAUSESTATE_H

#include "State.h"
#include "../HUD/ImageButton.h"
#include "../HUD/Button.h"
#include "../Animations/SpriteSheet.h"
#include "../Managers/InputManager.h"

class PauseState: public State {
public:
    PauseState();
    PauseState(const PauseState& orig);
    virtual ~PauseState();
    
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

    sf::RectangleShape*  overlay;

    std::vector<Button*>    *vButtons;
    ImageButton   *continuar, *seleccion, *menu;
    SpriteSheet   *background, *menuS, *seleccionS, *continuarS;
  
    
    std::pair<States::ID , bool> requestStateChange;
};

#endif	/* PAUSESTATE_H */

