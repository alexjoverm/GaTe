#ifndef SLIDER_H
#define	SLIDER_H


#include "../Otros/Time.h"
#include "../Motor2D/RenderWindow.h"
#include "../Managers/InputManager.h"
#include "../MusicSounds/MusicPlayer.h"


class Slider {
public:
    Slider(float x, float y, float width, float height);
    Slider(const Slider& orig);
    virtual ~Slider();
    
    // Bucle de ciclo de vida
    virtual void Draw(RenderWindow& window);
    virtual void Update(const Time& elapsedTime);
    
    //Valor 
    void SetValue(float value);
    float CalculateValue();//Obtenemos un valor entero de 0 a 100

    
    //Posición
    void SetPosition(float x, float y);
    void SetPositionControl(float pos);
    Vector GetPosition() const;
    Vector GetPositionControl() const;
    
    //Ratón
    Vector CalculateMousePos(); 
    bool IsHover() const;
    bool IsPressed() const;

    
    //void SetVolume(int v);
    
    float valor;  
    float posicion;
       
    
private:
    
    sf::RectangleShape* barra;
    sf::RectangleShape* control;

   // Time* tiempo;
    
};

#endif	/* SLIDER_H */

