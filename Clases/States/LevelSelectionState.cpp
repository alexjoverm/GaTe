/* 
 * File:   LevelSelectionState.cpp
 * Author: jc
 * 
 * Created on 24 de abril de 2014, 12:05
 */

#include "LevelSelectionState.h"
#include "../Otros/StringUtils.h"
#include "../Managers/StateManager.h"
#include <iostream>

LevelSelectionState::LevelSelectionState() {
	
	// Por realizar
    resourceManager = ResourceManager::Instance();
    window = RenderWindow::Instance();
	// Eventos
	inputManager = InputManager::Instance();
    
	vNonRealEvents = new std::vector<sf::Event>();
	vRealEvents = new std::vector<sf::Event>();
    
    id = States::ID::LevelSelectionState;
    
    //Players
    musicPlayer = MusicPlayer::Instance();
}

LevelSelectionState::LevelSelectionState(const LevelSelectionState& orig) {
}

LevelSelectionState::~LevelSelectionState() {
	vNonRealEvents->clear(); delete vNonRealEvents; // Como no contiene punteros, no habrá que eliminarlos
	vRealEvents->clear(); delete vRealEvents;
}



//************************  FUNCIONES INICIALES
// Cargamos las texturas del nivel, y las fuentes generales
void LevelSelectionState::LoadResources(){
	try{
		// Texturas
		resourceManager->AddTexture("texMenuLevelSelection", "Recursos/SeleccionNivel.jpg");
		
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


void LevelSelectionState::Init() {
	LoadResources(); // Cargamos recursos
    
    musicPlayer->Play();
	
	// Inicializamos
    fondo= new SpriteSheet(resourceManager->GetTexture("texMenuLevelSelection"));
}


void LevelSelectionState::Clean(){
    // liberamos recursos
    resourceManager->CleanResources();
    delete fondo; fondo=NULL;
    
    vNonRealEvents->clear();
    vRealEvents->clear();
    musicPlayer->Stop();
}



//**************** BUCLES PRINCIPALES **************************

void LevelSelectionState::Update(const Time& timeElapsed)
{
	InputManager::Instance()->Update();
    
    if(InputManager::Instance()->keyR)
        StateManager::Instance()->SetCurrentState(States::ID::LoadingState);
    
    SoundPlayer::Instance()->RemoveStoppedSounds();
}




void LevelSelectionState::Render(float interp)
{
    // Eventos de Tiempo Real
	ProcessRealEvent();

	window->Clear(sf::Color(255,255,255, 255)); // rgba
        
    window->Draw(*fondo); 
        
	window->Display();
}





// ***************************  EVENTOS ***************

void LevelSelectionState::HandleEvents()
{
	sf::Event event = sf::Event();
	
	while (window->PollEvent(event))
		InputManager::Instance()->Process(event);
}


void LevelSelectionState::ProcessRealEvent(){
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
