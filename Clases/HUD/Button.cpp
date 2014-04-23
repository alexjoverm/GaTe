/* 
 * File:   Button.cpp
 * Author: aba
 * 
 * Created on April 23, 2014, 2:05 AM
 */

#include "Button.h"
#include "../Managers/ResourceManager.h"

Button::Button(float width, float height, float x, float y, std::string contenido, std::string fuente) {
    
    rectangulo = new sf::RectangleShape();
    texto = new sf::Text();
    
    float margen_v = height*0.2;
    float margen_h = width/2-((width/2)/2);
    
    rectangulo->setSize(sf::Vector2f(width, height));
    rectangulo->setPosition(sf::Vector2f(x, y));
    rectangulo->setFillColor(sf::Color::Blue);
    rectangulo->setOutlineThickness(3);
    rectangulo->setOutlineColor(sf::Color::White);
    
    
    texto->setFont(ResourceManager::Instance()->GetFont(fuente));
    texto->setCharacterSize(28);
    texto->setColor(sf::Color::White);
    
    texto->setPosition(x+margen_h, y+margen_v);
    texto->setString(contenido);
    
}

Button::Button(const Button& orig) {
}

Button::~Button() {
    delete rectangulo;
    delete texto;
}



void Button::Draw(float interp){

  RenderWindow::Instance()->Draw(*rectangulo);
  RenderWindow::Instance()->Draw(*texto);
}
 

 void Button::Update(const Time& timeElapsed){
    
    sf::Event event;
    sf::Vector2i MousePos=sf::Mouse::getPosition(*RenderWindow::Instance()->renderWindow);

   if(texto->getGlobalBounds().contains(sf::Vector2f((float)MousePos.x, (float)MousePos.y)))
        texto->setStyle(sf::Text::Bold );
   else
       texto->setStyle(sf::Text::Regular);
}
 
 
 
 
 void Button::SetSize(float w, float h){
    float margen_v = h*0.2;
    float margen_h = w*0.2-((w/2)/2);;
    
    rectangulo->setSize(sf::Vector2f(w, h));
    texto->setPosition(rectangulo->getSize().x+margen_h, rectangulo->getSize().y+margen_v);
    
 }
 
Vector Button::GetSize() const{
    return Vector(rectangulo->getSize().x, rectangulo->getSize().y);
}
 
Vector Button::GetPosition() const{ 
      return Vector(rectangulo->getPosition().x, rectangulo->getPosition().y);
}
  

void Button::SetPosition(float x, float y){
   float margen_v = (GetSize().GetX())*0.2;
   float margen_h = (GetSize().GetY())*0.2-(((GetSize().GetX())/2)/2);;

   rectangulo->setPosition(sf::Vector2f(x, y));
   texto->setPosition(rectangulo->getSize().x+margen_h, rectangulo->getSize().y+margen_v);
}
  
void Button::SetFont(std::string fuente){     
    texto->setFont(ResourceManager::Instance()->GetFont(fuente));
}
  
void Button::SetText(std::string text){
    texto->setString(text);
}

void Button::SetColor(sf::Color color){
    rectangulo->setFillColor(color);
}

void Button::SetBorderColor(sf::Color color){
  rectangulo->setOutlineColor(color);
}

void Button::SetBorderThickness(int borde){
  rectangulo->setOutlineThickness(borde);
}


void Button::Center(){
    texto->setOrigin(texto->getGlobalBounds().width/2, texto->getGlobalBounds().height/2);
    texto->setPosition(texto->getPosition().x, texto->getPosition().y);
}