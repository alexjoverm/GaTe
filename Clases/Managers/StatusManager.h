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



namespace Parameters{
    enum ID{
        credit, maxLevelImproves, maxLevelWaves,                // GLOBAL
        unlockedGuns, unlockedBullets,
        countingLevels, countingWaves,
        worldLifeLevel, worldLifeInitValue, worldLifeIncrement,
        //currentGun, currentBullet,
        
        gunDamageLevel, gunDamageInitValue, gunDamageIncrement,             // GUN
        gunCadencyLevel, gunCadencyInitValue, gunCadencyMinValue,
        
        bulletDamageLevel, bulletDamageInitValue, bulletDamageIncrement,    // BULLET
        
        
        
        enemyLifeDenom, enemySpeedDenom, enemyAttackDenom,   // ENEMY
        
        enemyOneLifeLevel, enemyOneLifeInitValue,           // ENEMY ONE
        enemyOneSpeedLevel, enemyOneSpeedInitValue,
        enemyOneAttackLevel, enemyOneAttackInitValue,
        
        enemyTwoLifeLevel, enemyTwoLifeInitValue,           // ENEMY TWO
        enemyTwoSpeedLevel, enemyTwoSpeedInitValue,
        enemyTwoAttackLevel, enemyTwoAttackInitValue,
        
        
        
        towerOneDamageLevel, towerOneDamageInitValue, towerOneDamageIncrement,      // TOWER ONE
        towerOneCadencyLevel, towerOneCadencyInitValue, towerOneCadencyMinValue,
        towerOneRangeLevel, towerOneRangeInitValue, towerOneRangeIncrement,
        
        towerTwoDamageLevel, towerTwoDamageInitValue, towerTwoDamageIncrement,      // TOWER TWO
        towerTwoCadencyLevel, towerTwoCadencyInitValue, towerTwoCadencyMinValue,
        towerTwoRangeLevel, towerTwoRangeInitValue, towerTwoRangeIncrement,
        
        
        
        playerLifeLevel, playerLifeInitValue, playerLifeIncrement,    // PLAYER
        playerSpeedLevel, playerSpeedInitValue, playerSpeedIncrement,
    };
}


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
    void ResetParameters();
    
    std::string  GetValue(Parameters::ID key){ return map.find(key)->second; }
    void         SetValue(Parameters::ID key, std::string value){ map.find(key)->second = value; }
    
    float        GetFloat(Parameters::ID key){ return StringUtils::ParseFloat(map.find(key)->second); }
    int          GetInt(Parameters::ID key){ return StringUtils::ParseInt(map.find(key)->second); }
    
    void         IncrementInt(Parameters::ID key, int value);
    void         IncrementFloat(Parameters::ID key, float value);
    
    void         DecrementInt(Parameters::ID key, int value);
    void         DecrementFloat(Parameters::ID key, float value);
    
    
    float       GetWorldLife();
    
    float       GetGunDamage();
    float       GetGunCadency();
    
    float       GetBulletDamage();
    
    float       GetPlayerSpeed();
    float       GetPlayerLife();
    
    float       GetTowerOneDamage();
    float       GetTowerOneCadency();
    float       GetTowerOneRange();
    
    float       GetTowerTwoDamage();
    float       GetTowerTwoCadency();
    float       GetTowerTwoRange();
    
    float       GetEnemyOneLife();
    float       GetEnemyOneSpeed();
    float       GetEnemyOneAttack();
    
    float       GetEnemyTwoLife();
    float       GetEnemyTwoSpeed();
    float       GetEnemyTwoAttack();
    
    
    
    bool loaded = false;
    
private:
	static StatusManager* instance;
    
    std::ifstream* streamIn;
    std::ofstream* streamOut;
    
    std::map<Parameters::ID, std::string> map;
    
    //Funciones
    bool FileExists(const std::string filename);
    
    void OpenIn(const std::string filename);
    void OpenOut(const std::string filename);
    
    void CloseIn();
    void CloseOut();
    
    
};

#endif	/* StatusMANAGER_H */

