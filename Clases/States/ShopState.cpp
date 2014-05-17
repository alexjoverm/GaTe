/* 
 * File:   ShopState.cpp
 * Author: jc
 * 
 * Created on 24 de abril de 2014, 12:05
 */

#include "ShopState.h"
#include "../Otros/StringUtils.h"
#include "../Managers/StateManager.h"
#include "../Managers/StatusManager.h"
#include <iostream>

ShopState::ShopState() {
	
	// Por realizar
    resourceManager = ResourceManager::Instance();
    window = RenderWindow::Instance();
	// Eventos
	inputManager = InputManager::Instance();
    
	vNonRealEvents = new std::vector<sf::Event>();
	vRealEvents = new std::vector<sf::Event>();
    
    id = States::ID::ShopState;
    
    //Players
    musicPlayer = MusicPlayer::Instance();
}

ShopState::ShopState(const ShopState& orig) {
}

ShopState::~ShopState() {
	vNonRealEvents->clear(); delete vNonRealEvents; // Como no contiene punteros, no habrá que eliminarlos
	vRealEvents->clear(); delete vRealEvents;
    
    
    
    
}



//************************  FUNCIONES INICIALES
// Cargamos las texturas del nivel, y las fuentes generales
void ShopState::LoadResources(){
	try{
		// Texturas
		resourceManager->AddTexture("texMenuShop", "Recursos/Screens/menuMejoras.jpg");
        resourceManager->AddTexture("texMenuShop2", "Recursos/Screens/menuHabilidades.jpg");
        
        resourceManager->AddTexture("habDobleJump", "Recursos/Buttons/spriteSalto.png");
        resourceManager->AddTexture("habAngularShot", "Recursos/Buttons/spriteDisparoAngulo.png");
        resourceManager->AddTexture("habTower2", "Recursos/Buttons/spriteTorreta2Tienda.png");
        resourceManager->AddTexture("habTower3", "Recursos/Buttons/spriteTorreta3Tienda.png");
        
        resourceManager->AddTexture("texReturn", "Recursos/Buttons/return.png");
        resourceManager->AddTexture("iconPlus", "Recursos/Icons/iconPlus.png");
        resourceManager->AddTexture("iconPlayer", "Recursos/Icons/iconPlayer.png");
        resourceManager->AddTexture("iconGun", "Recursos/Icons/iconGun.png");
        resourceManager->AddTexture("iconBullet", "Recursos/Icons/iconBullet.png");
        resourceManager->AddTexture("iconTower", "Recursos/Icons/iconTower.png");
        resourceManager->AddTexture("iconTower2", "Recursos/Icons/iconTower2.png");
        resourceManager->AddTexture("iconTower3", "Recursos/Icons/iconTower3.png");
        resourceManager->AddTexture("iconPortal", "Recursos/Icons/iconPortal.png");
		resourceManager->AddTexture("buttonHab", "Recursos/Buttons/spriteTxtTienda.png");
        resourceManager->AddTexture("buttonImp", "Recursos/Buttons/improvesButton.png");
        
		// Fuente
		resourceManager->AddFont("Urban", "Recursos/Urban_Stone.otf");
        
        if(!musicPlayer->isPlaying)
            musicPlayer->Load(Music::MenuTheme);
	}
	catch (std::runtime_error& e)	{
		std::cout << "Exception: " << e.what() << std::endl;
		exit(0);
	}
}


