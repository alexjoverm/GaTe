/******************************************/
/*              ANIMABLE.CPP             */
/******************************************/

#include "Animable.h"
#include <iostream>

Animable::Animable(SpriteSheet* spriteSheet)
{
    m_spriteSheet = spriteSheet;
    m_animaciones = new std::vector<Animation*>();
    m_animatedSprite = new AnimatedSprite(Time(2.0f), m_spriteSheet, false, false);
}

Animable::~Animable()
{
    while(!m_animaciones->empty()) 
		delete m_animaciones->back(), m_animaciones->pop_back();
	delete m_animaciones;  m_animaciones = NULL;
    
    delete m_animatedSprite;  m_animatedSprite = NULL;
}

void Animable::AddAnimation(Animation* animation)
{
    bool encontrado = false;
    for(unsigned int i = 0; i < m_animaciones->size(); i++)
        if(m_animaciones->at(i)->GetAnimationName() == animation->GetAnimationName())
            encontrado = true;
       
    if(!encontrado)
         m_animaciones->push_back(animation);
    
    else std::cout << "No se ha podido añadir la animacion: ya existe una animacion con ese nombre" << std::endl;
}

void Animable::AddAnimation(std::vector<Animation*>* animations)
{
    if(animations->size() > 0)
    {
        bool encontrado = false;
        
        for(unsigned int i = 0; i < animations->size(); i++)
        {
            for(unsigned int j = 0; j < m_animaciones->size() && !encontrado; j++)
                if(m_animaciones->at(j)->GetAnimationName() == animations->at(i)->GetAnimationName())
                    encontrado = true;
                
            if(!encontrado) 
                m_animaciones->push_back(animations->at(i));
            
            encontrado = false;
        }
    }
}

Animation* Animable::GetAnimation(std::string nombre) const
{
    try
    {
        if(m_animaciones->size() > 0)
        {
            bool encontrado = false;
            for(unsigned int i = 0; i < m_animaciones->size(); i++)
            {
                if(m_animaciones->at(i)->GetAnimationName() == nombre)
                {
                    encontrado = true;
                    return m_animaciones->at(i);
                }
            }
            if(!encontrado)  throw std::string("La animacion " + nombre + " no existe en el vector de animaciones.");
        }
    }
    catch (std::string msg)
    {
        std::cout << "Error: " << msg << std::endl;
    }
}

void Animable::SetCurrentAnimation(std::string nombre, SpriteSheet* sp)
{
    try
    {
        bool encontrado = false;
        
        for(int i = 0; i < m_animaciones->size() && !encontrado; i++)
        {
            if(m_animaciones->at(i)->GetAnimationName() == nombre)
            {
                encontrado = true;
                if(this->GetCurrentAnimation() != NULL && m_animaciones->at(i)->GetAnimationName() != this->GetCurrentAnimation()->GetAnimationName())
                {
                   //Velocidad por defecto, falta añadir parametros
                    Animation* animation = this->GetAnimation(nombre);
                    Time tiempoFrame = Time(animation->GetAnimSpeed());
                    m_animatedSprite->SetFrameTime(tiempoFrame);
                    m_animatedSprite->SetLooped(animation->GetLoop());
                    m_animatedSprite->SetPaused(animation->GetPause());
                    m_animatedSprite->SetAnimation(animation);

                    sf::IntRect rect = m_animatedSprite->SetFrame(0, false);
                    m_animatedSprite->SetRect(rect, isReverse);
                    sp->GetSprite()->setTextureRect(rect);
                }
            }
        }
        if(!encontrado) throw std::string("La animacion " + nombre + "no existe en el vector de animaciones");
    }
    catch(std::string msg)
    {
        std::cout << "Error: " << msg << std::endl;
    }
}

Animation* Animable::GetCurrentAnimation() const
{
        return m_animatedSprite->GetAnimation();
}

void Animable::PlayAnimation()
{
    m_initAnim = true;
}

void Animable::StopAnimation()
{
    m_initAnim = false;
}

bool Animable::InitAnim()
{
    return m_initAnim;
}