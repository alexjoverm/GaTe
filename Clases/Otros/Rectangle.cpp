/* 
 * File:   Rectangle.cpp
 * Author: linuxero
 * 
 * Created on March 12, 2014, 7:37 AM
 */

#include "Rectangle.h"

Rectangle::Rectangle(float x, float y, float width, float height, bool fromCenter) {
	if(fromCenter){
		x -= width/2.f;
		y -= height/2.f;
	}
	rectangle = new sf::FloatRect(x, y, width, height);
}

Rectangle::Rectangle(const sf::FloatRect& rect) {
	rectangle = new sf::FloatRect(rect.left, rect.top, rect.width, rect.height);
}

Rectangle::Rectangle(const Rectangle& orig) {
}

Rectangle::~Rectangle() {
	delete rectangle;
	rectangle = NULL;
}
