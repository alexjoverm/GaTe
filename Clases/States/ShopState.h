/* 
 * File:   ShopState.h
 * Author: jc
 *
 * Created on 24 de abril de 2014, 12:05
 */

#ifndef SHOPSTATE_H
#define	SHOPSTATE_H

#include "../Motor2D/Level.h"
#include "../Motor2D/RenderWindow.h"
#include "../Managers/InputManager.h"
#include "../Managers/ResourceManager.h"
#include "../MusicSounds/MusicPlayer.h"
#include "../HUD/ImageButton.h"
#include "../HUD/ImproveGroup.h"
#include "State.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class ShopState : public State {
public:
    ShopState();
    ShopState(const ShopState& orig);
    virtual ~ShopState();

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
    sf::Text     *creditText;
    
    
    std::vector<ImproveGroup*>     *vImproves;
    

    //Players
    MusicPlayer* musicPlayer;
};

#endif	/* LEVELSELECTIONSTATE_H */

