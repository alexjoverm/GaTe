/* 
 * File:   HUD.h
 * Author: aba
 *
 * Created on April 22, 2014, 9:47 AM
 */

#ifndef HUD_H
#define	HUD_H


#include "../Otros/Time.h"
#include "../HUD/Lifebar.h"
#include "../Motor2D/RenderWindow.h"
#include "../HUD/ImageButton.h"

class HUD {
public:
    HUD(float alto, std::string fuente);
    HUD(const HUD& orig);
    virtual ~HUD();
    
    // Bucle de ciclo de vida
    virtual void Draw(RenderWindow& window);
    virtual void Update(const Time& elapsedTime);
    
    float GetHeight() const{ return menuHUD->getLocalBounds().GetHeight(); }
    
    //Lifebar
    void SubstractLife(float value){ barravida->Restar(value); }
    
    //ImageButton
    void SetFrameSoundButton(int frame){ soundButton->SetFrame(frame); }
    void SetFrameMusicButton(int frame){ musicButton->SetFrame(frame); }
    
private:
    

    SpriteSheet*        menuHUD;
    SpriteSheet*        coins;
    SpriteSheet*        clock;
    
    sf::Text*           nivel;
    Lifebar*            barravida;
    ImageButton*        soundButton;
    ImageButton*        musicButton;
    
    
    float alto;
    
    //Time* tiempo;
    
    
    
};

#endif	/* HUD_H */

