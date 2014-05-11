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
    map.clear();
   
 //******************* HABILIDADES
    map.insert(std::make_pair(Parameters::habilityAngularShot, "0"));
    map.insert(std::make_pair(Parameters::habilityDobleJump, "0"));
    
 //******************* ECONOMIA
    map.insert(std::make_pair(Parameters::priceImproveInit, "20"));       // Mejoras
    map.insert(std::make_pair(Parameters::priceImproveIncrement, "10"));
    
    map.insert(std::make_pair(Parameters::priceBuyTowerTwo, "100"));      // Torretas (comprar)
    map.insert(std::make_pair(Parameters::priceBuyTowerThree, "200"));
    
    map.insert(std::make_pair(Parameters::pricePutTowerOne, "50"));       // Torretas (poner)
    map.insert(std::make_pair(Parameters::pricePutTowerTwo, "75"));
    map.insert(std::make_pair(Parameters::pricePutTowerThree, "100"));
    
    map.insert(std::make_pair(Parameters::priceBuyBulletTwo, "50"));      // Bullets
    map.insert(std::make_pair(Parameters::priceBuyBulletThree, "50"));
    
    map.insert(std::make_pair(Parameters::priceLeaveEnemyDenom, "20"));     // Enemies
    map.insert(std::make_pair(Parameters::priceLeaveEnemyOne, "10"));
    map.insert(std::make_pair(Parameters::priceLeaveEnemyTwo, "15"));
    map.insert(std::make_pair(Parameters::priceLeaveEnemyThree, "20"));
    
    
 //******************* VARIABLES
    
    // GLOBALES
    map.insert(std::make_pair(Parameters::credit, "50"));         // Credito disponible
    map.insert(std::make_pair(Parameters::countingLevels, "1"));     // Nivel por el que se va
    map.insert(std::make_pair(Parameters::countingWaves, "1"));      // Oleada por la que se va
    map.insert(std::make_pair(Parameters::maxLevelImproves, "20"));
    map.insert(std::make_pair(Parameters::maxLevelWaves, "20"));
    map.insert(std::make_pair(Parameters::unlockedGuns, "1"));
    map.insert(std::make_pair(Parameters::unlockedBullets, "1"));
    map.insert(std::make_pair(Parameters::unlockedTowers, "1"));
    
    
    // WORLD
    map.insert(std::make_pair(Parameters::worldLifeLevel, "1"));    
    map.insert(std::make_pair(Parameters::worldLifeInitValue, "150.0"));
    map.insert(std::make_pair(Parameters::worldLifeIncrement, "15.0"));

    
    // GUN
    map.insert(std::make_pair(Parameters::gunDamageLevel, "1"));    
    map.insert(std::make_pair(Parameters::gunDamageInitValue, "18.0"));
    map.insert(std::make_pair(Parameters::gunDamageIncrement, "5.0"));
    
    map.insert(std::make_pair(Parameters::gunCadencyLevel, "1"));    
    map.insert(std::make_pair(Parameters::gunCadencyInitValue, "1.0"));
    map.insert(std::make_pair(Parameters::gunCadencyMinValue, "0.1"));
    
    // BULLET
    map.insert(std::make_pair(Parameters::bulletDamageLevel, "1"));    
    map.insert(std::make_pair(Parameters::bulletDamageInitValue, "12.0"));
    map.insert(std::make_pair(Parameters::bulletDamageIncrement, "5.0"));
    
    
    // PLAYER
    map.insert(std::make_pair(Parameters::playerLifeLevel, "1"));    
    map.insert(std::make_pair(Parameters::playerLifeInitValue, "150.0"));
    map.insert(std::make_pair(Parameters::playerLifeIncrement, "15.0"));
    map.insert(std::make_pair(Parameters::playerSpeedLevel, "1"));
    map.insert(std::make_pair(Parameters::playerSpeedInitValue, "370.0"));
    map.insert(std::make_pair(Parameters::playerSpeedIncrement, "4.0"));
    
    
    
    // TOWER ONE (DISPARO RÁPIDO)
    map.insert(std::make_pair(Parameters::towerOneDamageLevel, "1"));    
    map.insert(std::make_pair(Parameters::towerOneDamageInitValue, "8.0"));
    map.insert(std::make_pair(Parameters::towerOneDamageIncrement, "4.0"));
    
    map.insert(std::make_pair(Parameters::towerOneCadencyLevel, "1"));    
    map.insert(std::make_pair(Parameters::towerOneCadencyInitValue, "0.9"));
    map.insert(std::make_pair(Parameters::towerOneCadencyMinValue, "0.1"));
    
    map.insert(std::make_pair(Parameters::towerOneRangeLevel, "1"));    
    map.insert(std::make_pair(Parameters::towerOneRangeInitValue, "100.0"));
    map.insert(std::make_pair(Parameters::towerOneRangeIncrement, "5.0"));
    
     // TOWER TWO (EQUILIBRADO)
    map.insert(std::make_pair(Parameters::towerTwoDamageLevel, "1"));    
    map.insert(std::make_pair(Parameters::towerTwoDamageInitValue, "12.0"));
    map.insert(std::make_pair(Parameters::towerTwoDamageIncrement, "6.0"));
    
    map.insert(std::make_pair(Parameters::towerTwoCadencyLevel, "1"));    
    map.insert(std::make_pair(Parameters::towerTwoCadencyInitValue, "1.3"));
    map.insert(std::make_pair(Parameters::towerTwoCadencyMinValue, "0.3"));
    
    map.insert(std::make_pair(Parameters::towerTwoRangeLevel, "1"));    
    map.insert(std::make_pair(Parameters::towerTwoRangeInitValue, "150.0"));
    map.insert(std::make_pair(Parameters::towerTwoRangeIncrement, "10.0"));
    
     // TOWER THREE (CAÑONAZOS)
    map.insert(std::make_pair(Parameters::towerThreeDamageLevel, "1"));    
    map.insert(std::make_pair(Parameters::towerThreeDamageInitValue, "18.0"));
    map.insert(std::make_pair(Parameters::towerThreeDamageIncrement, "9.0"));
    
    map.insert(std::make_pair(Parameters::towerThreeCadencyLevel, "1"));    
    map.insert(std::make_pair(Parameters::towerThreeCadencyInitValue, "2.0"));
    map.insert(std::make_pair(Parameters::towerThreeCadencyMinValue, "0.6"));
    
    map.insert(std::make_pair(Parameters::towerThreeRangeLevel, "1"));    
    map.insert(std::make_pair(Parameters::towerThreeRangeInitValue, "200.0"));
    map.insert(std::make_pair(Parameters::towerThreeRangeIncrement, "13.0"));
    

    // ENEMIES
    map.insert(std::make_pair(Parameters::enemyLifeDenom, "8.0"));    
    map.insert(std::make_pair(Parameters::enemySpeedDenom, "50.0"));
    map.insert(std::make_pair(Parameters::enemyAttackDenom, "4.0"));
    
    // ENEMY ONE
    map.insert(std::make_pair(Parameters::enemyOneLifeLevel, "1"));    
    map.insert(std::make_pair(Parameters::enemyOneLifeInitValue, "100.0"));
    map.insert(std::make_pair(Parameters::enemyOneSpeedLevel, "1"));
    map.insert(std::make_pair(Parameters::enemyOneSpeedInitValue, "190.0"));
    map.insert(std::make_pair(Parameters::enemyOneAttackLevel, "1"));
    map.insert(std::make_pair(Parameters::enemyOneAttackInitValue, "7.0"));
    
    // ENEMY TWO
    map.insert(std::make_pair(Parameters::enemyTwoLifeLevel, "1"));    
    map.insert(std::make_pair(Parameters::enemyTwoLifeInitValue, "150.0"));
    map.insert(std::make_pair(Parameters::enemyTwoSpeedLevel, "1"));
    map.insert(std::make_pair(Parameters::enemyTwoSpeedInitValue, "140.0"));
    map.insert(std::make_pair(Parameters::enemyTwoAttackLevel, "1"));
    map.insert(std::make_pair(Parameters::enemyTwoAttackInitValue, "11.0"));
    
    // ENEMY THREE
    map.insert(std::make_pair(Parameters::enemyThreeLifeLevel, "1"));    
    map.insert(std::make_pair(Parameters::enemyThreeLifeInitValue, "200.0"));
    map.insert(std::make_pair(Parameters::enemyThreeSpeedLevel, "1"));
    map.insert(std::make_pair(Parameters::enemyThreeSpeedInitValue, "90.0"));
    map.insert(std::make_pair(Parameters::enemyThreeAttackLevel, "1"));
    map.insert(std::make_pair(Parameters::enemyThreeAttackInitValue, "18.0"));
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

