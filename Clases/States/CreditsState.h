/* 
 * File:   CreditsState.h
 * Author: jc
 *
 * Created on 28 de abril de 2014, 11:11
 */

#ifndef CREDITSSTATE_H
#define	CREDITSSTATE_H

#include "../Motor2D/Level.h"
#include "../Motor2D/RenderWindow.h"
#include "../Managers/InputManager.h"
#include "../Managers/ResourceManager.h"
#include "../MusicSounds/MusicPlayer.h"
#include "../HUD/ImageButton.h"
#include "State.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class CreditsState : public State {
public:
    CreditsState();
    CreditsState(const CreditsState& orig);
    virtual ~CreditsState();

    // Inicialización y Liberación
    void Init();
    void Clean();

    // 3 bucles principales
    void Update(const Time& timeElapsed);
    void Render(float interp);

    // Eventos
    void HandleEvents(); // Le pasa al InputManager los eventos

    void AddNonRealEvent(sf::Event e) {
        vNonRealEvents->push_back(e);
    }

    void AddRealEvent(sf::Event e) {
        vRealEvents->push_back(e);
    }
    void ProcessRealEvent();
    //void ProcessNonRealEvent();

private:

    // Funciones
    void LoadResources(); // Carga recursos, se llama desde Init();

    //Eventos
    std::vector<sf::Event> *vNonRealEvents;
    std::vector<sf::Event> *vRealEvents;

    SpriteSheet* fondo;

    ImageButton* returnButton;

    //Players
    MusicPlayer* musicPlayer;
};

#endif	/* CREDITSSTATE_H */