void ShopState::Init() {
	LoadResources(); // Cargamos recursos
    
    musicPlayer->Play();
    
    returnButton = new ImageButton(15.f, 15.f, 1, resourceManager->GetTexture("texReturn"));
        
	// Inicializamos
    fondo= new SpriteSheet(resourceManager->GetTexture("texMenuShop"));
    fondo2= new SpriteSheet(resourceManager->GetTexture("texMenuShop2"));
    
    StatusManager* st = StatusManager::Instance();
    
    creditText = new sf::Text();
    creditText->setString(st->GetValue(Parameters::credit) + " $");
    creditText->setPosition( 300.f, 10.f);
    creditText->setFont(ResourceManager::Instance()->GetFont("Urban"));
    creditText->setCharacterSize(35);
    creditText->setColor(sf::Color(250,220,60,255));
    creditText->setStyle(sf::Text::Bold);
    
    towersText = new sf::Text();
    towersText->setString("Warks");
    towersText->setPosition(475.f, 130.f);
    towersText->setFont(ResourceManager::Instance()->GetFont("Urban"));
    towersText->setCharacterSize(32);
    
    habText = new sf::Text();
    habText->setString("Habilidades");
    habText->setPosition(435.f, 435.f);
    habText->setFont(ResourceManager::Instance()->GetFont("Urban"));
    habText->setCharacterSize(32);
    
    
    // Habilidades
    habTower2 = new ImageButton(260.f, 190.f, 3, resourceManager->GetTexture("habTower2"));
    habTower3 = new ImageButton(560.f, 190.f, 3, resourceManager->GetTexture("habTower3"));
    habDobleJump = new ImageButton(260.f, 500.f, 3, resourceManager->GetTexture("habDobleJump"));
    habAngularShot = new ImageButton(560.f, 500.f, 3, resourceManager->GetTexture("habAngularShot"));

    
    
    buttonImproves = new ImageButton(875.f, 10.f, 2, resourceManager->GetTexture("buttonImp"));
    buttonHabilities = new ImageButton(650.f, 10.f, 2, resourceManager->GetTexture("buttonHab"));
    buttonHabilities->SetFrame(1);
    
//********* IMPROVES
    vImproves = new std::vector<ImproveGroup*>();
    
    // PLAYER
    ImproveGroup* aux = new ImproveGroup(Vector(80.f, 150.f), "Jugador",  ResourceManager::Instance()->GetTexture("iconPlayer"));
    aux->CreateImprove("Velocidad", Parameters::playerSpeedLevel);
    vImproves->push_back(aux);
    
    // WORLD
    aux = new ImproveGroup(Vector(80.f, 270.f), "Portal",  ResourceManager::Instance()->GetTexture("iconPortal"));
    aux->CreateImprove("Vida", Parameters::worldLifeLevel);
    vImproves->push_back(aux);
        
    // GUN    
    aux = new ImproveGroup(Vector(80.f, 390.f), "Pistola",  ResourceManager::Instance()->GetTexture("iconGun"));
    aux->CreateImprove("Ataque", Parameters::gunDamageLevel);
    aux->CreateImprove("Cadencia", Parameters::gunCadencyLevel);
    vImproves->push_back(aux);
    
    // BULLET
    aux = new ImproveGroup(Vector(80.f, 550.f), "Bala",  ResourceManager::Instance()->GetTexture("iconBullet"));
    aux->CreateImprove("Ataque", Parameters::bulletDamageLevel);
    aux->CreateImprove("Lifetime", Parameters::bulletLifetimeLevel);
    vImproves->push_back(aux);
    
    // TOWERS
    aux = new ImproveGroup(Vector(600.f, 150.f), "Shooter",  ResourceManager::Instance()->GetTexture("iconTower"));
    aux->CreateImprove("Ataque", Parameters::towerOneDamageLevel);
    aux->CreateImprove("Cadencia", Parameters::towerOneCadencyLevel);
    aux->CreateImprove("Rango", Parameters::towerOneRangeLevel);
    vImproves->push_back(aux);
    
    aux = new ImproveGroup(Vector(600.f, 340.f), "Delayer",  ResourceManager::Instance()->GetTexture("iconTower2"));
    aux->CreateImprove("Ataque", Parameters::towerTwoDamageLevel);
    aux->CreateImprove("Cadencia", Parameters::towerTwoCadencyLevel);
    aux->CreateImprove("Rango", Parameters::towerTwoRangeLevel);
    
    if(StatusManager::Instance()->GetInt(Parameters::unlockedTowers) < 2)
        aux->active = false;
    
    vImproves->push_back(aux);
    
    aux = new ImproveGroup(Vector(600.f, 540.f), "Destroyer",  ResourceManager::Instance()->GetTexture("iconTower3"));
    aux->CreateImprove("Ataque", Parameters::towerThreeDamageLevel);
    aux->CreateImprove("Cadencia", Parameters::towerThreeCadencyLevel);
    aux->CreateImprove("Rango", Parameters::towerThreeRangeLevel);
    if(StatusManager::Instance()->GetInt(Parameters::unlockedTowers) < 3)
        aux->active = false;
    vImproves->push_back(aux);
    

}


