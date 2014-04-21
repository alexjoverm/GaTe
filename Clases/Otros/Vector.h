/* 
 * File:   Vector.h
 * Author: linuxero
 *
 * Created on March 11, 2014, 9:46 AM
 */

#ifndef VECTOR_H
#define	VECTOR_H

#include <SFML/Graphics.hpp>
#include <cmath>

class Vector {
	
public:
	Vector();
	Vector(float x, float y);
	Vector(const Vector& orig);
	virtual ~Vector();
	
	
	float GetX() const{ return vector->x; }
	float GetY() const{ return vector->y; }
	void SetX(float x){ vector->x = x; }
	void SetY(float y){ vector->y = y; }
	
	void Set(float x, float y){ vector->x = x; vector->y = y; } ///<Setea X e Y
	void Set(Vector& v){ vector->x = v.GetX(); vector->y = v.GetY(); }

// Operaciones Básicas
/**
 * Esta función Suma X e Y al vector
 * @param x posicion en el eje X
 * @param y posicion en el eje Y
 * @return No devuelve nada
 */
	Vector& operator=(const Vector& v);
	Vector& operator+=(const Vector& t);
	Vector& operator-=(const Vector& t);
	Vector& operator*=(const float f);
	Vector& operator/=(const float f);
	
/*	
	void Add(float x, float y);
	void Substract(float x, float y);
	void Multiply(float num);
	void Divide(float num);
 */
	
// Operaciones Complejas
	float GetModule(){///<Calcula el módulo del vector
		return hypot(vector->x, vector->y);
	}
	
	Vector GetNormalize(){///<Normaliza un vector
		Vector aux = Vector(vector->x, vector->y);
		aux /= (float)aux.GetModule();
		return aux;
	}

	
private:
	sf::Vector2f*	vector;

};

#endif	/* VECTOR_H */

