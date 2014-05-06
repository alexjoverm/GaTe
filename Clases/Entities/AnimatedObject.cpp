/* 
 * File:   AnimatedObject.cpp
 * Author: jmsm30
 * 
 * Created on 28 de abril de 2014, 3:37
 */

#include "AnimatedObject.h"
#include <iostream>

AnimatedObject::AnimatedObject(const sf::Texture& tex, const Vector& size) :EntPassive(tex), Animable(spriteSheet) {
    
        this->SetSizeTile((int)size.GetX(), (int)size.GetY());
        this->GetSprite()->SetNumRowsColumns();
    
}

AnimatedObject::AnimatedObject(const AnimatedObject& orig) :EntPassive(orig), Animable(spriteSheet) {
    
}

AnimatedObject::~AnimatedObject() {
}


void AnimatedObject::Update(const Time& elapsedTime){

    // Animaciones
    if(this->InitAnim())
       this->GetAnimatedSprite()->Update(elapsedTime,false);
    
    this->spriteSheet->GetSprite()->setTextureRect(this->GetAnimatedSprite()->GetSpriteRect());
        
}


void AnimatedObject::Draw(RenderWindow& window){
    
    window.Draw(*this->spriteSheet);

}


