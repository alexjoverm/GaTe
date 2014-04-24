/* 
 * File:   InputManager.h
 * Author: linuxero
 *
 * Created on April 14, 2014, 5:37 PM
 */

#ifndef INPUTMANAGER_H
#define	INPUTMANAGER_H
#include <SFML/Graphics.hpp>

class InputManager {
public:
	static InputManager* Instance(); // Método que habrá que llamar para crear el objeto
	
protected:
	InputManager();
	InputManager(const InputManager& orig);
	virtual ~InputManager();
	
public:
	void AddKeyboardKey(sf::Keyboard::Key key,	bool pressed);
	void AddMouseKey(sf::Mouse::Button key,		bool pressed);
	
	void Process(sf::Event event); // Bucle de gestión de los eventos
	void Update(); // Se encarga de actualizar las variables según lo que haya en los arrays
	
	// Booleanas a modo de "Propiedades"
	bool	keyW, keyA, keyS, keyD, keyR, keyT;
	bool	mouseLeft, mouseRight;
	
private:
	static InputManager* instance;

	std::vector< std::pair<sf::Keyboard::Key , bool>>	*vKeyboard;
	std::vector< std::pair<sf::Mouse::Button , bool>>	*vMouse;
};

#endif	/* INPUTMANAGER_H */

