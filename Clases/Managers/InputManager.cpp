/* 
 * File:   InputManager.cpp
 * Author: linuxero
 * 
 * Created on April 14, 2014, 5:37 PM
 */

#include "InputManager.h"
#include "../States/WorldState.h"
#include "StateManager.h"
#include "ConfigurationManager.h"
#include "StatusManager.h"

InputManager* InputManager::instance = 0;

//*********** METODO CREADOR DEL OBJETO ****/
InputManager* InputManager::Instance() {
	if(instance == 0)
		instance = new InputManager();
	
	return instance;
}


InputManager::InputManager() {
	vKeyboard	= new std::vector<std::pair<sf::Keyboard::Key , bool>>();
	vMouse		= new std::vector<std::pair<sf::Mouse::Button , bool>>();
	
}

InputManager::InputManager(const InputManager& orig) {
}

InputManager::~InputManager() {
	vKeyboard->clear();
	delete vKeyboard;
	vKeyboard = NULL;
	
	vMouse->clear();
	delete vMouse;
	vMouse = NULL;
}


void InputManager::AddKeyboardKey(sf::Keyboard::Key key, bool pressed){
	vKeyboard->push_back(std::make_pair(key, pressed));
}

void InputManager::AddMouseKey(sf::Mouse::Button key,    bool pressed){
	vMouse->push_back(std::make_pair(key, pressed));
}


// Actualiza las teclas pulsadas
void InputManager::Update()
{
    unsigned short int auxkeyW=0, auxkeyA=0, auxkeyS=0, auxkeyD=0, auxkeyM=0, auxkeyT=0, auxkeyR=0, auxkeyP=0, auxkeySpace=0;
    unsigned short int auxmouseLeft=0, auxmouseRight=0;
    
    
    lastKeyW = keyW;
    lastKeyA = keyA;
    lastKeyS = keyS;
    lastKeyD = keyD;
    
    lastKeyR = keyR;
    lastKeyT = keyT;
    lastKeyM = keyM;
    lastKeyP = keyP;
    lastKeySpace = keySpace;
    
	// Teclado
	for (int i=0; i < vKeyboard->size(); i++)
	{
        switch(vKeyboard->at(i).first)
        {
            case sf::Keyboard::W:
                auxkeyW |= (vKeyboard->at(i).second ? 2 : 1);
                break;

            case sf::Keyboard::A:
                auxkeyA |= (vKeyboard->at(i).second ? 2 : 1);
                break;

            case sf::Keyboard::S:
                auxkeyS |= (vKeyboard->at(i).second ? 2 : 1);
                break;

            case sf::Keyboard::D:
                auxkeyD |= (vKeyboard->at(i).second ? 2 : 1);
                break;

            case sf::Keyboard::R:
                auxkeyR |= (vKeyboard->at(i).second ? 2 : 1);
                break;

            case sf::Keyboard::T:
                auxkeyT |= (vKeyboard->at(i).second ? 2 : 1);
                break;

            case sf::Keyboard::M:
                auxkeyM |= (vKeyboard->at(i).second ? 2 : 1);
                break;
                
            case sf::Keyboard::P:
                auxkeyP |= (vKeyboard->at(i).second ? 2 : 1);
                break;

            case sf::Keyboard::Space:
                auxkeySpace |= (vKeyboard->at(i).second ? 2 : 1);
                break;
        }
	}
	
	vKeyboard->clear();
	
    // Si ha habido evento, actualizamos variables
    keyW = (auxkeyW == 0 ? keyW : auxkeyW);
    keyA = (auxkeyA == 0 ? keyA : auxkeyA);
    keyS = (auxkeyS == 0 ? keyS : auxkeyS);
    keyD = (auxkeyD == 0 ? keyD : auxkeyD);
    keyM = (auxkeyM == 0 ? keyM : auxkeyM);
    keyT = (auxkeyT == 0 ? keyT : auxkeyT);
    keyR = (auxkeyR == 0 ? keyR : auxkeyR);
    keyP = (auxkeyP == 0 ? keyP : auxkeyP);
    keySpace = (auxkeySpace == 0 ? keySpace : auxkeySpace);
    
    // Si el anterior ha sido un click, reiniciamos la variable para que no se quede congelada
    keyW = (lastKeyW == 3 && auxkeyW == 0 ? 1 : keyW);
    keyA = (lastKeyA == 3 && auxkeyA == 0 ? 1 : keyA);
    keyS = (lastKeyS == 3 && auxkeyS == 0 ? 1 : keyS);
    keyD = (lastKeyD == 3 && auxkeyD == 0 ? 1 : keyD);
    keyM = (lastKeyM == 3 && auxkeyM == 0 ? 1 : keyM);
    keyT = (lastKeyT == 3 && auxkeyT == 0 ? 1 : keyT);
    keyR = (lastKeyR == 3 && auxkeyR == 0 ? 1 : keyR);
    keyP = (lastKeyP == 3 && auxkeyP == 0 ? 1 : keyP);
    keySpace = (lastKeySpace == 3 && auxkeySpace == 0 ? 1 : keySpace);
    
    lastMouseLeft = mouseLeft;
    lastMouseRight = mouseRight;
    
	// Raton
	for (int i=0; i < vMouse->size(); i++)
	{
        switch(vMouse->at(i).first)
        {
            case sf::Mouse::Left:
                auxmouseLeft |= (vMouse->at(i).second ? 2 : 1);
                break;
                
            case sf::Mouse::Right:
                auxmouseRight |= (vMouse->at(i).second ? 2 : 1);
                break;
        }
	}
	
	vMouse->clear();
    
    mouseLeft = (auxmouseLeft == 0 ? mouseLeft : auxmouseLeft);
    mouseRight = (auxmouseRight == 0 ? mouseRight : auxmouseRight);
    
    mouseLeft = (lastMouseLeft == 3 && auxmouseLeft == 0 ? 1 : mouseLeft);
    mouseRight = (lastMouseRight == 3 && auxmouseRight == 0 ? 1 : keyR);
    
}



void InputManager::Process(sf::Event event)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			AddKeyboardKey(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			AddKeyboardKey(event.key.code, false);
			break;

		case sf::Event::Closed:
            ConfigurationManager::Instance()->SaveConfigurations();
            StatusManager::Instance()->SaveStatus();
			RenderWindow::Instance()->Close();
			break;

		// A tiempo real
        case sf::Event::MouseMoved:
            mousePosX = event.mouseMove.x;
            mousePosY = event.mouseMove.y;
            break;
            
		case sf::Event::MouseButtonPressed:
            AddMouseKey(event.mouseButton.button, true);
			break;
            
        case sf::Event::MouseButtonReleased:
            AddMouseKey(event.mouseButton.button, false);
			break;
	}
}



Vector InputManager::GetMousePosition() const{
    return Vector(mousePosX, mousePosY);
}