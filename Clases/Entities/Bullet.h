/* 
 * File:   Bullet.h
 * Author: linuxero
 *
 * Created on March 16, 2014, 11:21 AM
 */

#ifndef BULLET_H
#define	BULLET_H

#include "../Otros/Time.h"
#include "EntActive.h"
#include "../MotorPhysics/Colisionable.h"
#include "../MusicSounds/SoundPlayer.h"

namespace Bullets{
    enum Type{
        Normal, Fire, SpeedDown
    };
}


class Bullet: public EntActive, public Colisionable {
public:
	Bullet(const sf::Texture& tex);
	Bullet(const sf::Texture& tex, const Vector& pos, const Vector& vel=Vector(0.f, 0.f), const Vector& maxvel=Vector(600.f, 600.f));
	Bullet(const Bullet& orig);
	virtual ~Bullet();
	
    virtual void Draw(RenderWindow& window);
	virtual void Draw(RenderWindow& window, float inter);
	virtual void Update(const Time& elapsedTime);
	
	void AddTimeElapsed(const Time& time){ timeElapsed->SetSeconds(timeElapsed->AsSeconds() + time.AsSeconds()); }
	Time& GetTimeElapsed() const { return *timeElapsed; }
	
	// Colisiones. Estas NO se usarán, ya que las colisiones son diferentes
	void DoColisions(const Time& elapsedTime, int i);
	void OnColision(Colision::Type type, const Rectangle& rec, const Time& elapsedTime){};
	
	bool		affectGravity=false;
    
    
    // PARAMETROS
	float		damage;
	
private:
	Time*		timeElapsed;
	
	

};

#endif	/* BULLET_H */

