/* 
 * File:   Button.cpp
 * Author: aba
 * 
 * Created on April 23, 2014, 2:05 AM
 */

#include "Button.h"
#include "../Managers/ResourceManager.h"

Button::Button(float x, float y, std::string contenido, std::string fuente) {
    
    texto = new sf::Text();
    controlSound =false;
    
    texto->setFont(ResourceManager::Instance()->GetFont(fuente));
    texto->setCharacterSize(28);
    texto->setColor(sf::Color::White);
    
    texto->setPosition(x, y);
    texto->setString(contenido);
    
}

Button::Button(const Button& orig) {
}

Button::~Button() {
    delete texto;
}



void Button::Draw(float interp){

  RenderWindow::Instance()->Draw(*texto);
}
 

 void Button::Update(const Time& timeElapsed){
    
    sf::Event event;
    sf::Vector2i MousePos=sf::Mouse::getPosition(*RenderWindow::Instance()->renderWindow);

    
    
    if(IsPressed(MousePos.x, MousePos.y) && !controlSound){
            SoundPlayer::Instance()->Play("hover");
            controlSound = true;
    }
    else
            controlSound =false;
    
    
    
   if(texto->getGlobalBounds().contains(sf::Vector2f((float)MousePos.x, (float)MousePos.y)))
       texto->setStyle(sf::Text::Bold);
   else
       texto->setStyle(sf::Text::Regular);
}
 

 
Vector Button::GetPosition() const{ 
      return Vector(texto->getPosition().x, texto->getPosition().y);
}
  

void Button::SetPosition(float x, float y){
   texto->setPosition(x, y);
}
  
void Button::SetFont(std::string fuente){     
    texto->setFont(ResourceManager::Instance()->GetFont(fuente));
}
  
void Button::SetText(std::string text){
    texto->setString(text);
}


void Button::Center(){
    texto->setOrigin(texto->getGlobalBounds().width/2, texto->getGlobalBounds().height/2);
    texto->setPosition(texto->getPosition().x, texto->getPosition().y);
}



   