float StatusManager::GetWorldLife(){
    return GetFloat(Parameters::worldLifeInitValue) + GetInt(Parameters::worldLifeLevel) * GetFloat(Parameters::worldLifeIncrement);
}


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

float StatusManager::GetTowerThreeDamage(){
    return GetFloat(Parameters::towerThreeDamageInitValue) + GetInt(Parameters::towerThreeDamageLevel) * GetFloat(Parameters::towerThreeDamageIncrement);
}
float StatusManager::GetTowerThreeCadency(){
    float cad = GetFloat(Parameters::towerThreeCadencyInitValue) + (GetInt(Parameters::towerThreeCadencyLevel) * GetFloat(Parameters::towerThreeCadencyInitValue) / GetFloat(Parameters::maxLevelImproves));
    return (cad < GetFloat(Parameters::towerThreeCadencyMinValue) ? GetFloat(Parameters::towerThreeCadencyMinValue) : cad);
}
float StatusManager::GetTowerThreeRange(){
    return GetFloat(Parameters::towerThreeRangeInitValue) + GetInt(Parameters::towerThreeRangeLevel) * GetFloat(Parameters::towerThreeRangeIncrement);
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
float StatusManager::GetEnemyOnePrice(){
    return GetFloat(Parameters::priceLeaveEnemyOne) + (GetInt(Parameters::countingWaves) * GetFloat(Parameters::priceLeaveEnemyOne) / GetFloat(Parameters::priceLeaveEnemyDenom));
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
float StatusManager::GetEnemyTwoPrice(){
    return GetFloat(Parameters::priceLeaveEnemyTwo) + (GetInt(Parameters::countingWaves) * GetFloat(Parameters::priceLeaveEnemyTwo) / GetFloat(Parameters::priceLeaveEnemyDenom));
}

float StatusManager::GetEnemyThreeLife(){
    return GetFloat(Parameters::enemyThreeLifeInitValue) + (GetInt(Parameters::countingWaves) * GetFloat(Parameters::enemyThreeLifeInitValue) / GetFloat(Parameters::enemyLifeDenom));
}
float StatusManager::GetEnemyThreeSpeed(){
    return GetFloat(Parameters::enemyThreeSpeedInitValue) + (GetInt(Parameters::countingWaves) * GetFloat(Parameters::enemyThreeSpeedInitValue) / GetFloat(Parameters::enemySpeedDenom));
}
float StatusManager::GetEnemyThreeAttack(){
    return GetFloat(Parameters::enemyThreeAttackInitValue) + (GetInt(Parameters::countingWaves) * GetFloat(Parameters::enemyThreeAttackInitValue) / GetFloat(Parameters::enemyAttackDenom));
}
float StatusManager::GetEnemyThreePrice(){
    return GetFloat(Parameters::priceLeaveEnemyThree) + (GetInt(Parameters::countingWaves) * GetFloat(Parameters::priceLeaveEnemyThree) / GetFloat(Parameters::priceLeaveEnemyDenom));
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