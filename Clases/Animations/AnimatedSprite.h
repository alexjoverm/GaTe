/******************************************/
/*           ANIMATEDSPRITE.HPP           */
/******************************************/

#ifndef ANIMATEDSPRITE_HPP
#define	ANIMATEDSPRITE_HPP

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "../Otros/Time.h"

class AnimatedSprite
{
public:
    explicit AnimatedSprite(Time frameTime, SpriteSheet* spriteSheet, bool paused, bool looped);
    ~AnimatedSprite();

    void Update(const Time& deltaTime);                                                    //Acutualizamos la animacion
    void SetAnimation(Animation* animation);                                      //Fijamos la animacion
    void SetFrameTime(const Time& time);                                                   //Fijamos el tiempo de cada frame
    void Play();                                                                        //Reproducimos
    void Pause();                                                                       //Pausamos la animacion
    void Stop();                                                                        //Pausamos la animacion y volvemos al frame de inicio
    void SetLooped(bool looped);                                                        //Fijamos loop                                           //Fijamos color
    Animation* GetAnimation() const;                                              //Devuelve la animacion
    bool IsLooped() const;                                                              //Devuele si esta activado el loop
    bool IsPlaying() const;                                                             //Devuelve si se esta ejecutando la animacion
    Time GetFrameTime() const;                                                      //Devuele el tiempo de cada frame
    sf::IntRect SetFrame(std::size_t newFrame, bool resetTime = true);                         //Fijamos el frame de animacion actual
    sf::IntRect GetSpriteRect();
    void SetPaused(bool paused) { m_isPaused = paused; };
    void SetRect(const sf::IntRect& rectAux);
    
private:
    Animation* m_animation;                                                       //Animacion del sprite
    Time* m_frameTime;                                                               //Tiempo de cada frame
    Time* m_currentTime;                                                             //Tiempo actual
    std::size_t m_currentFrame;                                                         //Frame actual de la animacion
    bool m_isPaused;                                                 //Animacion en puase
    bool m_isLooped;                                                                    //Animacion en bucle
    const sf::Texture* m_texture;     
    sf::IntRect* rect; //Rectangulo del sprite  
};

#endif	/* ANIMATEDSPRITE_HPP */
