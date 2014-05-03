/* 
 * File:   TemporalChange.h
 * Author: jmsm30
 *
 * Created on 3 de mayo de 2014, 3:41
 */

#ifndef TEMPORALCHANGE_H
#define	TEMPORALCHANGE_H

#include "../Managers/StatusManager.h"
#include "../Entities/Enemy.h"

namespace Changes{
    enum State{
       Damage,Speed,SpeedShot,DoubleJump,AngleShoot,Slow
    };
}


class TemporalChange {
public:
    TemporalChange(Changes::State st , float changeLifeTime);
    TemporalChange(Changes::State st , float changeLifeTime, Enemy* changeEnemy);
    TemporalChange(const TemporalChange& orig);
    virtual ~TemporalChange();
    
    bool UpdateBool(const Time& timeElapsed);
    void Draw(RenderWindow* window);
    
    void AddChange();
    void RemoveChange();
    
private:
    float               timeAlive;
    float               lifeTime;
    Changes::State      type;
    
    SpriteSheet*        spritesheet;
    
    Enemy*              enemy;
    
    StatusManager*      status;
    
};

#endif	/* TEMPORALCHANGE_H */

