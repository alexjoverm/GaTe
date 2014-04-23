/* 
 * File:   World.cpp
 * Author: linuxero
 * 
 * Created on March 15, 2014, 10:40 AM
 */

#include "MenuState.h"
#include "../Otros/StringUtils.h"
#include "../Managers/StateManager.h"
#include <iostream>


//**************** SINGLETON
MenuState* MenuState::instance = 0;

MenuState* MenuState::Instance() {
	if(instance == 0)
		instance = new MenuState();
	
	return instance;
}


MenuState::MenuState() : textColision() {
	
	// Por realizar
    resourceManager = ResourceManager::Instance();
    window = RenderWindow::Instance();
	// Eventos
	inputManager = InputManager::Instance();
    
	vNonRealEvents = new std::vector<sf::Event>();
	vRealEvents = new std::vector<sf::Event>();
    
    id = States::ID::MenuState;
}

MenuState::MenuState(const MenuState& orig) {
}

MenuState::~MenuState() {
	vNonRealEvents->clear(); delete vNonRealEvents; // Como no contiene punteros, no habrá que eliminarlos
	vRealEvents->clear(); delete vRealEvents;
}



//************************  FUNCIONES INICIALES
// Cargamos las texturas del nivel, y las fuentes generales
void MenuState::LoadResources(){
	try{
		// Texturas
		resourceManager->AddTexture("texMenuFondo", "Recursos/Foe.png");
		
		// Fuente
		resourceManager->AddFont("Juan", "Recursos/OpenSans-Regular.ttf");
	}
	catch (std::runtime_error& e)	{
		std::cout << "Exception: " << e.what() << std::endl;
		exit(0);
	}
}


void MenuState::Init() {
	LoadResources(); // Cargamos recursos
	
	// Inicializamos fuentes
	textColision.setFont(resourceManager->GetFont("Juan"));
	textColision.setPosition(25.f, 25.f);
	textColision.setCharacterSize(13);
	textColision.setColor(sf::Color::Black);
	textColision.setString("Enemy life: 100" );
}


void MenuState::Clean(){
    // liberamos recursos
    resourceManager->CleanResources();
    
    vNonRealEvents->clear();
    vRealEvents->clear();
}



//**************** BUCLES PRINCIPALES **************************

void MenuState::Update(const Time& timeElapsed)
{
	InputManager::Instance()->Update();
    
    if(InputManager::Instance()->keyR)
        StateManager::Instance()->SetCurrentState(States::ID::WorldState);
}




void MenuState::Render(float interp)
{
    // Eventos de Tiempo Real
	ProcessRealEvent();

	window->Clear(sf::Color(255,255,255, 255)); // rgba
 // HUD
	window->Draw(textColision);
	window->Display();
}





// ***************************  EVENTOS ***************

void MenuState::HandleEvents()
{
	sf::Event event = sf::Event();
	
	while (window->PollEvent(event))
		InputManager::Instance()->Process(event);
}

void MenuState::ProcessRealEvent(){
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