/* 
 * File:   Button.h
 * Author: aba
 *
 * Created on April 23, 2014, 2:05 AM
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include <SFML/System/String.hpp>
#include "../Motor2D/RenderWindow.h"
#include "../Otros/Vector.h"
#include "../Otros/Time.h"



class Button {
public:
    Button(float width, float height, float x, float y, std::string contenido, std::string fuente="Urban");
    Button(const Button& orig);
    virtual ~Button();
    
    
    
    virtual void Draw(float interp);
    virtual void Update(const Time& timeElapsed);
    
    void SetSize(float w, float h);
    Vector GetSize() const;
    void SetPosition(float x, float y);
    Vector GetPosition() const;
    void SetFont(std::string fuente);
    void SetFontSize(unsigned int s){ texto->setCharacterSize(s); }
    void SetText(std::string texto);
    void SetColor(sf::Color color);
    void SetBorderColor(sf::Color color);
    void SetBorderThickness(int borde);
    
    bool IsPressed(float x, float y){ return texto->getGlobalBounds().contains(sf::Vector2f(x,y)); }
    void Center();
    
    
private:
    
    sf::RectangleShape* rectangulo;  //Rectangulo no hará falta en un principio
    sf::Text*           texto;
    
    
};

#endif	/* BUTTON_H */

