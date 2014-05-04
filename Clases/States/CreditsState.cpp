/* 
 * File:   CreditsState.cpp
 * Author: jc
 * 
 * Created on 28 de abril de 2014, 11:11
 */

#include "CreditsState.h"

#include "../Otros/StringUtils.h"
#include "../Managers/StateManager.h"
#include <iostream>

CreditsState::CreditsState() {
	
	// Por realizar
    resourceManager = ResourceManager::Instance();
    window = RenderWindow::Instance();
	// Eventos
	inputManager = InputManager::Instance();
    
	vNonRealEvents = new std::vector<sf::Event>();
	vRealEvents = new std::vector<sf::Event>();
    
    id = States::ID::CreditsState;
    
    //Players
    musicPlayer = MusicPlayer::Instance();
}

CreditsState::CreditsState(const CreditsState& orig) {
}

CreditsState::~CreditsState() {
	vNonRealEvents->clear(); delete vNonRealEvents; // Como no contiene punteros, no habrá que eliminarlos
	vRealEvents->clear(); delete vRealEvents;
}



//************************  FUNCIONES INICIALES
// Cargamos las texturas del nivel, y las fuentes generales
void CreditsState::LoadResources(){
	try{
		// Texturas
		resourceManager->AddTexture("texCredits", "Recursos/Screens/Creditos.jpg");
        resourceManager->AddTexture("texReturn", "Recursos/Buttons/return.png");
		
		// Fuente
		resourceManager->AddFont("OpenSans", "Recursos/OpenSans-Regular.ttf");
        
        if(!musicPlayer->isPlaying)
            musicPlayer->Load(Music::MenuTheme);
	}
	catch (std::runtime_error& e)	{
		std::cout << "Exception: " << e.what() << std::endl;
		exit(0);
	}
}


void CreditsState::Init() {
	LoadResources(); // Cargamos recursos
    
    musicPlayer->Play();
    
    returnButton   = new ImageButton(15.f, 15.f, 1, resourceManager->GetTexture("texReturn"));
	
	// Inicializamos
    fondo= new SpriteSheet(resourceManager->GetTexture("texCredits"));
}


void CreditsState::Clean(){
    // liberamos recursos
    resourceManager->CleanResources();
    delete fondo; fondo=NULL;
    
    vNonRealEvents->clear();
    vRealEvents->clear();
}



//**************** BUCLES PRINCIPALES **************************

void CreditsState::Update(const Time& timeElapsed)
{
	InputManager::Instance()->Update();
    
    if(InputManager::Instance()->IsClickedKeyR())
        StateManager::Instance()->SetCurrentState(States::ID::LoadingState);
    
    SoundPlayer::Instance()->RemoveStoppedSounds();
    
    if(returnButton->IsClicked())
       StateManager::Instance()->SetCurrentState(States::ID::MenuState);
}




void CreditsState::Render(float interp)
{
    // Eventos de Tiempo Real
	ProcessRealEvent();

	window->Clear(sf::Color(255,255,255, 255)); // rgba
        
    window->Draw(*fondo); 
    returnButton->Draw(*window);
        
	window->Display();
}





// ***************************  EVENTOS ***************

void CreditsState::HandleEvents()
{
	sf::Event event = sf::Event();
	
	while (window->PollEvent(event))
		InputManager::Instance()->Process(event);
}


void CreditsState::ProcessRealEvent(){
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

