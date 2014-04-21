/* 
 * File:   Vector.cpp
 * Author: linuxero
 * 
 * Created on March 11, 2014, 9:46 AM
 */

#include "Vector.h"

///Este constructor...
Vector::Vector() {
	vector = new sf::Vector2f(0.f, 0.f);
}

Vector::Vector(float x, float y) {
	vector = new sf::Vector2f(x, y);
}

Vector::Vector(const Vector& orig) {
}

Vector::~Vector() {
	delete vector;
	vector = NULL;
}


Vector& Vector::operator=(const Vector& v)
{	
    vector->x = v.GetX();
	vector->y = v.GetY();
    return *this;
}

Vector& Vector::operator+=(const Vector& t){ 
	*vector += *(t.vector); 
	return *this; 
}



Vector& Vector::operator-=(const Vector& t){ 
	*vector -= *(t.vector); 
	return *this; 
}

Vector& Vector::operator*=(const float f){ 
	*vector *= f; 
	return *this; 
}

Vector& Vector::operator/=(const float f){ 
	*vector /= f; 
	return *this; 
}
