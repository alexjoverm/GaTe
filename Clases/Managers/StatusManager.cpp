/* 
 * File:   StatusManager.cpp
 * Author: linuxero
 * 
 * Created on April 14, 2014, 5:37 PM
 */

#include "StatusManager.h"
#include <string>



std::string separator("|");
const std::string fileStatus = "status_conf.dat";


StatusManager* StatusManager::instance = 0;

//*********** METODO CREADOR DEL OBJETO ****/
StatusManager* StatusManager::Instance() {
	if(instance == 0)
		instance = new StatusManager();
	
	return instance;
}


StatusManager::StatusManager()
{
    streamIn = new std::ifstream();
    streamOut = new std::ofstream();
}

StatusManager::StatusManager(const StatusManager& orig) {
}

StatusManager::~StatusManager() {
}

void StatusManager::SaveStatus()
{
    OpenOut(fileStatus);
    
    for(std::map<std::string,std::string>::iterator iterator = mapConf.begin(); iterator != mapConf.end(); iterator++)
        *streamOut << iterator->first << separator << iterator->second << "\n";
    
       
    CloseOut();
}

void StatusManager::LoadStatus()
{
    if(FileExists(fileStatus) && !loaded)
    {
        OpenIn(fileStatus);

        std::string line, key, value;
        std::size_t position = 0;
        
        
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
        
        
        loaded = true;
    }
    
    // Si no existe el fichero, lo predefinimos
    else
    {
        mapConf.insert(std::make_pair("credit", "50"));     // Credito disponible
        mapConf.insert(std::make_pair("levelGun", "1"));    // Nivel de la pistola
        mapConf.insert(std::make_pair("level", "1"));       // Nivel por el que se va
    }
}



bool StatusManager::FileExists(const std::string filename)
{
    std::ifstream ifile(filename);
    return (bool)ifile;
}

void StatusManager::OpenIn(const std::string filename)
{
    streamIn->open(filename);
    
    if(!*streamIn)
        throw std::string("El fichero " + filename + " no existe");
}

void StatusManager::OpenOut(const std::string filename)
{
    streamOut->open(filename);
    
    if(!*streamOut)
        throw std::string("Fallo con el fichero " + filename);
}


void StatusManager::CloseIn()
{
    streamIn->close();
}

void StatusManager::CloseOut()
{
    streamOut->close();
}