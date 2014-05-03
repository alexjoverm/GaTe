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
		resourceManager->AddTexture("texMenuShop", "Recursos/menuMejoras.jpg");
        resourceManager->AddTexture("texReturn", "Recursos/return.png");
        resourceManager->AddTexture("iconPlus", "Recursos/iconPlus.png");
        resourceManager->AddTexture("iconPlayer", "Recursos/iconPlayer.png");
        resourceManager->AddTexture("iconGun", "Recursos/iconGun.png");
        resourceManager->AddTexture("iconBullet", "Recursos/iconBullet.png");
        resourceManager->AddTexture("iconTower", "Recursos/iconTower.png");
		
		// Fuente
		resourceManager->AddFont("Urban", "Recursos/OpenSans-Regular.ttf");
        
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
    
    returnButton   = new ImageButton(15.f, 15.f, 1, resourceManager->GetTexture("texReturn"));
        
	// Inicializamos
    fondo= new SpriteSheet(resourceManager->GetTexture("texMenuShop"));
    
    StatusManager* st = StatusManager::Instance();
    
    creditText = new sf::Text();
    creditText->setString(st->GetValue(Parameters::credit) + " $");
    creditText->setPosition( 150.f, 30.f);
    creditText->setFont(ResourceManager::Instance()->GetFont("Urban"));
    creditText->setCharacterSize(32);
    creditText->setStyle(sf::Text::Bold);
    
    
//********* IMPROVES
    vImproves = new std::vector<ImproveGroup*>();
    
    // PLAYER
    ImproveGroup* aux = new ImproveGroup(Vector(80.f, 150.f), "Player",  ResourceManager::Instance()->GetTexture("iconPlayer"));
    aux->CreateImprove("Velocidad", Parameters::playerSpeedLevel);
    vImproves->push_back(aux);
        
    // GUN    
    aux = new ImproveGroup(Vector(80.f, 320.f), "Pistola",  ResourceManager::Instance()->GetTexture("iconGun"));
    aux->CreateImprove("Ataque", Parameters::gunDamageLevel);
    aux->CreateImprove("Cadencia", Parameters::gunCadencyLevel);
    vImproves->push_back(aux);
    
    // BULLET
    aux = new ImproveGroup(Vector(80.f, 500.f), "Bala",  ResourceManager::Instance()->GetTexture("iconBullet"));
    aux->CreateImprove("Ataque", Parameters::bulletDamageLevel);
    aux->CreateImprove("Lifetime", Parameters::bulletLifetimeLevel);
    vImproves->push_back(aux);
    
    // TOWERS
    aux = new ImproveGroup(Vector(600.f, 150.f), "Torreta 1",  ResourceManager::Instance()->GetTexture("iconTower"));
    aux->CreateImprove("Ataque", Parameters::towerOneDamageLevel);
    aux->CreateImprove("Cadencia", Parameters::towerOneCadencyLevel);
    aux->CreateImprove("Rango", Parameters::towerOneRangeLevel);
    vImproves->push_back(aux);
    
    aux = new ImproveGroup(Vector(600.f, 340.f), "Torreta 2",  ResourceManager::Instance()->GetTexture("iconTower"));
    aux->CreateImprove("Ataque", Parameters::towerTwoDamageLevel);
    aux->CreateImprove("Cadencia", Parameters::towerTwoCadencyLevel);
    aux->CreateImprove("Rango", Parameters::towerTwoRangeLevel);
    vImproves->push_back(aux);
    
    aux = new ImproveGroup(Vector(600.f, 540.f), "Torreta 3",  ResourceManager::Instance()->GetTexture("iconTower"));
    aux->CreateImprove("Ataque", Parameters::towerThreeDamageLevel);
    aux->CreateImprove("Cadencia", Parameters::towerThreeCadencyLevel);
    aux->CreateImprove("Rango", Parameters::towerThreeRangeLevel);
    vImproves->push_back(aux);
    

}


void ShopState::Clean(){
    // liberamos recursos
    resourceManager->CleanResources();
    delete fondo; fondo=NULL;
    
    while(!vImproves->empty()) 
		delete vImproves->back(), vImproves->pop_back();
	delete vImproves; vImproves=NULL;
    
    delete returnButton; returnButton=NULL;
    delete creditText; creditText=NULL;
    
   
    vNonRealEvents->clear();
    vRealEvents->clear();
    musicPlayer->Stop();
}



//**************** BUCLES PRINCIPALES **************************

void ShopState::Update(const Time& timeElapsed)
{
	InputManager::Instance()->Update();
    
    SoundPlayer::Instance()->RemoveStoppedSounds();
           
    for(int i=0; i<vImproves->size(); i++)
        vImproves->at(i)->Update(timeElapsed);
    
    // credit
    creditText->setString(StatusManager::Instance()->GetValue(Parameters::credit) + " $");
    
    if(returnButton->IsClicked())
        StateManager::Instance()->SetCurrentState(States::LevelSelectionState);
}



void ShopState::Render(float interp)
{
    // Eventos de Tiempo Real
	ProcessRealEvent();

	window->Clear(sf::Color(255,255,255, 255)); // rgba
        
    window->Draw(*fondo); 
    returnButton->Draw(*window);
    window->Draw(*creditText);
    
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
