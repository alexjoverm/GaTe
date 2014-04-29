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
    isShooting = isMoving = false;
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
    isShooting = isMoving = false;
}


Player::Player(const Player& orig): EntActive(orig), Colisionable((EntActive*)this), Animable(spriteSheet) {
}

Player::~Player() {
	while(!guns->empty()) 
		delete guns->back(), guns->pop_back();
	delete guns;
	guns = NULL;
	
	delete clockReloadGun;
	clockReloadGun = NULL;
}

/*****************************   MOVIMIENTOS   ****************/

void Player::Jump(){
	
	if(canJump)
    {
        if(isShooting)
        {
            this->PlayAnimation();
            this->SetCurrentAnimation("disparoSaltar", this->GetSprite());
        }
        else
        {
            this->PlayAnimation();
            this->SetCurrentAnimation("saltar", this->GetSprite());
        }
		this->SetSpeed(this->GetSpeed().GetX(), -forceJump);

		canJump=false;
		affectGravity = !canJump;
	}
}

void Player::MovementLeft(){
    isMoving = true;
    // Animacion de Andar sólo cuando está en el suelo
    if(canJump){
        if(isShooting)
        {
            this->PlayAnimation();
            this->SetCurrentAnimation("disparoCorrer", this->GetSprite());
        }
        else
        {
                this->PlayAnimation();
                this->SetCurrentAnimation("andar", this->GetSprite());
        }
    }
        
    
    if(canLeft)
        SetSpeed(-factorSpeed, GetSpeed().GetY());
    else
        SetSpeed(0.f, GetSpeed().GetY());
}

void Player::MovementRight(){
    isMoving = true;
    if(canJump){
        if(isShooting)
        {
            this->PlayAnimation();
            this->SetCurrentAnimation("disparoCorrer", this->GetSprite());
        }
        else
        {
                this->PlayAnimation();
                this->SetCurrentAnimation("andar", this->GetSprite());
        }
    }
    
    if(canRight)
        SetSpeed(factorSpeed, GetSpeed().GetY());
    else
        SetSpeed(0.f, GetSpeed().GetY());

}


void Player::MovementIdle(){
    isMoving = false;
    if(isShooting && !isMoving)
    {
        //this->SetCurrentAnimation("disparoIdle", this->GetSprite());
    }
    else
    {
        this->PlayAnimation();
        this->SetCurrentAnimation("idle", this->GetSprite());
        SetSpeed(0.f, GetSpeed().GetY());
    }
}


void Player::Shot(float x, float y){
    // Si se ha pasado el tiempo de carga de la pistola
	if(clockReloadGun->GetElapsedTime().AsSeconds() >= guns->at(selectedGun)->GetReloadTime().AsSeconds()){
            if(canJump && !isMoving)
            {
                this->PlayAnimation();
                this->SetCurrentAnimation("disparoIdle", this->GetSprite());
            }
                // Reproducimos sonido
        SoundPlayer::Instance()->Play("shot");
        
        
        
          
         
        // Calculamos posicion mapeada de la pistola
		Vector posPistola = Vector();
        posPistola = guns->at(selectedGun)->GetPosition();
        sf::Vector2i aux = RenderWindow::Instance()->renderWindow->mapCoordsToPixel(sf::Vector2f(posPistola.GetX(), posPistola.GetY()) 
            , WorldState::Instance()->GetCamera()->standard);
        
        posPistola.Set(aux.x , aux.y);
          
        /*   DISPARO ANGULADO
        // Calculamos vector "pistola-raton"
		Vector sp = Vector(x, y); 
		sp -= posPistola;
        
		// Normalizamos y multiplicamos por velocidad de la bala
		Vector norm = sp.GetNormalize();
		norm *= 800.f;*/
        
        // DISPARO RECTO
        
        // Disparar hacia la orientación del personaje
          
         
		
        //  Disparamos
		guns->at(selectedGun)->Shot(Vector(550.f,0.f), guns->at(selectedGun)->GetPosition());
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
            
			// Comprobamos tipo de colision, y hacemos lo que debamos
			type = TypeOfColision(*world->level->vRectColision->at(i), elapsedTime);
			OnColision(type,*world->level->vRectColision->at(i), elapsedTime);
			
			if(type==Colision::Type::BOTTOM)
				isInFloor = true;
            
			colisionado = true;
		}
	}
    
    for(int i=0; i < world->level->vPlatforms->size(); i++){
		if(CheckColision(*world->level->vPlatforms->at(i), elapsedTime)){
			
			// Comprobamos tipo de colision, y hacemos lo que debamos
			type = TypeOfColision(*world->level->vPlatforms->at(i), elapsedTime);
            
            if(type==Colision::Type::BOTTOM && GetSpeed().GetY() >= 0.f){
                OnColision(type,*world->level->vPlatforms->at(i), elapsedTime);
				isInFloor = true;
                colisionado = true;
            }
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


void Player::Draw(RenderWindow& window){
	renderState->Draw(window, *this->spriteSheet);
	GetSelectedGun()->Draw(window);
}


void Player::Update(const Time& elapsedTime){
    
    isPrevReverse = isReverse;
    
	InputManager* im = InputManager::Instance();
    
    if(im->IsPressedKeyA())
        isReverse = true;

    if(im->IsPressedKeyD())
        isReverse = false;
	
// Animaciones
  //  if(this->InitAnim())
    //   this->GetAnimatedSprite()->Update(elapsedTime, isReverse);
    


    
    //Cuando caemos ponemos la animacion de salto
    if(!canJump && !im->IsPressedKeyW() && !isShooting)
    {
        this->PlayAnimation();
        this->SetCurrentAnimation("saltar", this->GetSprite());
    }
    if(!canJump && isShooting)
    {
        this->SetCurrentAnimation("disparoSaltar", this->GetSprite());
    }
    if(canJump && isShooting && isMoving)
    {
        this->SetCurrentAnimation("disparoCorrer", this->GetSprite());
    }
        

    this->spriteSheet->GetSprite()->setTextureRect(this->GetAnimatedSprite()->GetSpriteRect());

// Movimientos
    if(im->IsClickedMouseLeft()) isShooting = true;
    if(im->IsPressedMouseLeft()) isShooting = true;
    else isShooting = false;
    if(im->IsPressedKeyW())
		Jump();
	//else if(im->IsPressedKeyS())
		// GetDown()
	
	if(im->IsPressedKeyA())
        MovementLeft();
	else if(im->IsPressedKeyD())
        MovementRight();
    
    if(im->IsReleasedKeyA() || im->IsReleasedKeyD())
        SetSpeed(0.f, GetSpeed().GetY());
	
	if(!im->IsPressedKeyA() && !im->IsPressedKeyD() && canJump)
        MovementIdle();
    
    
    if(this->InitAnim())
       this->GetAnimatedSprite()->Update(elapsedTime, isReverse);
	
// COLISIONES
	ResetCan();
    ResetLimits();
	DoRectangleColisions(elapsedTime);
	
	
// UPDATE 
    physicsState->Update(elapsedTime, affectGravity);
    
    GetSelectedGun()->Update((EntActive*)this);
}
