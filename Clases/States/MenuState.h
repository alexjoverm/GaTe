/* 
 * File:   MenuState.h
 * Author: alejandrojovermorales
 *
 * Created on April 22, 2014, 7:50 PM
 */

#ifndef MENUSTATE_H
#define	MENUSTATE_H

#include "../Animations/SpriteSheet.h"
#include "../Otros/Time.h"
#include "State.h"

class MenuState: public State {
public:
    MenuState();
    MenuState(const MenuState& orig);
    virtual ~MenuState();
    
    // Inicialización y Liberación
	void Init();
    void Clean();
    
// 3 bucles principales
	void Update(const Time& timeElapsed);
	void Render(float interp);
    
// Eventos
	void HandleEvents(); // Le pasa al InputManager los eventos
    
    
private:
    
    SpriteSheet*    fondo;

    sf::Text m_Text[7];
    sf::Text volver;
    sf::RectangleShape rectangle;
    sf::Font m_Font;

    sf::IntRect r1;
    sf::IntRect r2;
    sf::IntRect r3;
    sf::IntRect r4;
    sf::IntRect r5;
    sf::IntRect r6;
    sf::IntRect r7;
     
   int screen;
   
   bool m_Increase[3];
   int m_Alpha[3];
    
   int titleSize;
   int optionsSize;
   
   float leftMargin;
   float spaceLine;
   float topMargin;

};

#endif	/* MENUSTATE_H */

