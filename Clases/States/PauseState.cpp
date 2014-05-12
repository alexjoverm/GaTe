/* 
 * File:   PauseState.cpp
 * Author: aba
 * 
 * Created on May 8, 2014, 11:16 AM
 */

#include "PauseState.h"
#include "../Managers/StateManager.h"
#include "../Managers/StatusManager.h"
#include "WorldState.h"
#include <iostream>


PauseState::PauseState() {
    
    resourceManager = ResourceManager::Instance();
    window = RenderWindow::Instance();

    vButtons = new std::vector<Button*>();
    
    // Eventos
    inputManager = InputManager::Instance();
        
    id = States::ID::PauseState;
}

PauseState::PauseState(const PauseState& orig) {
}

PauseState::~PauseState() {
}

void PauseState::LoadResources(){
}



void PauseState::Init() {

    //LoadResources(); // Cargamos recursos
    requestStateChange = std::make_pair(States::ID::LoadingState,false);
    
    background = new SpriteSheet(resourceManager->GetTexture("texPausaBackground"));
    
    if(WorldState::Instance()->estado != 2) // muerto
        continuarS = new SpriteSheet(resourceManager->GetTexture("texPausaContinuar"));
    
    seleccionS = new SpriteSheet(resourceManager->GetTexture("texPausaSeleccion"));
    menuS      = new SpriteSheet(resourceManager->GetTexture("texPausaMenu"));
    
    
    float windowW = (window->width)/2;
    float windowH = (window->height)/2;
    float bW = (background->getGlobalBounds().GetWidth())/2;
    float bH = (background->getGlobalBounds().GetHeight())/2;
    
    float bX = windowW - bW;
    float bY = windowH - bH;
    
    
    background->SetPosition(Vector(bX, bY));
            
    float backW = background->getGlobalBounds().GetWidth();
    float backH = background->getGlobalBounds().GetHeight();
    
    
    //for(int i=0; i<6; i++)         //  x   ,  y,            contenido
    
    float posIniYtexts = bY + 150.f;
        
    vButtons->push_back(new Button(bX  +  250.f, posIniYtexts, ""));
    vButtons->push_back(new Button(bX  +  250.f, posIniYtexts + 60.f, ""));
    vButtons->push_back(new Button(bX  +  250.f, posIniYtexts + 120.f, ""));

    if(WorldState::Instance()->estado != 2)
        continuarS->SetPosition(Vector(bX + 190.f , posIniYtexts - 10.f));
    
    seleccionS->SetPosition(Vector(bX + 190.f , posIniYtexts + 50.f));
    menuS->SetPosition(Vector( bX + 190.f , posIniYtexts + 110.f));
    
    if(WorldState::Instance()->estado == 0)  // pausa
        vButtons->at(0)->SetText("Continuar");
    else if(WorldState::Instance()->estado == 1) // muerto
        vButtons->at(0)->SetText("Reiniciar nivel");
    else
        vButtons->at(0)->SetText("");
    
    
    if(WorldState::Instance()->estado == 2) // Has ganado
        vButtons->at(1)->SetText("Siguiente nivel");
    else
        vButtons->at(1)->SetText("Seleccion de nivel");
    
    vButtons->at(2)->SetText("Menu Principal");
    
    vButtons->at(0)->SetFontSize(22);
    vButtons->at(1)->SetFontSize(22);
    vButtons->at(2)->SetFontSize(22);
       
    
    
    
    
    overlay = new sf::RectangleShape();
    overlay->setFillColor(sf::Color(0,0,0 , 150));
        
    sf::Vector2f pos(0, WorldState::Instance()->hud->GetHeight());
    sf::Vector2f size(RenderWindow::Instance()->renderWindow->getSize());
    
    overlay->setPosition(pos);
    overlay->setSize(size);


}

void PauseState::Clean(){
    
    //resourceManager->CleanResources();
 
    if(WorldState::Instance()->estado != 2)
        delete continuarS; continuarS=NULL;
        
    delete seleccionS; seleccionS=NULL;
    delete menuS; menuS=NULL;

    
   while(!vButtons->empty()) 
		delete vButtons->back(), vButtons->pop_back();
    
    delete overlay; overlay=NULL;
}



//**************** BUCLES PRINCIPALES **************************

void PauseState::Update(const Time& timeElapsed)
{
    
    inputManager->Update();
    //InputManager::Instance()->Update();

    for(int i=0; i<vButtons->size(); i++)
        vButtons->at(i)->Update(timeElapsed);
    
    if(vButtons->at(0)->IsPressed(InputManager::Instance()->GetMousePosition().GetX(), InputManager::Instance()->GetMousePosition().GetY())){
        if(WorldState::Instance()->estado == 1) // muerto
            requestStateChange = std::make_pair(States::ID::LoadingState ,true);
        else
            requestStateChange = std::make_pair(States::ID::WorldState ,true);
    }

    else if(vButtons->at(1)->IsPressed(InputManager::Instance()->GetMousePosition().GetX(), InputManager::Instance()->GetMousePosition().GetY()))
      requestStateChange = std::make_pair(States::ID::LevelSelectionState,true);
    
    else if(vButtons->at(2)->IsPressed(InputManager::Instance()->GetMousePosition().GetX(), InputManager::Instance()->GetMousePosition().GetY()))
      requestStateChange = std::make_pair(States::ID::MenuState,true);
    
    
    if(requestStateChange.second){
        if(requestStateChange.first != States::WorldState){
            if(WorldState::Instance()->estado < 2)
                StatusManager::Instance()->GoBackMap();
                
            WorldState::Instance()->Clean();
        }
            
        
       StateManager::Instance()->SetCurrentState(requestStateChange.first);
    }

}



void PauseState::Render(float interp)
{
        
        WorldState::Instance()->GetCamera()->SetCurrentView(Views::Type::Fixed);
        
        window->Draw(*overlay);
        window->Draw(*background);
        if(WorldState::Instance()->estado != 2)
            window->Draw(*continuarS);
        window->Draw(*seleccionS);
        window->Draw(*menuS);
        
        if(WorldState::Instance()->estado != 2){
            for(int i=0; i<vButtons->size(); i++)
                vButtons->at(i)->Draw(interp);
        }
        else{
            for(int i=0; i<vButtons->size(); i++)
                vButtons->at(i)->Draw(interp);
        }
        
        
	window->Display();
}


void PauseState::HandleEvents()
{
	sf::Event event = sf::Event();
	
	while (window->PollEvent(event))
		inputManager->Process(event);
}