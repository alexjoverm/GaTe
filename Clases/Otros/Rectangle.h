/* 
 * File:   Rectangle.h
 * Author: linuxero
 *
 * Created on March 12, 2014, 7:37 AM
 */

#ifndef RECTANGLE_H
#define	RECTANGLE_H

#include <SFML/Graphics.hpp>

#include "Vector.h"

class Rectangle {
public:
	Rectangle(float x, float y, float width, float height, bool fromCenter = false);
	Rectangle(const sf::FloatRect& rect);
	Rectangle(const Rectangle& orig);
	virtual ~Rectangle();
	
	Vector GetTopLeft() const{ return Vector(rectangle->left, rectangle->top); }
	Vector GetTopRight() const{ return Vector(rectangle->left + rectangle->width, rectangle->top); }
	Vector GetBottomLeft() const{ return Vector(rectangle->left, rectangle->top + rectangle->height); }
	Vector GetBottomRight() const{ return Vector(rectangle->left  + rectangle->width, rectangle->top  + rectangle->height); }
	
	float GetWidth() const{ return rectangle->width; }
	float GetHeight() const{ return rectangle->height; }
	
	
	void SetX(float x){ rectangle->left = x; }
	void SetY(float y){ rectangle->top	= y; }
	void SetWidth(float w){ rectangle->width = w; }
	void SetHeight(float h){ rectangle->height	= h; }
	void Set(float x, float y, float w, float h){
		rectangle->left = x;	rectangle->top = y;
		rectangle->width= w;	rectangle->height = h;
	}
	
	
// Intersecciones
	bool Intersects(const Rectangle& rec){ return rectangle->intersects(*(rec.GetRectangle())); }
	bool IsInside(const Vector& vec){ return rectangle->contains(vec.GetX(), vec.GetY()); }
	
	sf::FloatRect* GetRectangle() const{ return rectangle; }
	
protected:
	sf::FloatRect*	rectangle;
};

#endif	/* RECTANGLE_H */

