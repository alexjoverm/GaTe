/* 
 * File:   World.cpp
 * Author: linuxero
 * 
 * Created on March 15, 2014, 10:40 AM
 */

#include "MenuState.h"
#include "../Otros/StringUtils.h"
#include "../Managers/StateManager.h"
#include "../Managers/StatusManager.h"
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
		resourceManager->AddTexture("texBackground", "Recursos/Screens/fondoMenu.jpg");
        resourceManager->AddTexture("texDialogBack", "Recursos/Screens/fondoVentana.png");
        resourceManager->AddTexture("texDialogYes", "Recursos/Buttons/SiNo.png");
        resourceManager->AddTexture("texDialogNo", "Recursos/Buttons/SiNo.png");
		
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
    releaseMouse = true;
    dialogVisible = false;
    
	LoadResources(); // Cargamos recursos
    
    if(!ConfigurationManager::Instance()->loaded)
        ConfigurationManager::Instance()->LoadConfigurations();
    
    if(!StatusManager::Instance()->loaded)
        StatusManager::Instance()->LoadStatus();
    
    musicPlayer->Play();
	
	// Inicializamos fuentes
	background = new SpriteSheet(resourceManager->GetTexture("texBackground"));
    
    
    // Dialog
    backgroundDialog = new SpriteSheet(resourceManager->GetTexture("texDialogBack"));
    
    Vector posDialog = Vector(
        RenderWindow::Instance()->width/2 - backgroundDialog->getGlobalBounds().GetWidth()/2,
        RenderWindow::Instance()->height/2 - backgroundDialog->getGlobalBounds().GetHeight()/2
    );
    backgroundDialog->SetPosition(posDialog);
    
    
    dialogNo = new ImageButton(posDialog.GetX()+50.f, posDialog.GetY()+100.f, 2, resourceManager->GetTexture("texDialogNo"));
    dialogNo->SetFrame(1);
    dialogYes = new ImageButton(posDialog.GetX()+200.f, posDialog.GetY()+100.f ,2,resourceManager->GetTexture("texDialogYes"));
    
    for(int i=0; i<6; i++)         //  x   ,  y,            contenido
        vButtons->push_back(new Button(512.f, 380.f + 50.f*i, ""));

    
    vButtons->at(0)->SetText("Nueva Partida");
    vButtons->at(1)->SetText("Continuar");
    vButtons->at(2)->SetText("Controles");
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
    delete backgroundDialog; backgroundDialog=NULL;
    
    delete dialogNo; dialogNo=NULL;
    delete dialogYes; dialogYes=NULL;
    
    while(!vButtons->empty()) 
		delete vButtons->back(), vButtons->pop_back();
    
    vNonRealEvents->clear();
    vRealEvents->clear();
}



//**************** BUCLES PRINCIPALES **************************

void MenuState::Update(const Time& timeElapsed)
{
    InputManager::Instance()->Update();
    
    if(InputManager::Instance()->IsReleasedMouseLeft())
        releaseMouse=false;
    
    for(int i=0; i<vButtons->size(); i++)
        vButtons->at(i)->Update(timeElapsed);
    
    if(dialogVisible){
        if(dialogNo->IsClicked())
            dialogVisible=false;
        else if(dialogYes->IsClicked()){
            StatusManager::Instance()->ResetParameters();
            requestStateChange = std::make_pair(States::ID::LevelSelectionState, true);  // Nueva Partida
        }  
    }
    
       
    
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
    
    if(dialogVisible){
        window->Draw(*backgroundDialog);
        dialogNo->Draw(*window);
        dialogYes->Draw(*window);
    }
    
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
	
    if(inputManager->IsPressedMouseLeft() && !releaseMouse)
    {
        Vector posMouse = inputManager->GetMousePosition();
        
        if(!dialogVisible){
            if(vButtons->at(0)->IsPressed(posMouse.GetX(), posMouse.GetY()))
                dialogVisible=true;   
            else if(vButtons->at(1)->IsPressed(posMouse.GetX(), posMouse.GetY()))
               requestStateChange = std::make_pair(States::ID::LevelSelectionState, true);  // Continuar
            else if(vButtons->at(2)->IsPressed(posMouse.GetX(), posMouse.GetY()))
               requestStateChange = std::make_pair(States::ID::TutorialState, true);  // Tutorial
            else if(vButtons->at(3)->IsPressed(posMouse.GetX(), posMouse.GetY()))
               requestStateChange = std::make_pair(States::ID::SettingsState, true);  // Opciones
            else if(vButtons->at(4)->IsPressed(posMouse.GetX(), posMouse.GetY()))
               requestStateChange = std::make_pair(States::ID::CreditsState, true);  // Acerca De
            else if(vButtons->at(5)->IsPressed(posMouse.GetX(), posMouse.GetY())){
                ConfigurationManager::Instance()->SaveConfigurations();                 // Salir
                StatusManager::Instance()->SaveStatus();
                window->Close(); 
            }
        }                                                   
    }
    
	
	//vRealEvents->clear();
}