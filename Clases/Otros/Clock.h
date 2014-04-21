/* 
 * File:   Clock.h
 * Author: linuxero
 *
 * Created on March 15, 2014, 5:53 AM
 */

#ifndef CLOCK_H
#define	CLOCK_H

#include <SFML/Graphics.hpp>
#include "Time.h"
#include <iostream>

class Clock {
public:
	Clock();
	Clock(const Clock& orig);
	virtual ~Clock();
	
	Time Restart(){ 
		return Time(clock->restart().asSeconds());
	} 
	/*
	float Restart(){
		return clock->restart().asSeconds();
	}*/
	Time GetElapsedTime() const{ return Time(clock->getElapsedTime().asSeconds()); }
	
	sf::Clock*	clock;
	
};

#endif	/* CLOCK_H */

