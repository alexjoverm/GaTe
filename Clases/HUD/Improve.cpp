/* 
 * File:   Improve.cpp
 * Author: alejandrojovermorales
 * 
 * Created on May 11, 2014, 7:17 PM
 */

#include "Improve.h"
#include "../Managers/ResourceManager.h"
#include "../Otros/StringUtils.h"
#include "../Managers/StatusManager.h"

Improve::Improve(const Vector& pos, std::string title, Parameters::ID type) {
  
    improveType = type;
    
    int level = StatusManager::Instance()->GetInt(improveType);
    int price = StatusManager::Instance()->GetImprovePrice(improveType);
        
    position = new Vector(pos.GetX(), pos.GetY());
    
    textTitle = new sf::Text();
    textPrice = new sf::Text();
    
    levelBar = new Lifebar(pos.GetX() + 100.f, pos.GetY()+5.f, 150.f, 20.f, 3, false);
    levelBar->valor = level;
    levelBar->vmax = StatusManager::Instance()->GetInt(Parameters::maxLevelImproves);
    
    
    
    textTitle->setString(title);
    textTitle->setPosition(position->GetX(), position->GetY());
    textTitle->setFont(ResourceManager::Instance()->GetFont("Urban"));
    textTitle->setCharacterSize(19);
    
    textPrice->setString(StringUtils::ConvertInt(price) + " $");
    textPrice->setPosition(position->GetX() + 335.f, position->GetY());
    textPrice->setFont(ResourceManager::Instance()->GetFont("Urban"));
    textPrice->setCharacterSize(19);
    
    
    buttonPlus = new ImageButton(pos.GetX()+265.f, pos.GetY(), 1, ResourceManager::Instance()->GetTexture("iconPlus"));
}


Improve::~Improve() {
    delete position; position=NULL;
    delete textTitle; textTitle=NULL;
    delete textPrice; textPrice=NULL;
    delete levelBar; levelBar=NULL;
    delete buttonPlus; buttonPlus=NULL;
}



void Improve::SetLevel(int level, int price){
    if(level <= levelBar->vmax){
        levelBar->valor = level;
        textPrice->setString(StringUtils::ConvertInt(price) + " $");
    }
}


void Improve::Draw(){
    RenderWindow::Instance()->Draw(*textPrice);
    RenderWindow::Instance()->Draw(*textTitle);
    buttonPlus->Draw(*RenderWindow::Instance());
    levelBar->Draw(*RenderWindow::Instance(), 1);
}


void Improve::Update(const Time& elapsedTime){
    
    StatusManager* st = StatusManager::Instance();
    
    // Comprobamos pulsación, y actualizamos en tal caso
    if(this->IsClickedButtonPlus()){
        if(st->GetInt(Parameters::credit) - st->GetImprovePrice(improveType) >= 0.f
            && st->GetInt(improveType) < st->GetInt(Parameters::maxLevelImproves))
        {
            //Restamos dinero
            st->DecrementInt(Parameters::credit, st->GetImprovePrice(improveType)); 
            
            // Realizamos mejora en el Status
            st->IncrementInt(improveType, 1);
            this->SetLevel(st->GetInt(improveType) ,st->GetImprovePrice(improveType));
            
        }
    }
    
    levelBar->Update(elapsedTime);
}
