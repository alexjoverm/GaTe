/* 
 * File:   Maths.cpp
 * Author: linuxero
 * 
 * Created on March 12, 2014, 8:28 AM
 */

#include "Maths.h"

//**************** SINGLETON
Maths* Maths::instance = 0;

Maths* Maths::Instance() {
	if(instance == 0)
		instance = new Maths();
	
	return instance;
}


Maths::Maths() {
}

Maths::Maths(const Maths& orig) {
}

Maths::~Maths() {
}