void ShopState::Clean(){
    // liberamos recursos
    resourceManager->CleanResources();
    delete fondo; fondo=NULL;
    delete fondo2; fondo2=NULL;
    
    while(!vImproves->empty()) 
		delete vImproves->back(), vImproves->pop_back();
	delete vImproves; vImproves=NULL;
    
    delete returnButton; returnButton=NULL;
    delete creditText; creditText=NULL;
    
    delete buttonHabilities; buttonHabilities = NULL;
    delete buttonImproves; buttonImproves =  NULL;
    
    delete habText; habText = NULL;
    delete towersText; towersText = NULL;
    
   
    vNonRealEvents->clear();
    vRealEvents->clear();
    musicPlayer->Stop();
}



//**************** BUCLES PRINCIPALES **************************

void ShopState::Update(const Time& timeElapsed)
{
	InputManager::Instance()->Update();
    
    SoundPlayer::Instance()->RemoveStoppedSounds();
    
    if(buttonHabilities->currentFrame == 1 && buttonHabilities->IsClicked())   // Cambio a Habilidades
    {
        buttonHabilities->SetFrame(0);
        buttonImproves->SetFrame(1);
        
        for(int i=0; i<vImproves->size(); i++)
            vImproves->at(i)->active = false;
    }
    else if(buttonImproves->currentFrame == 1 && buttonImproves->IsClicked())  // A Mejoras
    {
        buttonHabilities->SetFrame(1);
        buttonImproves->SetFrame(0);
        
        for(int i=0; i<vImproves->size(); i++)
            vImproves->at(i)->active = true;
        
        // Comprobar Torr1 y 2
        if(StatusManager::Instance()->GetInt(Parameters::unlockedTowers) < 3)
            vImproves->at(vImproves->size() - 1)->active = false;
        else
            vImproves->at(vImproves->size() - 1)->active = true;
        
        if(StatusManager::Instance()->GetInt(Parameters::unlockedTowers) < 2)
            vImproves->at(vImproves->size() - 2)->active = false;
        else
            vImproves->at(vImproves->size() - 2)->active = true;
    }
    
         
   // Update de ImproveGroups (si estan en false no se harán)
    for(int i=0; i<vImproves->size(); i++)
        vImproves->at(i)->Update(timeElapsed);
    
    // Update de los habilities
    if(buttonHabilities->currentFrame == 0)
    {
        float credit = StatusManager::Instance()->GetFloat(Parameters::credit);
        
        if(StatusManager::Instance()->GetInt(Parameters::unlockedTowers) < 2){
            if(StatusManager::Instance()->GetInt(Parameters::priceBuyTowerTwo) > credit)
                habTower2->SetFrame(0);
            else{
                habTower2->SetFrame(1);
                if(habTower2->IsClicked()){
                    StatusManager::Instance()->SetValue(Parameters::unlockedTowers, "2");
                    StatusManager::Instance()->DecrementFloat(Parameters::credit, StatusManager::Instance()->GetFloat(Parameters::priceBuyTowerTwo));
                }
            }
        }
        else
            habTower2->SetFrame(2);
        
        if(StatusManager::Instance()->GetInt(Parameters::unlockedTowers) < 3){
            if(StatusManager::Instance()->GetInt(Parameters::priceBuyTowerThree) > credit || StatusManager::Instance()->GetInt(Parameters::unlockedTowers) < 2)
                habTower3->SetFrame(0);
            else{
                habTower3->SetFrame(1);
                if(habTower3->IsClicked()){
                    StatusManager::Instance()->SetValue(Parameters::unlockedTowers, "3");
                    StatusManager::Instance()->DecrementFloat(Parameters::credit, StatusManager::Instance()->GetFloat(Parameters::priceBuyTowerThree));
                }
            }
        }
        else
            habTower3->SetFrame(2);
        
        
        if(StatusManager::Instance()->GetInt(Parameters::habilityDobleJump) == 0){
            if(StatusManager::Instance()->GetInt(Parameters::priceHabilityDobleJump) > credit)
                habDobleJump->SetFrame(0);
            else{
                habDobleJump->SetFrame(1);
                if(habDobleJump->IsClicked()){
                    StatusManager::Instance()->SetValue(Parameters::habilityDobleJump, "1");
                    StatusManager::Instance()->DecrementFloat(Parameters::credit, StatusManager::Instance()->GetFloat(Parameters::priceHabilityDobleJump));
                }
            }
        }
        else
            habDobleJump->SetFrame(2);
        
        if(StatusManager::Instance()->GetInt(Parameters::habilityAngularShot) == 0){
            if(StatusManager::Instance()->GetInt(Parameters::priceHabilityAngularShot) > credit)
                habAngularShot->SetFrame(0);
            else{
                habAngularShot->SetFrame(1);
                if(habAngularShot->IsClicked()){
                    StatusManager::Instance()->SetValue(Parameters::habilityAngularShot, "1");
                    StatusManager::Instance()->DecrementFloat(Parameters::credit, StatusManager::Instance()->GetFloat(Parameters::priceHabilityAngularShot));
                }
            }
        }
        else
            habAngularShot->SetFrame(2);
        
        
        habAngularShot->Update(timeElapsed);
        habDobleJump->Update(timeElapsed);
        habTower3->Update(timeElapsed);
        habTower2->Update(timeElapsed);
    }

    
    // credit
    creditText->setString(StatusManager::Instance()->GetValue(Parameters::credit) + " $");
    
    if(InputManager::Instance()->IsPressedKeyA() && InputManager::Instance()->IsPressedKeyS() && InputManager::Instance()->IsPressedKeyD())
        StatusManager::Instance()->SetValue(Parameters::credit, "5000");
    
    if(returnButton->IsClicked())
        StateManager::Instance()->SetCurrentState(States::LevelSelectionState);
}



