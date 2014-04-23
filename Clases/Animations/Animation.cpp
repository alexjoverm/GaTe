/******************************************/
/*              ANIMATION.CPP             */
/******************************************/

#include "Animation.h"
#include <cmath>
#include <iostream>

/*Actualmente solo se soportan SpriteSheet con tiles del mismo tamaño*/

Animation::Animation(std::string nombre, SpriteSheet* spriteSheet, int initAnim, int endAnim, float animSpeed, bool pause, bool loop )
{
    m_spriteSheet = spriteSheet;
    m_animationName = nombre;
    m_initAnim = initAnim;
    m_endAnim = endAnim;
    m_frames = new std::vector<sf::IntRect>();
    m_animSpeed = animSpeed;
    m_pause = pause;
    m_loop = loop;
    
    InitAnim();
}

void Animation::InitAnim()
{
    int numFrames = m_endAnim - m_initAnim + 1;             //Numero de frames a ejecutar
    int numColumns = m_spriteSheet->GetColumns();          //Numero de columnas del spritesheet
    int numRows = m_spriteSheet->GetRows();                //Numero de filas del spritesheet
    int top = 0;                                        //Posicion superior del vertice superior izquierdo del rectangulo del frame actual
    int left = 0;                                       //Posicion izquierdo del vertice superior izquierdo del rectangulo del frame actual
    int width = m_spriteSheet->GetSizeTile().GetX();            //Anchura del frame actual
    int height = m_spriteSheet->GetSizeTile().GetY();           //Altura del frame actual
    int numFrame = 1;                                   //Numero de frame que estamos recorriendo
    
    for(int i = 0; i < numRows; i++)    //Por cada fila ...
    {
        //Cuando cambiamos de fila volvemos a empezar desde 0 -> fila1: 0, 32, 64 --> fila2: 0, 32, 64 ...
        left = 0;               
        //Vamos bajando de filas
        if(i > 0) top+=height;
        for(int j = 0; j < numColumns; j++)     //Por cada columna ...
        {
           if(numFrame >= m_initAnim && numFrame <= m_endAnim)      //Si leemos los frames que coinciden con el rango de animacion
           {
              m_frames->push_back(sf::IntRect(left, top, width, height));
           }
           left+=width;
           numFrame++;
        }
    }
 }

Animation::~Animation()
{
    m_frames->clear();
    delete m_frames;
    m_frames = NULL;
}

void Animation::SetInitAnim(int initAnim)
{
    m_initAnim = initAnim;
}

void Animation::SetEndAnim(int endAnim)
{
    m_endAnim = endAnim;
}

void Animation::SetAnimationName(std::string nombre)
{
    m_animationName = nombre;
}

SpriteSheet* Animation::GetSpriteSheet()
{
    return m_spriteSheet;
}

const sf::Texture* Animation::GetSpriteSheetTexture() const
{
    return m_spriteSheet->GetTexture();
}

 sf::IntRect Animation::GetFrame(std::size_t n) const
{
    try
    {
        if(m_frames->size() <= 0) throw "El vector de frames esta vacio";
        return m_frames->at(n);
    }
    catch (const char* msg)
    {
        std::cout << "Error: " << msg << std::endl;
    }
}

std::size_t Animation::GetNumFrames() const
{
    return m_frames->size();
}

std::string Animation::GetAnimationName() const
{
    return m_animationName;
}

float Animation::GetAnimSpeed() const
{
    return m_animSpeed;
}

bool Animation::GetPause() const
{
    return m_pause;
}

bool Animation::GetLoop() const
{
    return m_loop;
}