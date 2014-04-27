/* 
 * File:   ConfigurationManager.h
 * Author: linuxero
 *
 * Created on April 14, 2014, 5:37 PM
 */

#ifndef CONFIGURATIONMANAGER_H
#define	CONFIGURATIONMANAGER_H
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "../MusicSounds/MusicPlayer.h"
#include "../MusicSounds/SoundPlayer.h"

class ConfigurationManager {
public:
	static ConfigurationManager* Instance(); // Método que habrá que llamar para crear el objeto
	
protected:
	ConfigurationManager();
	ConfigurationManager(const ConfigurationManager& orig);
	virtual ~ConfigurationManager();
	
public:
    void SaveConfigurations();
    void LoadConfigurations();
    
    bool loaded = false;
    
private:
	static ConfigurationManager* instance;
    
    std::ifstream* streamIn;
    std::ofstream* streamOut;
    
    //Funciones
    bool FileExists(const std::string filename);
    
    void OpenIn(const std::string filename);
    void OpenOut(const std::string filename);
    
    void CloseIn();
    void CloseOut();
    
    
};

#endif	/* ConfigurationMANAGER_H */

