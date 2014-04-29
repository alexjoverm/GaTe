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
                resourceManager->AddTexture("texReturn", "Recursos/return.png");
                resourceManager->AddTexture("texEsferas1", "Recursos/esferas1.png");
                resourceManager->AddTexture("texEsferas2", "Recursos/esferas2.png");
                resourceManager->AddTexture("texEsferas3", "Recursos/esferas3.png");
		
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


void LevelSelectionState::Init() {
	LoadResources(); // Cargamos recursos
    
    musicPlayer->Play();
    
    returnButton   = new ImageButton(15.f, 15.f, 1, resourceManager->GetTexture("texReturn"));
    levelOneButton   = new ImageButton(230.f, 290.f, 2, resourceManager->GetTexture("texEsferas1"));
    levelTwoButton   = new ImageButton(580.f, 445.f, 2, resourceManager->GetTexture("texEsferas2"));
    levelThreeButton   = new ImageButton(525.f, 120.f, 2, resourceManager->GetTexture("texEsferas3"));
	
    txtlevelOne = new sf::Text();
    txtlevelOne->setPosition(190.f, 240.f);
    txtlevelOne->setFont(resourceManager->GetFont("Urban"));
    txtlevelOne->setCharacterSize(28);
    txtlevelOne->setString("Nivel 1");
    
    txtlevelTwo = new sf::Text();
    txtlevelTwo->setPosition(550.f, 540.f);
    txtlevelTwo->setFont(resourceManager->GetFont("Urban"));
    txtlevelTwo->setCharacterSize(28);
    txtlevelTwo->setString("Nivel 2");
    
    txtlevelThree = new sf::Text();
    txtlevelThree->setPosition(480.f, 80.f);
    txtlevelThree->setFont(resourceManager->GetFont("Urban"));
    txtlevelThree->setCharacterSize(28);
    txtlevelThree->setString("Nivel 3");
        
	// Inicializamos
    fondo= new SpriteSheet(resourceManager->GetTexture("texMenuLevelSelection"));
    
    requestStateChange = std::make_pair(States::ID::LoadingState,false);
}


void LevelSelectionState::Clean(){
    // liberamos recursos
    resourceManager->CleanResources();
    delete fondo; fondo=NULL;
    
  
    delete txtlevelOne; txtlevelOne=NULL;
    delete txtlevelTwo; txtlevelTwo=NULL;
    delete txtlevelThree; txtlevelThree=NULL;
    
    delete returnButton; returnButton=NULL;
    delete levelOneButton; levelOneButton=NULL;
    delete levelTwoButton; levelTwoButton=NULL;
    delete levelThreeButton; levelThreeButton=NULL;
    
   
    vNonRealEvents->clear();
    vRealEvents->clear();
    musicPlayer->Stop();
}



//**************** BUCLES PRINCIPALES **************************

void LevelSelectionState::Update(const Time& timeElapsed)
{
	InputManager::Instance()->Update();
    
    SoundPlayer::Instance()->RemoveStoppedSounds();
    
    
    
    //Boton Level 1
    if(levelOneButton->IsHover()){
        levelOneButton->SetFrame(1);
    }else{
        levelOneButton->SetFrame(0);
    }
        
    
    //Boton Level 2
    if(levelTwoButton->IsHover()){
        levelTwoButton->SetFrame(0);
    }else{
        levelTwoButton->SetFrame(0);
    }
    
    //Boton Level 3
    if(levelThreeButton->IsHover()){
        levelThreeButton->SetFrame(0);
    }else{
        levelThreeButton->SetFrame(0);
    }
    
    
    if(returnButton->IsClicked())
        requestStateChange = std::make_pair(States::ID::MenuState, true);
    
    if(levelOneButton->IsClicked())
        requestStateChange = std::make_pair(States::ID::LoadingState, true);
    
    if(requestStateChange.second)
       StateManager::Instance()->SetCurrentState(requestStateChange.first);
}




void LevelSelectionState::Render(float interp)
{
    // Eventos de Tiempo Real
	ProcessRealEvent();

	window->Clear(sf::Color(255,255,255, 255)); // rgba
        
        window->Draw(*fondo); 
        returnButton->Draw(*window);
        levelOneButton->Draw(*window);
        levelTwoButton->Draw(*window);
        levelThreeButton->Draw(*window);
        
        window->Draw(*txtlevelOne);
     window->Draw(*txtlevelThree);
      window->Draw(*txtlevelTwo);
     
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
