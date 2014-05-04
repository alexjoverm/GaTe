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

    bool IsClickedKeyA(){ return (keyA == 3 || keyA==2 && lastKeyA==1); }
    bool IsPressedKeyA(){ return (keyA >= 2); }
    bool IsReleasedKeyA(){ return (keyA == 1); }
    
    bool IsClickedKeyS(){ return (keyS == 3 || keyS==2 && lastKeyS==1); }
    bool IsPressedKeyS(){ return (keyS >= 2); }
    bool IsReleasedKeyS(){ return (keyS == 1); }
    
    bool IsClickedKeyD(){ return (keyD == 3 || keyD==2 && lastKeyD==1); }
    bool IsPressedKeyD(){ return (keyD >= 2); }
    bool IsReleasedKeyD(){ return (keyD == 1); }
    
    bool IsClickedKeyW(){ return (keyW == 3 || keyW==2 && lastKeyW==1); }
    bool IsPressedKeyW(){ return (keyW >= 2); }
    bool IsReleasedKeyW(){ return (keyW == 1); }
    
    bool IsClickedKeyM(){ return (keyM == 3 || keyM==2 && lastKeyM==1); }
    bool IsPressedKeyM(){ return (keyM >= 2); }
    bool IsReleasedKeyM(){ return (keyM == 1); }
    
    bool IsClickedKeyR(){ return (keyR == 3 || keyR==2 && lastKeyR==1); }
    bool IsPressedKeyR(){ return (keyR >= 2); }
    bool IsReleasedKeyR(){ return (keyR == 1); }
    
    bool IsClickedKeyT(){ return (keyT == 3 || keyT==2 && lastKeyT==1); }
    bool IsPressedKeyT(){ return (keyT >= 2); }
    bool IsTeleasedKeyT(){ return (keyT == 1); }
    
    bool IsClickedKeyP(){ return (keyP == 3 || keyP==2 && lastKeyP==1); }
    bool IsPressedKeyP(){ return (keyP >= 2); }
    bool IsReleasedKeyP(){ return (keyP == 1); }
    
    bool IsClickedKeySpace(){ return (keySpace == 3 || keySpace==2 && lastKeySpace==1); }
    bool IsPressedKeySpace(){ return (keySpace >= 2); }
    bool IsReleasedKeySpace(){ return (keySpace == 1); }
    
    bool IsClickedMouseLeft(){ return (mouseLeft == 3 || mouseLeft==2 && lastMouseLeft==1); }
    bool IsPressedMouseLeft(){ return (mouseLeft >= 2); }
    bool IsReleasedMouseLeft(){ return (mouseLeft == 1); }
    
    bool IsClickedMouseRight(){ return (mouseRight == 3 || mouseRight==2 && lastMouseRight==1); }
    bool IsPressedMouseRight(){ return (mouseRight >= 2); }
    bool IsReleasedMouseRight(){ return (mouseRight == 1); }
	
    
private:
	static InputManager* instance;
    
    // Variables BYTE para comprobar pulsaciones, mediante técnica binaria
    
        // keyX == 0 : no hay evento para esa tecla
        // keyX == 1 : ha habido un evento de release
        // keyX == 2 : ha habido un evento de press
        // keyX == 3 : ha habido un evento de release y uno de press == CLICK
    
	unsigned short int keyW=1, keyA=1, keyS=1, keyD=1, keyM=1, keyT=1, keyR=1, keyP=1, keySpace=1;
    unsigned short int mouseLeft=1, mouseRight=1;
    
    unsigned short int lastKeyW=1, lastKeyA=1, lastKeyS=1, lastKeyD=1, lastKeyM=1, lastKeyT=1, lastKeyR=1, lastKeyP=1, lastKeySpace=1;
	unsigned short int lastMouseLeft=1, lastMouseRight=1;
    
    float   mousePosX, mousePosY;

	std::vector< std::pair<sf::Keyboard::Key , bool>>	*vKeyboard;
	std::vector< std::pair<sf::Mouse::Button , bool>>	*vMouse;
};

#endif	/* INPUTMANAGER_H */

