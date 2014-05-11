/* 
 * File:   PowerUpManager.h
 * Author: jmsm30
 *
 * Created on 30 de abril de 2014, 3:41
 */

#ifndef POWERUPMANAGER_H
#define	POWERUPMANAGER_H

#include "../Entities/PowerUp.h"
#include "../Otros/Time.h"

class PowerUpManager {
public:
    PowerUpManager();
    virtual ~PowerUpManager();
    
    void Update(const Time& timeElapsed);
    
    void AddPowerUp();
    
    void Power(PowerUps::State st);
    
    void SetRespawnTime(float newRespawn){respawnTime = newRespawn;}
    
private:
    
    float                       respawnTime;
    float                       time;
};

#endif	/* POWERUPMANAGER_H */

