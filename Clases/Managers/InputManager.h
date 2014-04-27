/* 
 * File:   InputManager.h
 * Author: linuxero
 *
 * Created on April 14, 2014, 5:37 PM
 */

#ifndef INPUTMANAGER_H
#define	INPUTMANAGER_H
#include <SFML/Graphics.hpp>
#include "../Otros/Vector.h"

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
    
// Mouse
    Vector GetMousePosition() const;
    
    
// Getters
    bool IsClickedKeyA(){ return (keyA && !lastKeyA); }
    bool IsPressedKeyA(){ return keyA; }
    bool IsReleasedKeyA(){ return (!keyA && lastKeyA); }
    
    bool IsClickedKeyS(){ return (keyS && !lastKeyS); }
    bool IsPressedKeyS(){ return keyS; }
    bool IsReleasedKeyS(){ return (!keyS && lastKeyS); }
    
    bool IsClickedKeyD(){ return (keyD && !lastKeyD); }
    bool IsPressedKeyD(){ return keyD; }
    bool IsReleasedKeyD(){ return (!keyD && lastKeyD); }
    
    bool IsClickedKeyW(){ return (keyW && !lastKeyW); }
    bool IsPressedKeyW(){ return keyW; }
    bool IsReleasedKeyW(){ return (!keyW && lastKeyW); }
    
    bool IsClickedKeyM(){ return (keyM && !lastKeyM); }
    bool IsPressedKeyM(){ return keyM; }
    bool IsReleasedKeyM(){ return (!keyM && lastKeyM); }
    
    bool IsClickedKeyR(){ return (keyR && !lastKeyR); }
    bool IsPressedKeyR(){ return keyR; }
    bool IsReleasedKeyR(){ return (!keyR && lastKeyR); }
    
    bool IsClickedKeyT(){ return (keyT && !lastKeyT); }
    bool IsPressedKeyT(){ return keyT; }
    bool IsTeleasedKeyT(){ return (!keyT && lastKeyT); }
    
    bool IsClickedKeySpace(){ return (keySpace && !lastKeySpace); }
    bool IsPressedKeySpace(){ return keySpace; }
    bool IsReleasedKeySpace(){ return (!keySpace && lastKeySpace); }
    
    bool IsClickedMouseLeft(){ return (mouseLeft && !lastMouseLeft); }
    bool IsPressedMouseLeft(){ return mouseLeft; }
    bool IsReleasedMouseLeft(){ return (!mouseLeft && lastMouseLeft); }
    
    bool IsClickedMouseRight(){ return (mouseRight && !lastMouseRight); }
    bool IsPressedMouseRight(){ return mouseRight; }
    bool IsReleasedMouseRight(){ return (!mouseRight && lastMouseRight); }
	
    
private:
	static InputManager* instance;
    
    	// Booleanas a modo de "Propiedades"
	bool	keyW, keyA, keyS, keyD, keyM, keyT, keyR, keySpace ;
    bool	lastKeyW, lastKeyA, lastKeyS, lastKeyD, lastKeyM, lastKeyT, lastKeyR, lastKeySpace;  //Para comprobar pulsacion por click
	
    bool	mouseLeft, mouseRight;
    bool    lastMouseLeft, lastMouseRight;
    float   mousePosX, mousePosY;

	std::vector< std::pair<sf::Keyboard::Key , bool>>	*vKeyboard;
	std::vector< std::pair<sf::Mouse::Button , bool>>	*vMouse;
};

#endif	/* INPUTMANAGER_H */

