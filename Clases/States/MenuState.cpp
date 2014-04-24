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

MenuState::MenuState() {
	
    resourceManager = ResourceManager::Instance();
    window = RenderWindow::Instance();
    
    vButtons = new std::vector<Button*>();
    
    
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
		resourceManager->AddTexture("texBackground", "Recursos/fondoMenu.jpg");
		
		// Fuente
		resourceManager->AddFont("Urban", "Recursos/Urban_Stone.otf");
	}
	catch (std::runtime_error& e)	{
		std::cout << "Exception: " << e.what() << std::endl;
		exit(0);
	}
}


void MenuState::Init() {
	LoadResources(); // Cargamos recursos
	
	// Inicializamos fuentes
	background = new SpriteSheet(resourceManager->GetTexture("texBackground"));
    
    for(int i=0; i<6; i++)         //  w , h  ,  x   ,  y,            contenido
        vButtons->push_back(new Button(0.f, 0.f, 512.f, 380.f + 50.f*i, ""));

    
    vButtons->at(0)->SetText("Nueva Partida");
    vButtons->at(1)->SetText("Continuar");
    vButtons->at(2)->SetText("Tutorial");
    vButtons->at(3)->SetText("Opciones");
    vButtons->at(4)->SetText("Acerca De");
    vButtons->at(5)->SetText("Salir");
    
    for(int i=0; i<6; i++)         //  w , h  ,  x   ,  y,            contenido
        vButtons->at(i)->Center();
    
    requestStateChange = false;
}


void MenuState::Clean(){
    // liberamos recursos
    resourceManager->CleanResources();
    
    delete background; background=NULL;
    
    while(!vButtons->empty()) 
		delete vButtons->back(), vButtons->pop_back();
    
    vNonRealEvents->clear();
    vRealEvents->clear();
}



//**************** BUCLES PRINCIPALES **************************

void MenuState::Update(const Time& timeElapsed)
{
    InputManager::Instance()->Update();
    
    for(int i=0; i<vButtons->size(); i++)
        vButtons->at(i)->Update(timeElapsed);
}




void MenuState::Render(float interp)
{
    // Eventos de Tiempo Real
    ProcessRealEvent();
    
	window->Clear(sf::Color(255,255,255, 255)); // rgba
 // HUD
	window->Draw(*background);
    for(int i=0; i<vButtons->size(); i++)
        vButtons->at(i)->Draw(interp);
    
	window->Display();
    
    if(requestStateChange)
       StateManager::Instance()->SetCurrentState(States::ID::LoadingState); 
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
            if(ev.mouseButton.button == sf::Mouse::Left){
                if(vButtons->at(0)->IsPressed(ev.mouseButton.x, ev.mouseButton.y))
                    requestStateChange = true;
            }
		}	
	}
	
	vRealEvents->clear();
}