/* 
 * File:   Gun.h
 * Author: linuxero
 *
 * Created on March 16, 2014, 11:21 AM
 */

#ifndef GUN_H
#define	GUN_H

#include "../Otros/Time.h"
#include "../Otros/Vector.h"
#include "../Entities/Entity.h"
#include "../Otros/Rectangle.h"
#include "../Entities/Bullet.h"

class Gun {
public:
	Gun(float x, float y, float lifeTimeSeconds=0.9f, float bullSpeed=800.f);
	virtual ~Gun();
	
	
	Vector  CalculateAbsolutePosition(Entity* en, bool reverse);
	
    Time            *lifeTime, *reloadTime;
	Vector          *relativePos; // Debe ser un valor entre 0 y 1
    
    float           damage;
    float           bulletSpeed;
    Bullets::Type   typeBullet;
};

#endif	/* GUN_H */

