/******************************************/
/*           ANIMATEDSPRITE.HPP           */
/******************************************/

#include "AnimatedSprite.h"
#include <iostream>

AnimatedSprite::AnimatedSprite(Time frameTime, SpriteSheet* spriteSheet, bool paused, bool looped)
{
    m_animation = new Animation("defAnim", spriteSheet, 0, 0, 0.0, false, false );
    m_currentFrame = 0;
    m_isPaused = paused;
    m_isLooped = looped;
    m_texture = spriteSheet->GetTexture();
    m_frameTime = new Time(frameTime.AsSeconds());
    m_currentTime = new Time();
    rect = new sf::IntRect(0, 0, 0, 0);
}

AnimatedSprite::~AnimatedSprite()
{
    delete m_frameTime;
    delete m_currentTime;
    delete rect;
}

void AnimatedSprite::SetAnimation(Animation* animation)
{
    m_animation = animation;
    m_texture = m_animation->GetSpriteSheetTexture();
    m_currentFrame = 0;
    SetFrame(m_currentFrame);
}

void AnimatedSprite::SetFrameTime(const Time& time)
{
    m_frameTime->SetSeconds(time.AsSeconds());
}

void AnimatedSprite::Play()
{
    m_isPaused = false;
}

void AnimatedSprite::Pause()
{
    m_isPaused = true;
}

void AnimatedSprite::Stop()
{
    m_isPaused = true;
    m_currentFrame = 0;
    SetFrame(m_currentFrame);
}

void AnimatedSprite::SetLooped(bool looped)
{
    m_isLooped = looped;
}

Animation* AnimatedSprite::GetAnimation() const
{
    return m_animation;
}

bool AnimatedSprite::IsLooped() const
{
    return m_isLooped;
}

bool AnimatedSprite::IsPlaying() const
{
    return !m_isPaused;
}

Time AnimatedSprite::GetFrameTime() const
{
    return *m_frameTime;
}

sf::IntRect AnimatedSprite::SetFrame(std::size_t newFrame, bool resetTime)
{
    if (m_animation)
    {
        //Calculamos la posicion de los vertices del frame y sus coordenadas de texturas
        return m_animation->GetFrame(newFrame);  
    }

    if (resetTime)
        m_currentTime->SetSeconds(0.0f);
}

sf::IntRect AnimatedSprite::GetSpriteRect()
{
    return *rect;
}

void AnimatedSprite::Update(const Time& deltaTime)
{
    //Si la animacion esta pausada y es valida
    if (!m_isPaused && m_animation)
    {
        //Incrementamos el tiempo actual
        *m_currentTime += deltaTime.AsSeconds();

        //Si el tiempo actual es mayor que el tiempo de avance dl frame
        if (m_currentTime->AsMicroSeconds() >= m_frameTime->AsMicroSeconds())
        {
            //Reseteamos el tiempo (nos quedamos con el resto))
            m_currentTime->SetMicroSeconds(m_currentTime->AsMicroSeconds() % m_frameTime->AsMicroSeconds());

            //Nos guardamos el indice del siguiente frame
            if (m_currentFrame + 1 < m_animation->GetNumFrames())
                m_currentFrame++;
            else
            {
                //Si la animacion ha finalizado reseteamos la animacion y la pausamos
                m_currentFrame = 0;

                if (!m_isLooped)
                {
                    m_isPaused = true;
                }

            }

            //Fijamos el frame actual (sin resetear el tiempo))
            sf::IntRect rectAux = SetFrame(m_currentFrame, false);
            
            SetRect(rectAux);
        }
    }
}

void AnimatedSprite::SetRect(const sf::IntRect& rectAux)
{
    rect->left = rectAux.left;
    rect->height = rectAux.height;
    rect->top = rectAux.top;
    rect->width = rectAux.width;
}
