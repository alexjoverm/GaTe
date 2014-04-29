/* 
 * File:   Tower.cpp
 * Author: jc
 * 
 * Created on 19 de marzo de 2014, 10:41
 */

#include "Tower.h"
#include "../States/WorldState.h"
#include "Player.h"
#include "../Otros/StringUtils.h"
#include "../Managers/StateManager.h"
#include <iostream>

Tower::Tower(const sf::Texture& tex,const Vector pos, const float ran): EntPassive(tex) {
    
    this->SetPosition(pos);
    
    if(ran > 0)         
        range = ran;
    else
        range = 50.0;
    
    range_area.setRadius(range);
    range_area.setFillColor(green);
    range_area.setOrigin(range_area.getLocalBounds().width/2 , range_area.getLocalBounds().height/2);
    range_area.setPosition(pos.GetX()+this->spriteSheet->GetTexture()->getSize().x/2,pos.GetY()+this->spriteSheet->GetTexture()->getSize().y/2);
    
    lifeTime = new Time();
    reloadTime = new Time();
    
    reloadTime->SetSeconds(1.2f);
    
    clockReloadTower = new Clock();
    clockReloadTower->Restart();
    
    vEnemies = new std::deque<Enemy*>();

}

Tower::Tower(const Tower& orig): EntPassive(orig) {
}

Tower::~Tower() {
    
    delete lifeTime;
    lifeTime = NULL;

    delete reloadTime;
    reloadTime = NULL;
    
    delete clockReloadTower;
    clockReloadTower = NULL;
    
    vEnemies->clear();
    delete vEnemies; vEnemies=NULL;
}


void Tower::SetPosition(const Vector& v)
{ 
    spriteSheet->SetPosition(v); 
    range_area.setPosition(
        spriteSheet->GetPosition().GetX() + spriteSheet->getGlobalBounds().GetWidth()/2,
        spriteSheet->GetPosition().GetY() + spriteSheet->getGlobalBounds().GetHeight()/2
    );
}



void Tower::Shot(){
	
    if(!vEnemies->empty() && vEnemies->front() != NULL){
        if(clockReloadTower->GetElapsedTime().AsSeconds() >= reloadTime->AsSeconds()){
            WorldState* w = WorldState::Instance();
            int dirX = 1,dirY = 1;
            
            //POR MEJORAR
            
            // Dirección de bala
            Rectangle rect = vEnemies->front()->GetRectangleColisionAbsolute();
            
            // Posicion del enemido
            Vector posEnem = Vector();
            posEnem = rect.GetTopLeft();
            posEnem.SetY(posEnem.GetY() + rect.GetHeight()/2);
            
            // Dirección del vector, normalizado y multiplicado por velocidad
            posEnem -= this->GetPosition();
            posEnem = posEnem.GetNormalize();
            posEnem *= 800.f;

            Bullet* aux = new Bullet(ResourceManager::Instance()->GetTexture("texBullet"), this->GetPosition(), posEnem);

            
            w->AddBullet(aux);
            clockReloadTower->Restart();
            
            SoundPlayer::Instance()->Play("shot_torreta");
        }
    }
}



bool Tower::OnRange(float x, float y){
    
    
    float res = sqrt( ( pow( this->spriteSheet->GetPosition().GetX()-x , 2.0 ) + ( pow( this->spriteSheet->GetPosition().GetY() - y,2.0 ) ) ) );
    
    if(res <= range){
        return true;
    }else{
        return false;}
}




int Tower::SearchEnemy(Enemy* toSearch){
    
    int res = -1;

    for(int i = 0 ; i < vEnemies->size() ; i++){

        if(vEnemies->at(i) != NULL && vEnemies->at(i) == toSearch){
            return i;
        }
    }
    
    return res;
}

void Tower::CheckEnemies (){
    
    vGlobalEnemies = WorldState::Instance()->vEnemies;

        int in = 0 , encontrado = 0;

        for(int i= 0; i < vGlobalEnemies->size(); i++){
            
            if(i<vGlobalEnemies->size() && vGlobalEnemies->at(i) != NULL)
            {
                if(OnRange( vGlobalEnemies->at(i)->GetPosition().GetX() , vGlobalEnemies->at(i)->GetPosition().GetY() )
                   || OnRange( vGlobalEnemies->at(i)->GetPosition().GetX() + vGlobalEnemies->at(i)->GetRectangleColisionAbsolute().GetWidth(), vGlobalEnemies->at(i)->GetPosition().GetY() )
                   || OnRange( vGlobalEnemies->at(i)->GetPosition().GetX() , vGlobalEnemies->at(i)->GetPosition().GetY() + vGlobalEnemies->at(i)->GetRectangleColisionAbsolute().GetHeight())
                   || OnRange( vGlobalEnemies->at(i)->GetPosition().GetX() + vGlobalEnemies->at(i)->GetRectangleColisionAbsolute().GetWidth(), vGlobalEnemies->at(i)->GetPosition().GetY() + vGlobalEnemies->at(i)->GetRectangleColisionAbsolute().GetHeight())
                )
                    in = true;

                if(i<vGlobalEnemies->size() && vGlobalEnemies->at(i) != NULL)
                    encontrado = SearchEnemy(vGlobalEnemies->at(i));
                
               // Si esta dentro de rango
                if(in){
                    // Buscamos si ya esta en el vector
                // si no se encuentra, se añade
                    if(encontrado == -1 && i<vGlobalEnemies->size() && vGlobalEnemies->at(i) != NULL){
                        vEnemies->push_back(vGlobalEnemies->at(i));  
                    }
                }
                else{
                    // Si se encuentra se quita
                    if(encontrado != -1){
                        vEnemies->erase(vEnemies->begin()+encontrado);
                    }
                } 
            }
        }

        if( !vEnemies->empty() ){
            //this->Shot()
            range_area.setFillColor(red);
        }
        else
            range_area.setFillColor(green);
}


 void Tower::Draw(RenderWindow& window){
     
    if(WorldState::Instance()->showTowerRange || StateManager::Instance()->currentState == States::ID::TowerSelectionState){
        window.renderWindow->draw(range_area);
    }
     
    window.Draw(*(this->spriteSheet));
}



void Tower::Update(const Time& elapsedTime){
    CheckEnemies();
    Shot();
}

