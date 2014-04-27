/* 
 * File:   World.cpp
 * Author: linuxero
 * 
 * Created on March 15, 2014, 10:40 AM
 */

#include "MenuState.h"
#include "../Otros/StringUtils.h"
#include "../Managers/StateManager.h"
#include "../Managers/ConfigurationManager.h"
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
    
    //Players
    musicPlayer = MusicPlayer::Instance();
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
        
        if(!SoundPlayer::Instance()->loaded)
            SoundPlayer::Instance()->LoadMenuSounds();
        
        if(!musicPlayer->isPlaying)
            musicPlayer->Load(Music::MenuTheme);
	}
	catch (std::runtime_error& e)	{
		std::cout << "Exception: " << e.what() << std::endl;
		exit(0);
	}
}


void MenuState::Init() {
	LoadResources(); // Cargamos recursos
    
    if(!ConfigurationManager::Instance()->loaded)
        ConfigurationManager::Instance()->LoadConfigurations();
    
    musicPlayer->Play();
	
	// Inicializamos fuentes
	background = new SpriteSheet(resourceManager->GetTexture("texBackground"));
    
    for(int i=0; i<6; i++)         //  x   ,  y,            contenido
        vButtons->push_back(new Button(512.f, 380.f + 50.f*i, ""));

    
    vButtons->at(0)->SetText("Nueva Partida");
    vButtons->at(1)->SetText("Continuar");
    vButtons->at(2)->SetText("Tutorial");
    vButtons->at(3)->SetText("Opciones");
    vButtons->at(4)->SetText("Acerca De");
    vButtons->at(5)->SetText("Salir");
    
    for(int i=0; i<6; i++)         //  w , h  ,  x   ,  y,            contenido
        vButtons->at(i)->Center();
    
    requestStateChange = std::make_pair(States::ID::LoadingState,false);
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
    
    if(requestStateChange.second)
       StateManager::Instance()->SetCurrentState(requestStateChange.first);
    
    SoundPlayer::Instance()->RemoveStoppedSounds();
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
	
	//sf::Event ev;
	
    if(inputManager->IsPressedMouseLeft())
    {
        Vector posMouse = inputManager->GetMousePosition();
        
        if(vButtons->at(0)->IsPressed(posMouse.GetX(), posMouse.GetY()))
           requestStateChange = std::make_pair(States::ID::LevelSelectionState, true);  // Nueva Partida
        if(vButtons->at(1)->IsPressed(posMouse.GetX(), posMouse.GetY()))
           requestStateChange = std::make_pair(States::ID::LevelSelectionState, true);  // Continuar
        if(vButtons->at(2)->IsPressed(posMouse.GetX(), posMouse.GetY()))
           requestStateChange = std::make_pair(States::ID::LevelSelectionState, true);  // Tutorial
        if(vButtons->at(3)->IsPressed(posMouse.GetX(), posMouse.GetY()))
           requestStateChange = std::make_pair(States::ID::SettingsState, true);  // Opciones
        if(vButtons->at(4)->IsPressed(posMouse.GetX(), posMouse.GetY()))
           requestStateChange = std::make_pair(States::ID::SettingsState, true);  // Acerca De
        if(vButtons->at(5)->IsPressed(posMouse.GetX(), posMouse.GetY())){
            ConfigurationManager::Instance()->SaveConfigurations();                 // Salir
            window->Close(); 
        }
                                                                       
    }
    
	
	//vRealEvents->clear();
}