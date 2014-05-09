/* 
 * File:   StatusManager.cpp
 * Author: linuxero
 * 
 * Created on April 14, 2014, 5:37 PM
 */

#include "StatusManager.h"
#include <string>
#include <map>



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
    
    for(std::map<Parameters::ID ,std::string>::iterator iterator = map.begin(); iterator != map.end(); iterator++)
        *streamOut << StringUtils::ConvertInt((int)iterator->first) << separator << iterator->second << "\n";
    
       
    CloseOut();
}

void StatusManager::LoadStatus()
{
    if(FileExists(fileStatus) && !loaded)
    {
        OpenIn(fileStatus);

        std::string line, value;
        std::size_t position = 0;
        Parameters::ID key;
        
        
      // Introducimos en un Map las configuraciones, que luego cargaremos
        while(getline(*streamIn,line))
        {
            position = line.find(separator);
            if (position != std::string::npos)
            {
                key   = (Parameters::ID)StringUtils::ParseInt(line.substr(0, position));
                value = line.substr(position+1);
                map.insert(std::make_pair(key,value));
            }
        }
        CloseIn();
        
        
        loaded = true;
    }
    
    // Si no existe el fichero, lo predefinimos
    else
        ResetParameters();
}


void StatusManager::ResetParameters()
{
    // Globales
    map.insert(std::make_pair(Parameters::credit, "50"));         // Credito disponible
    map.insert(std::make_pair(Parameters::countingLevels, "1"));     // Nivel por el que se va
    map.insert(std::make_pair(Parameters::countingWaves, "1"));      // Oleada por la que se va
    map.insert(std::make_pair(Parameters::maxLevelImproves, "20"));
    map.insert(std::make_pair(Parameters::maxLevelWaves, "20"));
    map.insert(std::make_pair(Parameters::unlockedGuns, "1"));
    map.insert(std::make_pair(Parameters::unlockedBullets, "1"));

    // GUN
    map.insert(std::make_pair(Parameters::gunDamageLevel, "1"));    
    map.insert(std::make_pair(Parameters::gunDamageInitValue, "10.0"));
    map.insert(std::make_pair(Parameters::gunDamageIncrement, "5.0"));
    
    map.insert(std::make_pair(Parameters::gunCadencyLevel, "1"));    
    map.insert(std::make_pair(Parameters::gunCadencyInitValue, "1.0"));
    map.insert(std::make_pair(Parameters::gunCadencyMinValue, "0.1"));
    
    // BULLET
    map.insert(std::make_pair(Parameters::bulletDamageLevel, "1"));    
    map.insert(std::make_pair(Parameters::bulletDamageInitValue, "10.0"));
    map.insert(std::make_pair(Parameters::bulletDamageIncrement, "5.0"));
    
    
    
    // PLAYER
    map.insert(std::make_pair(Parameters::playerLifeLevel, "1"));    
    map.insert(std::make_pair(Parameters::playerLifeInitValue, "150.0"));
    map.insert(std::make_pair(Parameters::playerLifeIncrement, "15.0"));
    map.insert(std::make_pair(Parameters::playerSpeedLevel, "1"));
    map.insert(std::make_pair(Parameters::playerSpeedInitValue, "370.0"));
    map.insert(std::make_pair(Parameters::playerSpeedIncrement, "4.0"));
    
    
    
    // TOWER ONE
    map.insert(std::make_pair(Parameters::towerOneDamageLevel, "1"));    
    map.insert(std::make_pair(Parameters::towerOneDamageInitValue, "8.0"));
    map.insert(std::make_pair(Parameters::towerOneDamageIncrement, "4.0"));
    
    map.insert(std::make_pair(Parameters::towerOneCadencyLevel, "1"));    
    map.insert(std::make_pair(Parameters::towerOneCadencyInitValue, "1.1"));
    map.insert(std::make_pair(Parameters::towerOneCadencyMinValue, "0.1"));
    
    map.insert(std::make_pair(Parameters::towerOneRangeLevel, "1"));    
    map.insert(std::make_pair(Parameters::towerOneRangeInitValue, "120.0"));
    map.insert(std::make_pair(Parameters::towerOneRangeIncrement, "15.0"));
    
     // TOWER TWO
    map.insert(std::make_pair(Parameters::towerOneDamageLevel, "1"));    
    map.insert(std::make_pair(Parameters::towerOneDamageInitValue, "15.0"));
    map.insert(std::make_pair(Parameters::towerOneDamageIncrement, "7.0"));
    
    map.insert(std::make_pair(Parameters::towerOneCadencyLevel, "1"));    
    map.insert(std::make_pair(Parameters::towerOneCadencyInitValue, "1.9"));
    map.insert(std::make_pair(Parameters::towerOneCadencyMinValue, "0.4"));
    
    map.insert(std::make_pair(Parameters::towerOneRangeLevel, "1"));    
    map.insert(std::make_pair(Parameters::towerOneRangeInitValue, "145.0"));
    map.insert(std::make_pair(Parameters::towerOneRangeIncrement, "20.0"));
    
    

    // ENEMIES
    map.insert(std::make_pair(Parameters::enemyLifeDenom, "10.0"));    
    map.insert(std::make_pair(Parameters::enemySpeedDenom, "50.0"));
    map.insert(std::make_pair(Parameters::enemyAttackDenom, "4.0"));
    
    // ENEMY ONE
    map.insert(std::make_pair(Parameters::enemyOneLifeLevel, "1"));    
    map.insert(std::make_pair(Parameters::enemyOneLifeInitValue, "100.0"));
    map.insert(std::make_pair(Parameters::enemyOneSpeedLevel, "1"));
    map.insert(std::make_pair(Parameters::enemyOneSpeedInitValue, "200.0"));
    map.insert(std::make_pair(Parameters::enemyOneAttackLevel, "1"));
    map.insert(std::make_pair(Parameters::enemyOneAttackInitValue, "10.0"));
    
    // ENEMY TWO
    map.insert(std::make_pair(Parameters::enemyTwoLifeLevel, "1"));    
    map.insert(std::make_pair(Parameters::enemyTwoLifeInitValue, "150.0"));
    map.insert(std::make_pair(Parameters::enemyTwoSpeedLevel, "1"));
    map.insert(std::make_pair(Parameters::enemyTwoSpeedInitValue, "160.0"));
    map.insert(std::make_pair(Parameters::enemyTwoAttackLevel, "1"));
    map.insert(std::make_pair(Parameters::enemyTwoAttackInitValue, "15.0"));
}



