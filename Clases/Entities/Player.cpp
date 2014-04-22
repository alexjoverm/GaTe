/* 
 * File:   Player.cpp
 * Author: linuxero
 * 
 * Created on March 11, 2014, 9:47 AM
 */
#include <iostream>
#include "Player.h"
#include "../Otros/StringUtils.h"
#include "../States/WorldState.h"

Player::Player(const sf::Texture& tex, const Vector& size): EntActive(tex), Colisionable((EntActive*)this), Animable(spriteSheet){
	selectedGun = 0;
	guns = new std::vector<Gun*>();
	clockReloadGun = new Clock();
	clockReloadGun->Restart();
        
        this->SetSizeTile((int)size.GetX(), (int)size.GetY());
        this->GetSprite()->SetNumRowsColumns();
	
	// Controladores
	pressA = pressS = pressD = false;
	canLeft = canRight = true;
	canJump = false;
}

Player::Player(const sf::Texture& tex, const Vector& size, const Vector& pos, const Vector& vel, const Vector& maxvel): EntActive(tex, pos, vel, maxvel), Colisionable((EntActive*)this), Animable(spriteSheet){
	selectedGun = 0;
	guns = new std::vector<Gun*>();
	clockReloadGun = new Clock();
	clockReloadGun->Restart();
	
        //Fjamos el tamaño del o los tiles
        this->SetSizeTile((int)size.GetX(), (int)size.GetY());
        //Calculamos el numero de filas y columnas del spriteSheet
        this->GetSprite()->SetNumRowsColumns();
        
	// Controladores
	pressA = pressS = pressD = false;
	canLeft = canRight = true;
	canJump = false;
}


Player::Player(const Player& orig): EntActive(orig), Colisionable((EntActive*)this), Animable(spriteSheet) {
}

Player::~Player() {
	delete[] guns;
	guns = NULL;
	
	delete clockReloadGun;
	clockReloadGun = NULL;
}


void Player::Jump(){
	
	if(canJump){
		this->SetSpeed(this->GetSpeed().GetX(), -forceJump);

		canJump=false;
		affectGravity = !canJump;
	}
}


void Player::Shot(float x, float y){
	
	if(clockReloadGun->GetElapsedTime().AsSeconds() >= guns->at(selectedGun)->GetReloadTime().AsSeconds()){
		
		//************ ACABAR ESTO
		Vector sp = Vector(0.f, 0.f);
		sp = Vector(x, y);
		sp -= guns->at(selectedGun)->GetPosition();
		
		Vector norm = sp.GetNormalize();
		norm *= 800.f;
		
		guns->at(selectedGun)->Shot(norm, guns->at(selectedGun)->GetPosition());
		clockReloadGun->Restart();
	}
}



//******************** COLISIONES *****************

void Player::DoRectangleColisions(const Time& elapsedTime){
	WorldState* world = WorldState::Instance();
	
	Colision::Type	type;
	bool colisionado = false, isInFloor = false, changedNextPos = false;
	
	for(int i=0; i < world->level->vRectColision->size(); i++){
		if(CheckColision(*world->level->vRectColision->at(i), elapsedTime)){
            if(GetPosition().GetX() >= 350 && GetPosition().GetY() >= 380)
                std::cout << "a" << std::endl;
            
			// Comprobamos tipo de colision, y hacemos lo que debamos
			type = TypeOfColision(*world->level->vRectColision->at(i), elapsedTime);
			OnColision(type,*world->level->vRectColision->at(i), elapsedTime);
			
			if(type==Colision::Type::BOTTOM)
				isInFloor = true;
			
			colisionado = true;
		}
	}
	if(!isInFloor || !colisionado)
		canJump = false;
	else if(isInFloor)
		canJump = true;
	
	affectGravity = !canJump;
}


void Player::OnColision(Colision::Type type, const Rectangle& rec, const Time& elapsedTime){
    
    if(type==Colision::Type::LEFT)
        canRight = false;
    else if(type==Colision::Type::RIGHT)
        canLeft = false;
	
	// Movemos al borde
	MoveToEdge(type, rec, elapsedTime);
}


//************************* BUCLES PRINCIPALES *************************


void Player::Draw(RenderWindow& window, float inter){
	renderState->Draw(window, physicsState->GetPreviousPosition(), physicsState->GetPosition(), inter, *this->spriteSheet);
	GetSelectedGun()->Draw(window, inter);
}


void Player::Update(const Time& elapsedTime){
	InputManager* im = InputManager::Instance();
	
         if(this->InitAnim())
            this->GetAnimatedSprite()->Update(elapsedTime);
        
        this->spriteSheet->GetSprite()->setTextureRect(this->GetAnimatedSprite()->GetSpriteRect());

	// Verticales
	if(im->keyS){
		// GetDown()
	}
	else if(im->keyW){
		Jump();
	}
	
	// Horizontales
	if(im->keyA){
            //Iniciamos animacion y fijamos animacion izquierda
                this->PlayAnimation();
                
                this->SetCurrentAnimation("andar", this->GetSprite());
		if(canLeft)
			SetSpeed(-factorSpeed, GetSpeed().GetY());
		else
			SetSpeed(0.f, GetSpeed().GetY());
		
		this->GetSprite()->SetOrientation(Transform::Orientation::Left);
	}
	else if(im->keyD){
             this->PlayAnimation();
            this->SetCurrentAnimation("andar2", this->GetSprite());
		if(canRight)
			SetSpeed(factorSpeed, GetSpeed().GetY());
		else
			SetSpeed(0.f, GetSpeed().GetY());
		
		this->GetSprite()->SetOrientation(Transform::Orientation::Right);
	}
	else if(!im->keyA || !im->keyD)
        {
           this->StopAnimation();
           SetSpeed(0.f, GetSpeed().GetY());
        }	
	
// COLISIONES
	ResetCan();
    ResetLimits();
	DoRectangleColisions(elapsedTime);
	
	
// UPDATE 
	physicsState->Update(elapsedTime, affectGravity); // Si puede saltar, no se le aplica gravedad (por eso se pone negado)
	GetSelectedGun()->Update((EntActive*)this);
}