void ShopState::Render(float interp)
{
    // Eventos de Tiempo Real
	ProcessRealEvent();

	window->Clear(sf::Color(255,255,255, 255)); // rgba
        
    if(buttonHabilities->currentFrame == 0)
        window->Draw(*fondo2); 
    else
        window->Draw(*fondo); 
    
    returnButton->Draw(*window);
    window->Draw(*creditText);
    
    if(buttonHabilities->currentFrame == 0){
        habAngularShot->Draw(*window);
        habDobleJump->Draw(*window);
        habTower3->Draw(*window);
        habTower2->Draw(*window);
        window->Draw(*towersText);
        window->Draw(*habText);
    }
    
    
    buttonHabilities->Draw(*window);
    buttonImproves->Draw(*window);
    
    for(int i=0; i<vImproves->size(); i++)
        vImproves->at(i)->Draw();

	window->Display();
}





// ***************************  EVENTOS ***************

void ShopState::HandleEvents()
{
	sf::Event event = sf::Event();
	
	while (window->PollEvent(event))
		InputManager::Instance()->Process(event);
}


void ShopState::ProcessRealEvent(){
	bool buttonLeft , buttonRight;
	buttonLeft = buttonRight = false;
	
	sf::Event ev;
	
	for (int i = 0; i < vRealEvents->size(); i++) {
		ev = vRealEvents->at(i);
		
		if(ev.type == sf::Event::MouseButtonPressed)
		{
		}	
	}
	
	vRealEvents->clear();
}