/*****************   SETTERS  ****************/

void StatusManager::IncrementInt(Parameters::ID key, int value){
    int aux = GetInt(key);
    SetValue(key, StringUtils::ConvertInt(aux + value));
}
void StatusManager::IncrementFloat(Parameters::ID key, float value){
    float aux = GetFloat(key);
    SetValue(key, StringUtils::ConvertFloat(aux + value));
}

void StatusManager::DecrementInt(Parameters::ID key, int value){
    int aux = GetInt(key);
    SetValue(key, StringUtils::ConvertInt(aux - value));
}
void StatusManager::DecrementFloat(Parameters::ID key, float value){
    float aux = GetFloat(key);
    SetValue(key, StringUtils::ConvertFloat(aux - value));
}



/*****************   CALCULADORES  ****************/

float StatusManager::GetGunDamage(){
    return GetFloat(Parameters::gunDamageInitValue) + (GetInt(Parameters::gunDamageLevel) * GetFloat(Parameters::gunDamageIncrement));
}
float StatusManager::GetGunCadency(){
    float cad = GetFloat(Parameters::gunCadencyInitValue) + (GetInt(Parameters::gunCadencyLevel) * GetFloat(Parameters::gunCadencyInitValue) / GetFloat(Parameters::maxLevelImproves));
    return (cad < GetFloat(Parameters::gunCadencyMinValue) ? GetFloat(Parameters::gunCadencyMinValue) : cad);
}


float StatusManager::GetBulletDamage(){
    return GetFloat(Parameters::bulletDamageInitValue) + GetInt(Parameters::bulletDamageLevel) * GetFloat(Parameters::bulletDamageIncrement);
}


