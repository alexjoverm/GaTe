/* 
 * File:   Lifebar.h
 * Author: aba
 *
 * Created on April 22, 2014, 4:00 AM
 */

#ifndef LIFEBAR_H
#define	LIFEBAR_H


#include "../Otros/Time.h"
#include "../Motor2D/RenderWindow.h"
#include "../Managers/InputManager.h"

class Lifebar {
public:
    Lifebar(float width, float height, float x, float y,  int borde);
    Lifebar(const Lifebar& orig);
    virtual ~Lifebar();
    
    
    // Bucle de ciclo de vida
    virtual void Draw(RenderWindow& window, float inter);
    virtual void Update(const Time& elapsedTime);
    
    //Valor de la barra
    void Rellenar(float value);
    void Restar(float value);
    void SetPercent(float percent);
    
     
    float vmax;  
    float valor;    
    
private:
    
    sf::RectangleShape* borde;
    sf::RectangleShape* lifebar;
    
    Time* tiempo;
};

#endif	/* LIFEBAR_H */

