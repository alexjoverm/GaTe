/* 
 * File:   World.cpp
 * Author: linuxero
 * 
 * Created on March 15, 2014, 10:40 AM
 */

#include "SettingsState.h"
#include "../Otros/StringUtils.h"
#include "../Managers/StateManager.h"
#include "../Managers/ConfigurationManager.h"
#include <iostream>


const int posTextsX   = 150;
const int posButtonsX = 500;
const int posY        = 300;
const int marginTop   = 90;


SettingsState::SettingsState() {
	
    resourceManager = ResourceManager::Instance();
    window = RenderWindow::Instance();
    
    // Texts
    vTexts = new std::vector<sf::Text*>();
    
	// Eventos
	inputManager = InputManager::Instance();
    
	vNonRealEvents = new std::vector<sf::Event>();
	vRealEvents = new std::vector<sf::Event>();
    
    id = States::ID::SettingsState;
    
    //Players
    musicPlayer = MusicPlayer::Instance();
    soundPlayer = SoundPlayer::Instance();
}

SettingsState::SettingsState(const SettingsState& orig) {
}

SettingsState::~SettingsState() {
	vNonRealEvents->clear(); delete vNonRealEvents; // Como no contiene punteros, no habrá que eliminarlos
	vRealEvents->clear(); delete vRealEvents;
}



//************************  FUNCIONES INICIALES
// Cargamos las texturas del nivel, y las fuentes generales
void SettingsState::LoadResources(){
	try{
		// Texturas
		resourceManager->AddTexture("texBackground", "Recursos/Screens/fondoMenu.jpg");
		resourceManager->AddTexture("texSwitch", "Recursos/Buttons/switcher.png");
        resourceManager->AddTexture("texReturn", "Recursos/Buttons/return.png");
        
		// Fuente
		resourceManager->AddFont("Urban", "Recursos/Urban_Stone.otf");
	}
	catch (std::runtime_error& e)	{
		std::cout << "Exception: " << e.what() << std::endl;
		exit(0);
	}
}


void SettingsState::Init() {
	LoadResources(); // Cargamos recursos
	
	// Inicializamos
	background = new SpriteSheet(resourceManager->GetTexture("texBackground"));
    
    // Textos
    sf::Text* aux;
    for(int i=0; i<3; i++){
        aux = new sf::Text();
        aux->setPosition(posTextsX, posY + marginTop*i);
        aux->setFont(resourceManager->GetFont("Urban"));
        aux->setCharacterSize(28);
        
        vTexts->push_back(aux);
    }
    aux=NULL;
    
    vTexts->at(0)->setString("Sonido");
    vTexts->at(1)->setString("Musica");
    vTexts->at(2)->setString("Volumen");

    // Botones y Slider
    soundEffects = new ImageButton(posButtonsX, posY, 2, resourceManager->GetTexture("texSwitch"));
    music        = new ImageButton(posButtonsX, posY + marginTop, 2, resourceManager->GetTexture("texSwitch"));
    returnButton   = new ImageButton(15.f, 15.f, 1, resourceManager->GetTexture("texReturn"));
    
    slider = new Slider(posButtonsX, posY + marginTop*2, 200.f, 20.f);
    slider->SetValue(musicPlayer->GetVolume());
    
    
    if(musicPlayer->GetVolume()==0.f)
        SetFrameMusicButton(1);
    else
        SetFrameMusicButton(0);
    
    if(soundPlayer->active)
        SetFrameSoundButton(0);
    else
        SetFrameSoundButton(1);
    
    musicPlayer->Play();
}


void SettingsState::Clean(){
    // liberamos recursos
    resourceManager->CleanResources();
    
    delete background; background=NULL;
    delete soundEffects; soundEffects=NULL;
    delete music; music=NULL;
    delete returnButton; returnButton=NULL;
    
    delete slider; slider=NULL;
    
    
    while(!vTexts->empty()) 
		delete vTexts->back(), vTexts->pop_back();
    
    vNonRealEvents->clear();
    vRealEvents->clear();
}



//**************** BUCLES PRINCIPALES **************************

void SettingsState::Update(const Time& timeElapsed)
{
    InputManager::Instance()->Update();
    
    if(music->IsClicked())
        ToogleMusicButton();
    if(soundEffects->IsClicked())
        ToogleSoundButton();

    if(musicPlayer->GetVolume() != slider->valor){
        musicPlayer->SetVolume(slider->valor);
        if(slider->valor == 0.f)
            SetFrameMusicButton(1);
        else
            SetFrameMusicButton(0);
    }
    
    SoundPlayer::Instance()->RemoveStoppedSounds();
    
    if(returnButton->IsClicked())
       StateManager::Instance()->SetCurrentState(States::ID::MenuState);
}




void SettingsState::Render(float interp)
{
    // Eventos de Tiempo Real
    ProcessRealEvent();
    
	window->Clear(sf::Color(255,255,255, 255)); // rgba
   
	window->Draw(*background);
    
    // Buttons
    music->Draw(*window);
    soundEffects->Draw(*window);
    returnButton->Draw(*window);
    
    slider->Draw(*window);
    
    // Texts
    for(int i=0; i < vTexts->size(); i++)
        window->Draw(*vTexts->at(i));
    
	window->Display();
    
}


void SettingsState::ToogleSoundButton(){
    if(soundEffects->currentFrame==0)
        SetFrameSoundButton(1);
    else
        SetFrameSoundButton(0);
}

void SettingsState::ToogleMusicButton(){
    if(music->currentFrame==0){
        SetFrameMusicButton(1);
        slider->valor = 0.f;
    }
    else{
        SetFrameMusicButton(0);
        slider->valor = musicPlayer->ultVol;
    }
}


void SettingsState::SetFrameSoundButton(int frame){
    if(frame==1)
        SoundPlayer::Instance()->active=false;
    else if(frame==0)
        SoundPlayer::Instance()->active=true;
        
    soundEffects->SetFrame(frame);
}

void SettingsState::SetFrameMusicButton(int frame){
    if(frame==1)
        MusicPlayer::Instance()->DeActivate();
    else if(frame==0)
        MusicPlayer::Instance()->Activate();
        
    music->SetFrame(frame);
}





// ***************************  EVENTOS ***************

void SettingsState::HandleEvents()
{
	sf::Event event = sf::Event();
	
	while (window->PollEvent(event))
		InputManager::Instance()->Process(event);
}

void SettingsState::ProcessRealEvent(){
	bool buttonLeft , buttonRight;
	buttonLeft = buttonRight = false;
}