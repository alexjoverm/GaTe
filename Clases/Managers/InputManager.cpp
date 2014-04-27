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
	
	keyW = keyA = keyS = keyD = keyM = keySpace = mouseLeft = mouseRight = false;	
    keyR = keyT = false;
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
    lastKeyW = keyW;
    lastKeyA = keyA;
    lastKeyS = keyS;
    lastKeyD = keyD;
    
    lastKeyR = keyR;
    lastKeyT = keyT;
    lastKeyM = keyM;
    lastKeySpace = keySpace;
        
        
	// Teclado
	for (int i=0; i < vKeyboard->size(); i++)
	{
		switch(vKeyboard->at(i).first)
		{
			case sf::Keyboard::W:
				keyW = vKeyboard->at(i).second;	break;

			case sf::Keyboard::A:
				keyA = vKeyboard->at(i).second;	break;

			case sf::Keyboard::S:
				keyS = vKeyboard->at(i).second;	break;

			case sf::Keyboard::D:
				keyD = vKeyboard->at(i).second;	break;
            
            case sf::Keyboard::R:
				keyR = vKeyboard->at(i).second;	break;
                
            case sf::Keyboard::T:
				keyT = vKeyboard->at(i).second;	break;
                
            case sf::Keyboard::M:
				keyM = vKeyboard->at(i).second;	break;
                
            case sf::Keyboard::Space:
				keySpace = vKeyboard->at(i).second;	break;
                
		}
	}
	
	vKeyboard->clear();
	
    lastMouseLeft = mouseLeft;
    lastMouseRight = mouseRight;
    
	// Raton
	for (int i=0; i < vMouse->size(); i++)
	{
		switch(vMouse->at(i).first)
		{
			case sf::Mouse::Left:
				mouseLeft = vMouse->at(i).second;	break;
			case sf::Mouse::Right:
				mouseRight = vMouse->at(i).second;	break;
		}
	}
	
	vMouse->clear();
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