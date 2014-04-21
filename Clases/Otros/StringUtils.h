/* 
 * File:   StringUtils.h
 * Author: linuxero
 *
 * Created on March 18, 2014, 9:24 AM
 */

#ifndef STRINGUTILS_H
#define	STRINGUTILS_H

#include <SFML/Graphics.hpp>
#include "Vector.h"
#include <sstream>
#include <algorithm>

class StringUtils {
public:
	static StringUtils* Instance(); // Singleton
	
	static std::string ConvertBool(const bool theBoolean);
	static std::string ConvertDouble(const double theDouble);
	static std::string ConvertFloat(const float theFloat);
	static std::string ConvertSInt(const short int theNumber);
	static std::string ConvertInt(const int theNumber);
	static std::string ConvertLInt(const long int theNumber);
	static std::string ConvertUSInt(const unsigned short int theNumber);
	static std::string ConvertUInt(const unsigned int theNumber);
	static std::string ConvertULInt(const unsigned long int theNumber);
	static std::string ConvertColor(const sf::Color theColor);
    static std::string ConvertVector(const Vector& theVector);
	
	
	
	
	static bool ParseBool(std::string theValue);
	static double ParseDouble(const std::string theValue);
	static float ParseFloat(const std::string theValue);
	static short int ParseSInt(const std::string theValue);
	static int ParseInt(const std::string theValue);
	static long int ParseLInt(const std::string theValue);
	static unsigned short int ParseUSInt(const std::string theValue);
	static unsigned int ParseUInt(const std::string theValue);
	static unsigned long int ParseULInt(const std::string theValue);
	static sf::Color ParseColor(const std::string theValue);
	static Vector ParseVector(const std::string theValue);
	
	
private:
	StringUtils();
	StringUtils(const StringUtils& orig);
	virtual ~StringUtils();
	
	static StringUtils* instance;
	
	

};

#endif	/* STRINGUTILS_H */

