/* 
 * File:   Time.cpp
 * Author: linuxero
 * 
 * Created on March 15, 2014, 5:53 AM
 */

#include "Time.h"
#include <iostream>

Time::Time() {
	time = new sf::Time();
}

Time::Time(float t) {
	time = new sf::Time();
	SetSeconds(t);
}

Time::Time(const Time& orig) {
}

Time::~Time() {
	delete time;
	time = NULL;
}


void Time::SetSeconds(float sec){
	*time = sf::seconds(sec);
}

void Time::SetMicroSeconds(int64_t sec)
{
    *time = sf::microseconds(sec);
}

Time& Time::operator=(const Time& t)
{	
    *time = sf::seconds(t.AsSeconds());
    return *this;
}

Time& Time::operator+=(const Time& t){ 
	*time += *(t.time); 
	return *this; 
}

Time& Time::operator-=(const Time& t){ 
	*time -= *(t.time); 
	return *this; 
}

bool Time::operator>(const Time& t){ 
	return (*time > *t.time);  
}