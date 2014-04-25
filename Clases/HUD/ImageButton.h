/* 
 * File:   ImageButton.h
 * Author: aba
 *
 * Created on April 24, 2014, 2:04 AM
 */

#ifndef IMAGEBUTTON_H
#define	IMAGEBUTTON_H

#include "../Motor2D/RenderWindow.h"
#include "../Otros/Time.h"

namespace ButtonType{
    enum Type{
        DualClick, DualHover, Three
    };
}


class ImageButton {
public:
    ImageButton(int x, int y, int num, const sf::Texture& tex, ButtonType::Type t = ButtonType::Type::DualClick);
    ImageButton(const ImageButton& orig);
    virtual ~ImageButton();
    
    
    // Bucle de ciclo de vida
    virtual void Draw(RenderWindow& window);
    virtual void Update(const Time& timeElapsed);

    void SetFrame(int frame);
    void SetPosition(float x, float y);
 
    //Nº de tiles en el SpriteSheet
    int   maxFrames;
    int   currentFrame;
    ButtonType::Type  type;
    
private:

    SpriteSheet*    imageButton;
    
        
};

#endif	/* IMAGEBUTTON_H */

