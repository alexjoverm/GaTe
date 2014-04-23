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



class Button {
public:
    Button(float width, float height, float x, float y, std::string contenido, std::string fuente);
    Button(const Button& orig);
    virtual ~Button();
    
    
    
    virtual void Draw(RenderWindow& window);
    virtual void Update(RenderWindow& window);
    
    void SetSize(float w, float h);
    sf::Vector2f GetSize();
    void SetPosition(float x, float y);
    sf::Vector2f GetPosition();
    void SetFont(std::string fuente);
    void SetText(std::string texto);
    void SetTexture();
    void SetColor(sf::Color color);
    void SetBorderColor(sf::Color color);
    void SetBorderThickness(int borde);
    
    
private:
    
    sf::RectangleShape* rectangulo;
    sf::Text*           texto;
    
    
};

#endif	/* BUTTON_H */

