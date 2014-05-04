/* 
 * File:   World.cpp
 * Author: linuxero
 * 
 * Created on March 15, 2014, 10:40 AM
 */

#include "LoadingState.h"
#include "../Otros/StringUtils.h"
#include "../Managers/StateManager.h"
#include "WorldState.h"
#include <iostream>

LoadingState::LoadingState(){
	
    resourceManager = ResourceManager::Instance();
    window = RenderWindow::Instance();
    
	// Eventos
	inputManager = InputManager::Instance();
    
	vNonRealEvents = new std::vector<sf::Event>();
	vRealEvents = new std::vector<sf::Event>();
    
    id = States::ID::LoadingState;
}

LoadingState::LoadingState(const LoadingState& orig) {
}

LoadingState::~LoadingState() {
	vNonRealEvents->clear(); delete vNonRealEvents; // Como no contiene punteros, no habrá que eliminarlos
	vRealEvents->clear(); delete vRealEvents;
}



//************************  FUNCIONES INICIALES
// Cargamos las texturas del nivel, y las fuentes generales
void LoadingState::LoadResources(){
	try{
		// Texturas
		resourceManager->AddTexture("texBackground", "Recursos/Screens/loading.jpg");
		
		// Fuente
	}
	catch (std::runtime_error& e)	{
		std::cout << "Exception: " << e.what() << std::endl;
		exit(0);
	}
}


void LoadingState::Init() {
    resourceManager->CleanResources();
	LoadResources(); // Cargamos recursos
	
	// Inicializamos fuentes
	background = new SpriteSheet(resourceManager->GetTexture("texBackground"));
    
    seconds = 0.f;
    loaded = false;

    requestStateChange = false;
    //loadingTask = new LoadingTask();
    //loadingTask->Execute();
    
}


void LoadingState::Clean(){
    // liberamos recursos
    resourceManager->EraseTexture("texBackground");
    
    delete background; background=NULL;
    
    vNonRealEvents->clear();
    vRealEvents->clear();
}



//**************** BUCLES PRINCIPALES **************************

void LoadingState::Update(const Time& timeElapsed)
{
    seconds += timeElapsed.AsSeconds();    
}




void LoadingState::Render(float interp)
{
    // Eventos de Tiempo Real
    ProcessRealEvent();
    
	window->Clear(sf::Color(255,255,255, 255)); // rgba
 // HUD
	window->Draw(*background);
    
	window->Display();
    
    if(!loaded){
        WorldState::Instance()->LoadResources();
        loaded = true;
    }
    
    if(seconds > 1.5f)
        requestStateChange=true; 
    
    if(requestStateChange)
       StateManager::Instance()->SetCurrentState(States::ID::WorldState); 
}





// ***************************  EVENTOS ***************

void LoadingState::HandleEvents()
{
	sf::Event event = sf::Event();
	
	while (window->PollEvent(event))
		InputManager::Instance()->Process(event);
}

void LoadingState::ProcessRealEvent(){
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