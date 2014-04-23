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


class HUD {
public:
    HUD(float alto, std::string fuente);
    HUD(const HUD& orig);
    virtual ~HUD();
    
    // Bucle de ciclo de vida
    virtual void Draw(RenderWindow& window);
    virtual void Update(const Time& elapsedTime);
    
    void SubstractLife(float value){ barravida->Restar(value); }
    
private:
    

    SpriteSheet*         menuHUD;
    sf::Text*           nivel;
    Lifebar*            barravida;
    
    
    
    float alto;
    
    //Time* tiempo;
    
    
    
};

#endif	/* HUD_H */

