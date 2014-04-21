/* 
 * File:   Time.h
 * Author: linuxero
 *
 * Created on March 15, 2014, 5:53 AM
 */

#ifndef TIME_H
#define	TIME_H

#include <inttypes.h>
#include <SFML/Graphics.hpp>

class Time {
public:
	Time();
	Time(float t);
	Time(const Time& orig);
	virtual ~Time();
	
	float AsSeconds() const{ return time->asSeconds(); }
	int32_t AsMilliSeconds() const{ return time->asMilliseconds();}
	int64_t AsMicroSeconds() const{ return time->asMicroseconds(); }
	
	void SetSeconds(float sec);
    void SetMicroSeconds(int64_t sec);
	
  // Operadores	
	Time& operator=(const Time& t);
	Time& operator+=(const Time& t);
	Time& operator-=(const Time& t);
	bool operator>(const Time& t);
	
	
	
	sf::Time*	time;
	
};

#endif	/* TIME_H */

