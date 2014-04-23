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
    texto->setCharacterSize(16);
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



  void Button::Draw(RenderWindow& window){
    
    window.Draw(*rectangulo);
    window.Draw(*texto);
 
  
  
    
}
 
 

 void Button::Update(RenderWindow& window){
    
    sf::Event event;
    sf::Vector2i MousePos=sf::Mouse::getPosition(*window.renderWindow);

   if(rectangulo->getGlobalBounds().contains(sf::Vector2f((float)MousePos.x, (float)MousePos.y))){
        texto->setStyle(sf::Text::Bold );
        if(event.type==sf::Event::MouseButtonPressed){
            if(event.mouseButton.button==sf::Mouse::Left)
                texto->setStyle(sf::Text::Regular );
            
        }
        
    }
    

    
}
 
 
 
 
 void Button::SetSize(float w, float h){
    float margen_v = h*0.2;
    float margen_h = w*0.2-((w/2)/2);;
    
    rectangulo->setSize(sf::Vector2f(w, h));
    texto->setPosition(rectangulo->getSize().x+margen_h, rectangulo->getSize().y+margen_v);
    
 }
 
  sf::Vector2f Button::GetSize(){
      
      return rectangulo->getSize();
 }
 
  
 void Button::SetPosition(float x, float y){
    float margen_v = (GetSize().y)*0.2;
    float margen_h = (GetSize().x)*0.2-(((GetSize().x)/2)/2);;
    
    rectangulo->setPosition(sf::Vector2f(x, y));
    texto->setPosition(rectangulo->getSize().x+margen_h, rectangulo->getSize().y+margen_v);
    
 }
   
   
  sf::Vector2f Button::GetPosition(){
      
      return rectangulo->getPosition();
  }
  
  
  
  void Button::SetFont(std::string fuente){
      
      texto->setFont(ResourceManager::Instance()->GetFont(fuente));
  }
  
  
  void Button::SetText(std::string text){
     
      texto->setString(text);
      
  }
  
  
  
  void Button::SetTexture(){
      
      
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