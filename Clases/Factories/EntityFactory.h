/* 
 * File:   EntityFactory.h
 * Author: jc
 *
 * Created on 8 de mayo de 2014, 16:43
 */

#ifndef ENTITYFACTORY_H
#define	ENTITYFACTORY_H

#include "../Entities/Enemy.h"
#include "../States/WorldState.h"

class EntityFactory {
public:

    static Enemy* CreateEnemyOne(const Vector& pos, const Vector& vel=Vector(0.f, 0.f), const Vector& maxvel=Vector(550.f, 550.f));
    static Enemy* CreateEnemyTwo(const Vector& pos, const Vector& vel=Vector(0.f, 0.f), const Vector& maxvel=Vector(550.f, 550.f));
    static Enemy* CreateEnemyThree(const Vector& pos, const Vector& vel=Vector(0.f, 0.f), const Vector& maxvel=Vector(550.f, 550.f));

    static Tower* CreateTowerOne(const Vector& pos);
    static Tower* CreateTowerTwo(const Vector& pos);
};

#endif	/* ENTITYFACTORY_H */

