/* 
 * File:   Improve.cpp
 * Author: alejandrojovermorales
 * 
 * Created on May 11, 2014, 7:17 PM
 */

#include "ImproveGroup.h"
#include "../Managers/ResourceManager.h"

ImproveGroup::ImproveGroup(const Vector& pos, std::string title, const sf::Texture& tex) {
    
    vImproves = new std::vector<Improve*>();
    position = new Vector(pos.GetX(), pos.GetY());
    
    textTitle = new sf::Text();
    textTitle->setString(title);
    textTitle->setPosition(position->GetX() + 70.f, position->GetY());
    textTitle->setFont(ResourceManager::Instance()->GetFont("Urban"));
    textTitle->setCharacterSize(25);
    
    icon = new SpriteSheet(tex);
    icon->SetPosition(Vector(position->GetX(), position->GetY() - icon->getGlobalBounds().GetHeight()/2 + textTitle->getGlobalBounds().height/2));
}


ImproveGroup::~ImproveGroup() {
    while(!vImproves->empty()) 
		delete vImproves->back(), vImproves->pop_back();
	delete vImproves; vImproves=NULL;
}


void ImproveGroup::Update(const Time& timeElapsed){
    if(active)
    {
        for(int i=0; i<vImproves->size(); i++)
            vImproves->at(i)->Update(timeElapsed);
    }
}

void ImproveGroup::Draw(){
    if(active)
    {
        RenderWindow::Instance()->Draw(*textTitle);
        RenderWindow::Instance()->Draw(*icon);
        for(int i=0; i<vImproves->size(); i++)
            vImproves->at(i)->Draw();
    }
}


void ImproveGroup::CreateImprove(std::string title, Parameters::ID type){
    Vector aux = Vector(this->position->GetX()+20.f, this->position->GetY() + 50.f + (vImproves->size()*35.f));
    vImproves->push_back(new Improve(aux, title, type));
}
