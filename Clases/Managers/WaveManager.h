/* 
 * File:   WaveManager.h
 * Author: alejandrojovermorales
 *
 * Created on May 5, 2014, 3:30 PM
 */

#ifndef WAVEMANAGER_H
#define	WAVEMANAGER_H

#include "../Otros/Time.h"

namespace Wave{
    enum State{
        Loading, Waiting, Running, Finished
    };
}

class WaveManager {
public:
    WaveManager();
    virtual ~WaveManager();
    
    void Init(float secondsEnemies, float secondsWaves);
    void Update(const Time& tiElapsed);
    
    bool IsFinished() const{ return (state == Wave::State::Finished); }
    
    void AddWave(std::vector<int> wave) { vEnemies.push_back(wave); }
   // Wave::State GetState() const{ return state; }
    
    void LoadWave(){ state = Wave::State::Loading; }
    
    
private:
    
    Time    *timeElapsed, *timeInBetweenEnemies, *timeInBetweenWaves;
    int     waveCounter, enemyCounter;
    Wave::State    state;
    
    std::vector< std::vector<int> > vEnemies;
    
    void InsertEnemy();
};

#endif	/* WAVEMANAGER_H */

