/******************************************/
/*              ANIMATION.HPP             */
/******************************************/

#ifndef ANIMATION_H
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "SpriteSheet.h"
#include "../Otros/Rectangle.h"

class Animation
{
public:
    //initANim, tilesAnim, reverse
    Animation(std::string nombre, SpriteSheet* spriteSheet, int initAnim, int endAnim, float animSpeed, bool pause, bool loop);
    ~Animation();
    
    //void SetSpriteSheet(SpriteSheet& spriteSheet);                      //Fijamos el spritesheet de la animacion
    SpriteSheet* GetSpriteSheet();                                      //Devuelve el spritesheet de la animacion
    const sf::Texture* GetSpriteSheetTexture() const;                   //Devuelve la textura del spritesheet de la animacion
    sf::IntRect GetFrame(std::size_t n) const;                  //Devuelve un frame n de la animacion
    std::size_t GetNumFrames() const;                                   //Devuelve el numero de frames de la animacion                                                 //Devuelve si la animacion se reproduce al reves o no
    void InitAnim();
    void SetAnimationName(std::string nombre);
    std::string GetAnimationName() const;
    float GetAnimSpeed() const;
    bool GetPause() const;
    bool GetLoop() const;
    
    
private:
    std::vector<sf::IntRect>* m_frames;                                  //Frames de la animacion
    SpriteSheet* m_spriteSheet;                                         //Spritesheet de la animacion
    int m_initAnim;                                                     //Frame de inicio de la animacion
    int m_endAnim;                                                      //Frame final de la animacion
    std::string m_animationName;
    float m_animSpeed;
    bool m_pause;
    bool m_loop;
    void SetInitAnim(int initAnim);                                     //Fijamos el frame de inicio de la animacion
    void SetEndAnim(int endAnim);                                       //Fijamos el frame final de la animacion
    void SetFrames();
    
};

#endif	/* ANIMATION_HPP */
