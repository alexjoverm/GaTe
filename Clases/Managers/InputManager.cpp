/* 
 * File:   InputManager.cpp
 * Author: linuxero
 * 
 * Created on April 14, 2014, 5:37 PM
 */

#include "InputManager.h"
#include "../States/WorldState.h"

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
	
	keyW = keyA = keyS = keyD = mouseLeft = mouseRight = false;	
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
		}
	}
	
	vKeyboard->clear();
	
	// Raton
	for (int i=0; i < vMouse->size(); i++)
	{
		switch(vMouse->at(i).first)
		{
			case sf::Mouse::Left:
				mouseLeft = vKeyboard->at(i).second;	break;
			case sf::Mouse::Right:
				mouseRight = vKeyboard->at(i).second;	break;
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
			WorldState::Instance()->window->Close();
			break;

		// A tiempo real
		case sf::Event::MouseButtonPressed:
			// Habrá que comprobar el estado en el que está. De momento se lo damos al world
			WorldState::Instance()->AddRealEvent(event);
			break;
	}
}