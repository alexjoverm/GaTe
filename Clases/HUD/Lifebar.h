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
    Lifebar(float x, float y, float width, float height,  int borde, bool colorChang=true);
    Lifebar(const Lifebar& orig);
    virtual ~Lifebar();
    
    
    // Bucle de ciclo de vida
    virtual void Draw(RenderWindow& window, float inter);
    virtual void Update(const Time& elapsedTime);
    
    //Valor de la barra
    void Rellenar(float value);
    void Restar(float value);
    void SetPercent(float percent);
    
    void SetPosition(float x, float y);
    void SetLife(float life);
     
    float vmax;  
    float valor;    
    
private:
    
    sf::RectangleShape* borde;
    sf::RectangleShape* lifebar;
    bool colorChange;
    
    Time* tiempo;
};

#endif	/* LIFEBAR_H */

