/* 
 * File:   AnimatedObject.h
 * Author: jmsm30
 *
 * Created on 28 de abril de 2014, 3:37
 */

#ifndef ANIMATEDOBJECT_H
#define	ANIMATEDOBJECT_H

#include "../Animations/Animable.h"
#include "EntPassive.h"

class AnimatedObject: public EntPassive, public Animable{
public:
    
    AnimatedObject(const sf::Texture& tex, const Vector& size);
    AnimatedObject(const AnimatedObject& orig);
    virtual ~AnimatedObject();	
    
    virtual const std::string GetClassName() { return "AnimatedObject"; }

    // Bucle de ciclo de vida
    virtual void Draw(RenderWindow& window);
    void Update(const Time& elapsedTime);
	
private:

};

#endif	/* ANIMATEDOBJECT_H */

