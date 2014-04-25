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
    coins = new SpriteSheet(ResourceManager::Instance()->GetTexture("texCoins"));
    clock = new SpriteSheet(ResourceManager::Instance()->GetTexture("texClock"));
    
    coins->SetPosition(Vector(770, 15));
    clock->SetPosition(Vector(250, 10));
    
    
    /*sf::IntRect rect(0, 0, 47, 50);
    coins->GetSprite()->setTextureRect(rect);  */
    
    
    nivel   = new sf::Text();
    barravida = new Lifebar(280.f, 20.f, 450.f, 30.f,  5.f);
    
    
    soundButton = new ImageButton(950, 13, 2, ResourceManager::Instance()->GetTexture("texSounds"));
    musicButton = new ImageButton(1020, 10, 2, ResourceManager::Instance()->GetTexture("texMusic"));
    
    
    menuHUD->SetPosition(Vector(0.f,0.f));
     
    nivel->setString("Nivel: 1            Oleada: 1");
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
    delete soundButton;
    delete musicButton;
    delete coins;
    delete clock;
}


 void HUD::Draw(RenderWindow& window){
    
    window.Draw(*menuHUD);
    window.Draw(*nivel);
    barravida->Draw(window, 0.f);
    soundButton->Draw(window);
    musicButton->Draw(window);
    window.Draw(*clock);
    window.Draw(*coins);
    
}

void HUD::Update(const Time& elapsedTime){
    barravida->Update(elapsedTime);
    musicButton->Update(elapsedTime);
    soundButton->Update(elapsedTime);
}