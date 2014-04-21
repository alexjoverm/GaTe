/* 
 * File:   Entity.h
 * Author: linuxero
 *
 * Created on March 11, 2014, 9:42 AM
 */

#ifndef ENTITY_H
#define	ENTITY_H

#include "../Animations/SpriteSheet.h"
#include "../Motor2D/RenderWindow.h"
#include "../Otros/Time.h"
#include <SFML/Graphics.hpp>

class Entity {
public:
	Entity(const sf::Texture& tex);
	Entity(const Entity& orig);
	virtual ~Entity();
	
	virtual const std::string GetClassName() { return "Entity";}
	
	//virtual void Draw(RenderWindow& window) = 0; ESTE METODO NO SE HEREDARÁ, SE IMPLEMENTARÁ EN LAS SUBCLASES
	virtual void Update(const Time& elapsedTime) = 0;
	
	SpriteSheet* GetSprite() const{ return spriteSheet; } // Devolvemos el puntero ya que se usará para el Render
	void SetWidthTile(int widthTile) { spriteSheet->SetWidthTile(widthTile); }
	void SetHeightTile(int heightTile) { spriteSheet->SetHeightTile(heightTile); }
	
	virtual void SetPosition(const Vector& v) = 0;
	virtual Vector& GetPosition() const= 0;
	
protected:
	SpriteSheet* spriteSheet;

};

#endif	/* ENTITY_H */

