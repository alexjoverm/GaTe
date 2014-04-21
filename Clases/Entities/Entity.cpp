/* 
 * File:   Entity.cpp
 * Author: linuxero
 * 
 * Created on March 11, 2014, 9:42 AM
 */

#include "Entity.h"

Entity::Entity(const sf::Texture& tex) {
	spriteSheet = new SpriteSheet(tex);
}

Entity::Entity(const Entity& orig) {
}

Entity::~Entity() {
	delete spriteSheet;
	spriteSheet = NULL;
}