float StatusManager::GetPlayerSpeed(){
    return GetFloat(Parameters::playerSpeedInitValue) + GetInt(Parameters::playerSpeedLevel) * GetFloat(Parameters::playerSpeedIncrement);
}
float StatusManager::GetPlayerLife(){
    return GetFloat(Parameters::playerLifeInitValue) + GetInt(Parameters::playerLifeLevel) * GetFloat(Parameters::playerLifeIncrement);
}


float StatusManager::GetTowerOneDamage(){
    return GetFloat(Parameters::towerOneDamageInitValue) + GetInt(Parameters::towerOneDamageLevel) * GetFloat(Parameters::towerOneDamageIncrement);
}
float StatusManager::GetTowerOneCadency(){
    float cad = GetFloat(Parameters::towerOneCadencyInitValue) + (GetInt(Parameters::towerOneCadencyLevel) * GetFloat(Parameters::towerOneCadencyInitValue) / GetFloat(Parameters::maxLevelImproves));
    return (cad < GetFloat(Parameters::towerOneCadencyMinValue) ? GetFloat(Parameters::towerOneCadencyMinValue) : cad);
}
float StatusManager::GetTowerOneRange(){
    return GetFloat(Parameters::towerOneRangeInitValue) + GetInt(Parameters::towerOneRangeLevel) * GetFloat(Parameters::towerOneRangeIncrement);
}


float StatusManager::GetTowerTwoDamage(){
    return GetFloat(Parameters::towerTwoDamageInitValue) + GetInt(Parameters::towerTwoDamageLevel) * GetFloat(Parameters::towerTwoDamageIncrement);
}
float StatusManager::GetTowerTwoCadency(){
    float cad = GetFloat(Parameters::towerTwoCadencyInitValue) + (GetInt(Parameters::towerTwoCadencyLevel) * GetFloat(Parameters::towerTwoCadencyInitValue) / GetFloat(Parameters::maxLevelImproves));
    return (cad < GetFloat(Parameters::towerTwoCadencyMinValue) ? GetFloat(Parameters::towerTwoCadencyMinValue) : cad);
}
float StatusManager::GetTowerTwoRange(){
    return GetFloat(Parameters::towerTwoRangeInitValue) + GetInt(Parameters::towerTwoRangeLevel) * GetFloat(Parameters::towerTwoRangeIncrement);
}


float StatusManager::GetEnemyOneLife(){
    return GetFloat(Parameters::enemyOneLifeInitValue) + (GetInt(Parameters::countingWaves) * GetFloat(Parameters::enemyOneLifeInitValue) / GetFloat(Parameters::enemyLifeDenom));
}
float StatusManager::GetEnemyOneSpeed(){
    return GetFloat(Parameters::enemyOneSpeedInitValue) + (GetInt(Parameters::countingWaves) * GetFloat(Parameters::enemyOneSpeedInitValue) / GetFloat(Parameters::enemySpeedDenom));
}
float StatusManager::GetEnemyOneAttack(){
    return GetFloat(Parameters::enemyOneAttackInitValue) + (GetInt(Parameters::countingWaves) * GetFloat(Parameters::enemyOneAttackInitValue) / GetFloat(Parameters::enemyAttackDenom));
}

float StatusManager::GetEnemyTwoLife(){
    return GetFloat(Parameters::enemyTwoLifeInitValue) + (GetInt(Parameters::countingWaves) * GetFloat(Parameters::enemyTwoLifeInitValue) / GetFloat(Parameters::enemyLifeDenom));
}
float StatusManager::GetEnemyTwoSpeed(){
    return GetFloat(Parameters::enemyTwoSpeedInitValue) + (GetInt(Parameters::countingWaves) * GetFloat(Parameters::enemyTwoSpeedInitValue) / GetFloat(Parameters::enemySpeedDenom));
}
float StatusManager::GetEnemyTwoAttack(){
    return GetFloat(Parameters::enemyTwoAttackInitValue) + (GetInt(Parameters::countingWaves) * GetFloat(Parameters::enemyTwoAttackInitValue) / GetFloat(Parameters::enemyAttackDenom));
}





/************************ FICHEROS ***********************/

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