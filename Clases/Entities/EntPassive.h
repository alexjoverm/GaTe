/* 
 * File:   EntPassive.h
 * Author: linuxero
 *
 * Created on March 11, 2014, 9:44 AM
 */

#ifndef ENTPASSIVE_H
#define	ENTPASSIVE_H

#include "Entity.h"
#include "../Otros/Vector.h"


class EntPassive: public Entity {
public:
	EntPassive(const sf::Texture& tex);
	EntPassive(const EntPassive& orig);
	virtual ~EntPassive();
	
	virtual void Draw(RenderWindow& window); ///< Realiza un Draw simple
	virtual void Update(const Time& elapsedTime); ///< De momento no hará nada el update
	
	void SetPosition(const Vector& v){ spriteSheet->SetPosition(v); }
	virtual Vector& GetPosition() const{ return spriteSheet->GetPosition(); }
	void Move(Vector v){ spriteSheet->Move(v); }

};

#endif	/* ENTPASSIVE_H */

