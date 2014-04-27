/* 
 * File:   Player.h
 * Author: linuxero
 *
 * Created on March 11, 2014, 9:47 AM
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include "EntActive.h"
#include "../MotorPhysics/Colisionable.h"
#include "../Animations/Animable.h"
#include "Gun.h"
#include "../Otros/Clock.h"
#include "../MusicSounds/SoundPlayer.h"

class Player: public EntActive, public Colisionable, public Animable {
public:
	Player(const sf::Texture& tex, const Vector& size);
	Player(const sf::Texture& tex, const Vector& size, const Vector& pos, const Vector& vel=Vector(0.f, 0.f), const Vector& maxvel=Vector(550.f, 550.f));
	Player(const Player& orig);
	virtual ~Player();
	
	virtual const std::string GetClassName() { return "Player"; }
	
	// Bucle de ciclo de vida
	virtual void Draw(RenderWindow& window, float inter);
	virtual void Update(const Time& elapsedTime);
	
	// Pistola
	void AddGun(Gun* g){ guns->push_back(g); }
	void SelectGun(int i){ selectedGun = i; }
	Gun* GetSelectedGun() const{ return guns->at(selectedGun); }
	void Shot(float x, float y);
	
	// Colisiones
	void DoRectangleColisions(const Time& elapsedTime);
	void OnColision(Colision::Type type, const Rectangle& rec, const Time& elapsedTime);
    
    // Movimientos
    void MovementLeft();
    void MovementRight();
    void MovementIdle();
    void Jump();

	virtual void ResetCan(){ canLeft = canRight = true; }
	
	std::vector<Gun*>	*guns;
	int selectedGun;
	float forceJump = 800.f;
	bool canLeft, canRight, canJump;
        bool isShooting;
        bool isMoving;
	
private:
	Clock	*clockReloadGun;
	
	//Controladores
	bool pressA, pressS, pressD; // No se necesita pressW (pulsacion única)

};

#endif	/* PLAYER_H */

