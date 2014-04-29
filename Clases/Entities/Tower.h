/* 
 * File:   Torreta.h
 * Author: jc
 *
 * Created on 19 de marzo de 2014, 10:41
 */

#ifndef TOWER_H
#define	TOWER_H

#include "EntPassive.h"
#include "Enemy.h"
#include <deque>
#include "../Otros/Time.h"
#include "../Otros/Clock.h"

class Tower: public EntPassive {
public:
	Tower(const sf::Texture& tex, const Vector pos,const float ran);
	Tower(const Tower& orig);
	virtual ~Tower();
	
	virtual const std::string GetClassName() { return "Tower"; }
	
	// Bucle de ciclo de vida
	virtual void Draw(RenderWindow& window);
	virtual void Update(const Time& elapsedTime);
	
	virtual void Shot();
    
    virtual void SetPosition(const Vector& v);
    
    void SetRangeColor(sf::Color c){ range_area.setFillColor(c); }
	
	void SetTimes(float lifeT, float reloadT){ lifeTime->SetSeconds(lifeT); reloadTime->SetSeconds(reloadT);}
	
	void SetLifeTime(float time){ lifeTime->SetSeconds(time); }
	void SetReloadTime(float time){ reloadTime->SetSeconds(time); }
	
	Time& GetLifeTime() const { return *lifeTime; }
	Time& GetReloadTime() const { return *reloadTime; }
        
        bool OnRange(float x, float y);
        int  SearchEnemy(Enemy* toSearch);
        void CheckEnemies ();
        
        void AddEnemy(Enemy* ene){ vEnemies->push_back(ene); }
	
	
    std::deque<Enemy*>      *vEnemies;
private:
    
        float                   range;
        
        sf::CircleShape         range_area;
        
        std::deque<Enemy*>      *vGlobalEnemies;
        
	Time                    *lifeTime, *reloadTime;
        
        Clock                   *clockReloadTower;
        
        //Colores
        sf::Color               green = sf::Color(0,255,0,100);
        sf::Color               red = sf::Color(255, 0 ,0,100);
        
        
};

#endif	/* TOWER_H */

