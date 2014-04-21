/* 
 * File:   StringUtils.cpp
 * Author: linuxero
 * 
 * Created on March 18, 2014, 9:24 AM
 */
#include "StringUtils.h"
#include "Vector.h"

StringUtils* StringUtils::instance = 0;  // SINGLETON

StringUtils* StringUtils::Instance() {
	if(instance == 0)
		instance = new StringUtils();
	
	return instance;
}


StringUtils::StringUtils() {
}
StringUtils::StringUtils(const StringUtils& orig) {
}
StringUtils::~StringUtils() {
}


//***********************************  CONVERTS  *********************************************

  std::string StringUtils::ConvertBool(const bool theBoolean)
  {
    std::stringstream anResult;
    if(theBoolean)
      anResult << "true";
    else
      anResult << "false";
    return anResult.str();
  }
  
  
  
// NUMEROS
  std::string StringUtils::ConvertDouble(const double theDouble)
  {
    std::stringstream anResult;
    anResult << theDouble;
    return anResult.str();
  }
  
  std::string StringUtils::ConvertFloat(const float theFloat)
  {
    std::stringstream anResult;
    anResult << theFloat;
    return anResult.str();
  }
  
  
  std::string StringUtils::ConvertSInt(const short int theNumber)
  {
    std::stringstream anResult;
    anResult << theNumber;
    return anResult.str();
  }
  
  std::string StringUtils::ConvertInt(const int theNumber)
  {
    std::stringstream anResult;
    anResult << theNumber;
    return anResult.str();
  }

  std::string StringUtils::ConvertLInt(const long int theNumber)
  {
    std::stringstream anResult;
    anResult << theNumber;
    return anResult.str();
  }
  
  
  std::string StringUtils::ConvertUSInt(const unsigned short int theNumber)
  {
    std::stringstream anResult;
    anResult << theNumber;
    return anResult.str();
  }
  
  std::string StringUtils::ConvertUInt(const unsigned int theNumber)
  {
    std::stringstream anResult;
    anResult << theNumber;
    return anResult.str();
  }

  std::string StringUtils::ConvertULInt(const unsigned long int theNumber)
  {
    std::stringstream anResult;
    anResult << theNumber;
    return anResult.str();
  }
  
  
  
// SFML & MOTOR2D
  std::string StringUtils::ConvertColor(const sf::Color theColor)
  {
    std::stringstream anResult;
    anResult << theColor.r << ", ";
    anResult << theColor.g << ", ";
    anResult << theColor.b << ", ";
    anResult << theColor.a;
    return anResult.str();
  }
  
  
  std::string StringUtils::ConvertVector(const Vector& theVector)
  {
    std::stringstream anResult;
    anResult << theVector.GetX() << ", ";
    anResult << theVector.GetY();
    return anResult.str();
  }
  

  
  
  
  

//***********************************  PARSES  **********************************************  
  
 // BOOLEANOS
  bool StringUtils::ParseBool(std::string theValue)
  {
    bool anResult = false;
    std::transform(theValue.begin(), theValue.end(), theValue.begin(), tolower);
	
    if(theValue == "true" || theValue == "1" || theValue == "on")
      anResult = true;
    
    return anResult;
  }
  
  
// NUMEROS
  double StringUtils::ParseDouble(const std::string theValue)
  {
    double anResult = 0.0;
    std::istringstream iss(theValue);
    iss >> anResult;
    return anResult;
  }
  
  float StringUtils::ParseFloat(const std::string theValue)
  {
    float anResult = 0.f;
    std::istringstream iss(theValue);
    iss >> anResult;
    return anResult;
  }
  
  // int
  short int StringUtils::ParseSInt(const std::string theValue)
  {
    short int anResult = 0;
    std::istringstream iss(theValue);
    iss >> anResult;
    return anResult;
  }
  int StringUtils::ParseInt(const std::string theValue)
  {
    int anResult = 0;
    std::istringstream iss(theValue);
    iss >> anResult;
    return anResult;
  }
  long int StringUtils::ParseLInt(const std::string theValue)
  {
    long int anResult = 0;
    std::istringstream iss(theValue);
    iss >> anResult;
    return anResult;
  }

  
  unsigned short int StringUtils::ParseUSInt(const std::string theValue)
  {
    unsigned short int anResult = 0;
    std::istringstream iss(theValue);
    iss >> anResult;
    return anResult;
  }
  unsigned int StringUtils::ParseUInt(const std::string theValue)
  {
    unsigned int anResult = 0;
    std::istringstream iss(theValue);
    iss >> anResult;
    return anResult;
  }
  unsigned long int StringUtils::ParseULInt(const std::string theValue)
  {
    unsigned long int anResult = 0;
    std::istringstream iss(theValue);
    iss >> anResult;
    return anResult;
  }
  
  
  
 // SFML & MOTOR2D
   // Color
  sf::Color StringUtils::ParseColor(const std::string theValue)
  {
    sf::Color anResult = sf::Color(sf::Color::Black);
    size_t anComma1Offset = theValue.find_first_of(',');
    if(anComma1Offset != std::string::npos)
    {
      sf::Uint8 anRed = ParseUSInt(theValue.substr(0,anComma1Offset));
      size_t anComma2Offset = theValue.find_first_of(',',anComma1Offset+1);
	  
      if(anComma2Offset != std::string::npos)
      {
        sf::Uint8 anGreen = ParseUSInt(theValue.substr(anComma1Offset+1,anComma2Offset));
        size_t anComma3Offset = theValue.find_first_of(',',anComma2Offset+1);
		
        if(anComma3Offset != std::string::npos)
        {
          sf::Uint8 anBlue = ParseUSInt(theValue.substr(anComma2Offset+1,anComma3Offset));
          sf::Uint8 anAlpha = ParseUSInt(theValue.substr(anComma3Offset+1));
          anResult.r = anRed;
          anResult.g = anGreen;
          anResult.b = anBlue;
          anResult.a = anAlpha;
        }
      }
    }
    return anResult;
  }
  
  
  Vector StringUtils::ParseVector(const std::string theValue)
  {
    Vector anResult = Vector(0.f, 0.f);
    size_t anCommaOffset = theValue.find_first_of(',');
    if(anCommaOffset != std::string::npos)
    {
      float anX = ParseFloat(theValue.substr(0,anCommaOffset));
      float anY = ParseFloat(theValue.substr(anCommaOffset+1));
      anResult.SetX(anX);
      anResult.SetY(anY);
    }
    return anResult;
  }