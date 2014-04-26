/* 
 * File:   ImageButton.cpp
 * Author: aba
 * 
 * Created on April 24, 2014, 2:04 AM
 */

#include "ImageButton.h"
#include "../Animations/SpriteSheet.h"
#include "../Otros/StringUtils.h"
#include "../MotorPhysics/Maths.h"
#include "../Managers/InputManager.h"


ImageButton::ImageButton(int x, int y, int num, const sf::Texture& tex, ButtonType::Type t) { 
    
    imageButton   = new SpriteSheet(tex);
    imageButton->SetPosition(Vector(x, y));
    maxFrames = num;
    
    imageButton->SetWidthTile(imageButton->getGlobalBounds().GetWidth() / maxFrames);
    imageButton->SetHeightTile(imageButton->getGlobalBounds().GetHeight());
    
    sf::IntRect rect(0, 0, imageButton->GetSizeTile().GetX(), imageButton->GetSizeTile().GetY());
    imageButton->GetSprite()->setTextureRect(rect);  
    SetFrame(0);
    currentFrame = 0;
    
    type = t;
}

ImageButton::ImageButton(const ImageButton& orig) {
}

ImageButton::~ImageButton() {
    delete imageButton;
}

 void ImageButton::Draw(RenderWindow& window){
    
    window.Draw(*imageButton);
}

bool ImageButton::IsHover(){
    InputManager* im = InputManager::Instance();
    Vector mousePos = im->GetMousePosition();
    
    return imageButton->getGlobalBounds().IsInside(Vector(mousePos.GetX(), mousePos.GetY()));
}

bool ImageButton::IsClicked(){
    return (IsHover() && InputManager::Instance()->IsClickedMouseLeft());
}

void ImageButton::Update(const Time& timeElapsed){
  /*  
    InputManager* im = InputManager::Instance();
    Vector mousePos = im->GetMousePosition();

    if(imageButton->getGlobalBounds().IsInside(Vector(mousePos.GetX(), mousePos.GetY())))
    {
     // Boton DUAL CLICK
        if(type == ButtonType::Type::DualClick)
        {
            if(im->IsClickedMouseLeft()){
                if(currentFrame == 0)
                    SetFrame(1);
                else
                    SetFrame(0);
            }
        }
        
     // DUAL HOVER
        else if(type == ButtonType::Type::DualHover){
            if(currentFrame == 0)
                SetFrame(1);
            else
                SetFrame(0);
        }
            
    }*/
}
    

void ImageButton::SetFrame(int frame){
    if(frame<0 || frame>=maxFrames)
       throw std::string("El numero de frame " + StringUtils::ConvertInt(frame) + " está fuera del rango");
         
    else{
        currentFrame = frame;
        sf::IntRect rect((int)(imageButton->GetSizeTile().GetX()*frame), 0, (int)(imageButton->GetSizeTile().GetX()), imageButton->GetSizeTile().GetY());
        imageButton->GetSprite()->setTextureRect(rect);
    }
}

void ImageButton::SetPosition(float x, float y){
    
    imageButton->SetPosition(Vector(x,y));
}