/* 
 * File:   Maths.h
 * Author: linuxero
 *
 * Created on March 12, 2014, 8:28 AM
 */

#ifndef MATHS_H
#define	MATHS_H
#include <cmath>

#include "../Otros/Vector.h"

class Maths {
public:
	static Maths* Instance(); // Singleton

/** Redondea un float a "p" decimales
 * @param f float a redondear
 * @param  precisión (cuantos decimales
 * @return Devuelve float redondeado
 */
	static float Round(float f, int p){///<Redondea f a "p" decimales
		return (float)floor(f*pow(10,p) + 0.5) / pow(10,p);
	}
	
private:
  // SINGLETON
	Maths();
	Maths(const Maths& orig);
	virtual ~Maths();
	
	static Maths* instance;

};

#endif	/* MATHS_H */

