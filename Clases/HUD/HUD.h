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
    float GetLife() const { return barravida->valor; }
    
    //Textos
    void SetLevelText(const std::string text) { nivel->setString(text); }
    void SetWaveText(const std::string text) { wave->setString(text); }
    void SetTimeText(const std::string text) { tiempo->setString(text); }
    void SetCreditText(const std::string text){ credito->setString(text); }
    
    //Lifebar
    void SubstractLife(float value){ barravida->Restar(value); }
    
    //ImageButton
    void SetFrameSoundButton(int frame);
    void SetFrameMusicButton(int frame);
    
    void ToogleSoundButton();
    void ToogleMusicButton();
    
    
private:
    

    SpriteSheet*        menuHUD;
    SpriteSheet*        coins;
    SpriteSheet*        clock;
    
    sf::Text*           nivel;
    sf::Text*           wave;
    sf::Text*           tiempo;
    sf::Text*           credito;
    
    Lifebar*            barravida;
    ImageButton*        soundButton;
    ImageButton*        musicButton;
    
    
    float alto;
    
    //Time* tiempo;
    
    
    
};

#endif	/* HUD_H */

