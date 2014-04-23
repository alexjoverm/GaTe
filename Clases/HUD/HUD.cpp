/* 
 * File:   HUD.cpp
 * Author: aba
 * 
 * Created on April 22, 2014, 9:47 AM
 */

#include "HUD.h"
#include <iostream>
#include "../States/WorldState.h"



HUD::HUD(float alto, std::string fuente) {
    
    
    menuHUD = new SpriteSheet(ResourceManager::Instance()->GetTexture("texHUD"));
    nivel   = new sf::Text();
    barravida = new Lifebar(500.f, 20.f, 300.f, 30.f,  5.f);
    
    menuHUD->SetPosition(Vector(0.f,0.f));
    
    
    
    nivel->setString("Nivel: 1   Oleada: 1");
    nivel->setFont(ResourceManager::Instance()->GetFont(fuente));
    nivel->setPosition(30.f, 30.f);
    nivel->setCharacterSize(16);
    
}

HUD::HUD(const HUD& orig) {
}

HUD::~HUD() {
    delete menuHUD;
    delete nivel; 
    delete barravida;
}


 void HUD::Draw(RenderWindow& window){
    
    window.Draw(*menuHUD);
    window.Draw(*nivel);
    barravida->Draw(window, 0.f);
    
}

void HUD::Update(const Time& elapsedTime){
    barravida->Update(elapsedTime);
}