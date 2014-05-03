/* 
 * File:   Lifebar.cpp
 * Author: aba
 * 
 * Created on April 22, 2014, 4:00 AM
 */

#include "Lifebar.h"
#include <iostream>

Lifebar::Lifebar(float x, float y, float width, float height,  int brd, bool colorChang) {
    vmax = 120.f;
    valor =vmax;
    
    lifebar = new sf::RectangleShape();
    lifebar->setSize(sf::Vector2f(width, height));
    lifebar->setFillColor(sf::Color::White);
    lifebar->setPosition(x, y);
    
    borde = new sf::RectangleShape();
    borde->setSize(sf::Vector2f(width, height ));
    borde->setFillColor(sf::Color::Transparent);
    borde->setOutlineThickness(brd);
    borde->setOutlineColor(sf::Color::Black);
    borde->setPosition(lifebar->getPosition());
    
    colorChange = colorChang;
}

Lifebar::Lifebar(const Lifebar& orig) {
}

Lifebar::~Lifebar() {
    delete lifebar;   lifebar = NULL;
    delete borde;     borde = NULL;
}



 void Lifebar::Draw(RenderWindow& window, float inter){
    
    window.Draw(*borde);
    window.Draw(*lifebar);
}
 
void Lifebar::Update(const Time& elapsedTime)
{
    //Ajustar tamaño             
    lifebar->setSize(sf::Vector2f((borde->getSize().x) * (valor/vmax), lifebar->getSize().y));

    //Cambio de color
    if(colorChange){
        if(valor/vmax<=0.3f)
            lifebar->setFillColor(sf::Color::Red);

        else if(valor/vmax<=0.7f)
            lifebar->setFillColor(sf::Color::Yellow);

        else 
            lifebar->setFillColor(sf::Color::Green);
    }
}



void Lifebar::Restar(float value){
    valor = valor - value;
    
    if(valor < 0.f)
        valor = 0.f;
}

void Lifebar::Rellenar(float value){   
    valor = valor+value;
    
    if(valor>vmax)
        valor = vmax;
}

void Lifebar::SetPercent(float percent){ 
    if(percent > 1.f)
        percent = 1.f;
    else if(percent < 0.f)
        percent = 0.f;
    
    valor = vmax * percent;
}


void Lifebar::SetPosition(float x, float y){ 
    lifebar->setPosition(x,y);
    borde->setPosition(x,y);
}



void Lifebar::SetLife(float life)
 {
     vmax = life;
     valor =vmax;
 }
