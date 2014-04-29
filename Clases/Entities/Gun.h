/* 
 * File:   Gun.h
 * Author: linuxero
 *
 * Created on March 16, 2014, 11:21 AM
 */

#ifndef GUN_H
#define	GUN_H

#include "EntActive.h"
#include "../Otros/Time.h"

class Gun: public EntActive {
public:
	Gun(const sf::Texture& tex);
	Gun(const sf::Texture& tex, const Vector& pos, const Vector& vel=Vector(0.f, 0.f), const Vector& maxvel=Vector(600.f, 600.f));
	Gun(const Gun& orig);
	virtual ~Gun();
	
	virtual const std::string GetClassName() { return "Gun"; }
	
	// Bucle de ciclo de vida
    virtual void Draw(RenderWindow& window);
	virtual void Draw(RenderWindow& window, float inter);
	virtual void Update(const Time& elapsedTime);
	void Update(EntActive* ent);
	
	virtual void Shot(const Vector& speed, const Vector& pos);
	
	void SetTimes(float lifeT, float reloadT){ lifeTime->SetSeconds(lifeT); reloadTime->SetSeconds(reloadT);}
	
	void SetLifeTime(float time){ lifeTime->SetSeconds(time); }
	void SetReloadTime(float time){ reloadTime->SetSeconds(time); }
	
	Time& GetLifeTime() const { return *lifeTime; }
	Time& GetReloadTime() const { return *reloadTime; }
	
    // Posición relativa al Player
	Vector GetRelativePos() const{ return *relativePos; }
	void SetRelativePos(float x, float y){ relativePos->Set(x, y); }
	
	
	
private:
	Time		*lifeTime, *reloadTime;
	Vector		*relativePos;
};

#endif	/* GUN_H */

