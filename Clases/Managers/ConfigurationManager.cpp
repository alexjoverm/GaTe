/* 
 * File:   ConfigurationManager.cpp
 * Author: linuxero
 * 
 * Created on April 14, 2014, 5:37 PM
 */

#include "ConfigurationManager.h"
#include "../States/WorldState.h"
#include "StateManager.h"
#include <string>
#include "../Otros/StringUtils.h"


std::string separator(":");
const std::string fileConfiguration = "user_conf.dat";


ConfigurationManager* ConfigurationManager::instance = 0;

//*********** METODO CREADOR DEL OBJETO ****/
ConfigurationManager* ConfigurationManager::Instance() {
	if(instance == 0)
		instance = new ConfigurationManager();
	
	return instance;
}


ConfigurationManager::ConfigurationManager()
{
    streamIn = new std::ifstream();
    streamOut = new std::ofstream();
}

ConfigurationManager::ConfigurationManager(const ConfigurationManager& orig) {
}

ConfigurationManager::~ConfigurationManager() {
}

void ConfigurationManager::SaveConfigurations()
{
    OpenOut(fileConfiguration);
    
    *streamOut << "music" << separator << (int)(MusicPlayer::Instance()->GetVolume()) << "\n";
    *streamOut << "sound" << separator << (int)(SoundPlayer::Instance()->active) << "\n";
    
    CloseOut();
}

void ConfigurationManager::LoadConfigurations()
{
    if(FileExists(fileConfiguration))
    {
        OpenIn(fileConfiguration);

        std::string line, key, value;
        std::size_t position = 0;
        
        std::map<std::string, std::string> mapConf;
        
      // Introducimos en un Map las configuraciones, que luego cargaremos
        while(getline(*streamIn,line))
        {
            position = line.find(separator);
            if (position != std::string::npos)
            {
                key   = line.substr(0, position);
                value = line.substr(position+1);
                mapConf.insert(std::make_pair(key,value));
            }
        }
        CloseIn();
        
      // Cargamos configuraciones del map
        MusicPlayer::Instance()->SetVolume( StringUtils::ParseFloat(mapConf.find("music")->second) );
        SoundPlayer::Instance()->active = StringUtils::ParseInt(mapConf.find("sound")->second);
        
        loaded = true;
    }
}



bool ConfigurationManager::FileExists(const std::string filename)
{
    std::ifstream ifile(filename);
    return (bool)ifile;
}

void ConfigurationManager::OpenIn(const std::string filename)
{
    streamIn->open(filename);
    
    if(!*streamIn)
        throw std::string("El fichero " + filename + " no existe");
}

void ConfigurationManager::OpenOut(const std::string filename)
{
    streamOut->open(filename);
    
    if(!*streamOut)
        throw std::string("Fallo con el fichero " + filename);
}


void ConfigurationManager::CloseIn()
{
    streamIn->close();
}

void ConfigurationManager::CloseOut()
{
    streamOut->close();
}