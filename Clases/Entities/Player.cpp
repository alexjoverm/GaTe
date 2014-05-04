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
#include "../Managers/StatusManager.h"

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
    
    AddGun(new Gun(0.95f, 0.27f));
    
    factorSpeed = StatusManager::Instance()->GetPlayerSpeed();
    factorSpeedIni = factorSpeed;
    
    angularShoot = StatusManager::Instance()->GetInt(Parameters::habilityAngularShot);
    doubleJump =  StatusManager::Instance()->GetInt(Parameters::habilityDobleJump);
    
    jumps = 0;
    
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
    AddGun(new Gun(0.95f, 0.27f));
    
    factorSpeed = StatusManager::Instance()->GetPlayerSpeed();
    factorSpeedIni = factorSpeed;
    
    angularShoot = StatusManager::Instance()->GetInt(Parameters::habilityAngularShot);
    doubleJump =  StatusManager::Instance()->GetInt(Parameters::habilityDobleJump);
    
    jumps = 0;
    
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
	
	if(canJump) {
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

                    if(doubleJump)
                        jumps++;
                    else
                        jumps = 3;       
	}
}

void Player::MovementLeft(){
    isMoving = true;
    // Animacion de Andar sólo cuando está en el suelo
    if(jumps == 0){
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
    if(jumps == 0){
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

	if(clockReloadGun->GetElapsedTime().AsSeconds() >= guns->at(selectedGun)->reloadTime->AsSeconds()){
            if(jumps == 0 && !isMoving)
            {
                this->PlayAnimation();
                this->SetCurrentAnimation("disparoIdle", this->GetSprite());
            }
                // Reproducimos sonido
        SoundPlayer::Instance()->Play("shot");
        
        
         
        // Calculamos posicion mapeada de la pistola
		Vector posPistola = Vector();
        posPistola = guns->at(selectedGun)->CalculateAbsolutePosition(this, isReverse);
      
        Bullet* bAux ;
        
        /*   DISPARO ANGULADO */
        if(angularShoot){
            
            sf::Vector2f aux = RenderWindow::Instance()->renderWindow->mapPixelToCoords(sf::Vector2i(x, y), WorldState::Instance()->GetCamera()->standard);


            // Calculamos vector "pistola-raton"
                    Vector sp = Vector(aux.x,aux.y); 
                    sp -= posPistola;

                    // Normalizamos y multiplicamos por velocidad de la bala
                    Vector norm = sp.GetNormalize();
                    norm *= guns->at(selectedGun)->bulletSpeed;
                    
             //  Disparamos
             bAux = new Bullet(ResourceManager::Instance()->GetTexture("texBullet"), posPistola, norm);
        }
        
        // DISPARO RECTO
        // Disparar hacia la orientación del personaje
        else{
            float speedBull = (isReverse ? -guns->at(selectedGun)->bulletSpeed : guns->at(selectedGun)->bulletSpeed  );
            //  Disparamos
            bAux = new Bullet(ResourceManager::Instance()->GetTexture("texBullet"), posPistola, Vector(speedBull,0.f));
        }
        
        bAux->damage = guns->at(selectedGun)->damage + StatusManager::Instance()->GetBulletDamage();

        WorldState::Instance()->AddBullet(bAux);
        
		clockReloadGun->Restart();
	}
}

//******************** COLISIONES *****************

void Player::DoRectangleColisions(const Time& elapsedTime){
	WorldState* world = WorldState::Instance();
	
	Colision::Type	type;
	bool colisionado = false, isInFloor = false, changedNextPos = false;
    
    for(int i=0; i < world->level->vPlatforms->size(); i++){
		if(CheckColision(*world->level->vPlatforms->at(i), elapsedTime)){
			
			// Comprobamos tipo de colision, y hacemos lo que debamos
			type = TypeOfColision(*world->level->vPlatforms->at(i), elapsedTime);
            
            if(type==Colision::Type::BOTTOM && GetSpeed().GetY() >= 0.f){
                
                if(platformToIgnore < 0)
                    OnColision(type,*world->level->vPlatforms->at(i), elapsedTime);
                else if(i != platformToIgnore)
                    OnColision(type,*world->level->vPlatforms->at(i), elapsedTime);
                
                isInFloor = true;
                colisionado = true;
                
                if(InputManager::Instance()->IsClickedKeyS())
                    platformToIgnore=i;
                
            }
		}
	}
        
        if(!colisionado)
        platformToIgnore = -1;
    
    
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
        
        
    for(int i=0; i < world->vPowers->size(); i++){
		if(CheckColision(world->vPowers->at(i)->GetRectangleColisionAbsolute(), elapsedTime)){
                    
                    world->AddTemporalChange(new TemporalChange( Changes::State(world->vPowers->at(i)->GetType()) , 15.f ) );
                    
                    world->DeletePowerUp(i);
                }
	}
    
        affectGravity = true;
        
	if( (!isInFloor || !colisionado ) && jumps > 1)
		canJump = false;
	else{
            if(isInFloor){
		canJump = true;
                jumps = 0;
                if(platformToIgnore < 0){
                        affectGravity = false;
                }
            }
        }
        
        
    
	 
	
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
	//GetSelectedGun()->Draw(window, inter);
}


void Player::Draw(RenderWindow& window){
	renderState->Draw(window, *this->spriteSheet);
	//GetSelectedGun()->Draw(window);
}


void Player::Update(const Time& elapsedTime){
    
    isPrevReverse = isReverse;
    
	InputManager* im = InputManager::Instance();
    
    if(im->IsPressedKeyA())
        isReverse = true;

    if(im->IsPressedKeyD())
        isReverse = false;
	
// Animaciones
    if(this->InitAnim())
       this->GetAnimatedSprite()->Update(elapsedTime, isReverse);
    


    
    //Cuando caemos ponemos la animacion de salto
    if(jumps != 0 && !im->IsPressedKeyW() && !isShooting)
    {
        this->PlayAnimation();
        this->SetCurrentAnimation("saltar", this->GetSprite());
    }
    if(jumps != 0 && isShooting)
    {
        this->SetCurrentAnimation("disparoSaltar", this->GetSprite());
    }
    if(jumps == 0 && isShooting && isMoving)
    {
        this->SetCurrentAnimation("disparoCorrer", this->GetSprite());
    }
        

    this->spriteSheet->GetSprite()->setTextureRect(this->GetAnimatedSprite()->GetSpriteRect());

// Movimientos
    if(im->IsPressedMouseLeft()) isShooting = true;
    else isShooting = false;
    if(im->IsClickedKeyW())
		Jump();
	
	if(im->IsPressedKeyA())
        MovementLeft();
	else if(im->IsPressedKeyD())
        MovementRight();
    
    if(im->IsReleasedKeyA() && im->IsReleasedKeyD()){
        SetSpeed(0.f, GetSpeed().GetY());
        
        if(jumps == 0)
           MovementIdle(); 
    }
        
    
     if(this->InitAnim())
       this->GetAnimatedSprite()->Update(Time(0.f), isReverse);
    
	
// COLISIONES
	ResetCan();
    ResetLimits();
	DoRectangleColisions(elapsedTime);
	
	
// UPDATE 
    physicsState->Update(elapsedTime, affectGravity);
}
