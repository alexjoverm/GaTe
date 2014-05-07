/* 
 * File:   StatusManager.h
 * Author: linuxero
 *
 * Created on April 14, 2014, 5:37 PM
 */

#ifndef STATUSMANAGER_H
#define	STATUSMANAGER_H
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "../Otros/StringUtils.h"

class StatusManager {
public:
	static StatusManager* Instance(); // Método que habrá que llamar para crear el objeto
	
protected:
	StatusManager();
	StatusManager(const StatusManager& orig);
	virtual ~StatusManager();
	
public:
    void SaveStatus();
    void LoadStatus();
    
    std::string  GetValue(std::string key){ return mapConf.find(key)->second; }
    void         SetValue(std::string key, std::string value){ mapConf.find(key)->second = value; }
    float        GetFloat(std::string key){ return StringUtils::ParseFloat(mapConf.find(key)->second); }
    
    
    bool loaded = false;
    
private:
	static StatusManager* instance;
    
    std::ifstream* streamIn;
    std::ofstream* streamOut;
    
    std::map<std::string, std::string> mapConf;
    
    //Funciones
    bool FileExists(const std::string filename);
    
    void OpenIn(const std::string filename);
    void OpenOut(const std::string filename);
    
    void CloseIn();
    void CloseOut();
    
    
};

#endif	/* StatusMANAGER_H */

