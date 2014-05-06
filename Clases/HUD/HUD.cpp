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
    
    coins->SetPosition(Vector(770, 13));
    clock->SetPosition(Vector(290, 10));
    
    
    /*sf::IntRect rect(0, 0, 47, 50);
    coins->GetSprite()->setTextureRect(rect);  */
    
    barravida = new Lifebar( 450.f, 30.f, 280.f, 20.f, 5.f);
    
    
    soundButton = new ImageButton(950, 13, 2, ResourceManager::Instance()->GetTexture("texSounds"));
    musicButton = new ImageButton(1020, 10, 2, ResourceManager::Instance()->GetTexture("texMusic"));
    
    
    menuHUD->SetPosition(Vector(0.f,0.f));
     
    nivel   = new sf::Text();
    nivel->setString("Nivel: 1");
    nivel->setFont(ResourceManager::Instance()->GetFont(fuente));
    nivel->setPosition(20.f, 25.f);
    nivel->setCharacterSize(21);
    
    wave   = new sf::Text();
    wave->setString("Oleada: 1");
    wave->setFont(ResourceManager::Instance()->GetFont(fuente));
    wave->setPosition(125.f, 25.f);
    wave->setCharacterSize(21);
    
    tiempo   = new sf::Text();
    tiempo->setString("00");
    tiempo->setFont(ResourceManager::Instance()->GetFont(fuente));
    tiempo->setPosition(350.f, 25.f);
    tiempo->setCharacterSize(21);
    
    credito   = new sf::Text();
    credito->setString("0 $");
    credito->setFont(ResourceManager::Instance()->GetFont(fuente));
    credito->setPosition(830.f, 23.f);
    credito->setCharacterSize(22);
    
}

HUD::HUD(const HUD& orig) {
}

HUD::~HUD() {
    delete menuHUD; menuHUD = NULL;
    delete nivel; nivel = NULL;
    delete barravida; barravida = NULL;
    delete soundButton; soundButton = NULL;
    delete musicButton; musicButton = NULL;
    delete coins; coins = NULL;
    delete clock; clock = NULL;
    delete wave; wave = NULL;
    delete tiempo; tiempo = NULL;
    delete credito; credito = NULL;
}


 void HUD::Draw(RenderWindow& window){
    
    window.Draw(*menuHUD);
    window.Draw(*nivel);
    window.Draw(*wave);
    window.Draw(*tiempo);
    window.Draw(*credito);
    barravida->Draw(window, 0.f);
    soundButton->Draw(window);
    musicButton->Draw(window);
    window.Draw(*clock);
    window.Draw(*coins);
    
}

void HUD::Update(const Time& elapsedTime){
    barravida->Update(elapsedTime);
    
    if(musicButton->IsClicked())
        ToogleMusicButton();
    
    if(soundButton->IsClicked())
        ToogleSoundButton();
    
        
    //musicButton->Update(elapsedTime);
    //soundButton->Update(elapsedTime);
}



void HUD::ToogleSoundButton(){
    if(soundButton->currentFrame==0)
        SetFrameSoundButton(1);
    else
        SetFrameSoundButton(0);
}

void HUD::ToogleMusicButton(){
    if(musicButton->currentFrame==0)
        SetFrameMusicButton(1);
    else
        SetFrameMusicButton(0);
}


void HUD::SetFrameSoundButton(int frame){
    if(frame==0)
        SoundPlayer::Instance()->active=false;
    else if(frame==1)
        SoundPlayer::Instance()->active=true;
        
    soundButton->SetFrame(frame);
}

void HUD::SetFrameMusicButton(int frame){
    if(frame==0)
        MusicPlayer::Instance()->DeActivate();
    else if(frame==1)
        MusicPlayer::Instance()->Activate();
        
    musicButton->SetFrame(frame);
}