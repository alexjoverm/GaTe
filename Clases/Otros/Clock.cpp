/* 
 * File:   Clock.cpp
 * Author: linuxero
 * 
 * Created on March 15, 2014, 5:53 AM
 */

#include "Clock.h"

Clock::Clock() {
	clock = new sf::Clock();
}

Clock::Clock(const Clock& orig) {
}

Clock::~Clock() {
	delete clock;
	clock = NULL;
}

