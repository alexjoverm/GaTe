/* 
 * File:   NewTowerState.cpp
 * Author: jmsm30
 * 
 * Created on 23 de abril de 2014, 20:45
 */

#include "NewTowerState.h"
#include "../Otros/StringUtils.h"
#include "../Managers/StateManager.h"
#include "WorldState.h"
#include <iostream>

NewTowerState::NewTowerState() {
    
        resourceManager = ResourceManager::Instance();
        window = RenderWindow::Instance();
	// Eventos
	inputManager = InputManager::Instance();
        
        id = States::ID::TowerSelectionState;
}

NewTowerState::NewTowerState(const NewTowerState& orig) {
}

NewTowerState::~NewTowerState() {
}

// Cargamos las texturas del nivel, y las fuentes generales
void NewTowerState::LoadResources(){
	try{
		// Texturas
		
	}
	catch (std::runtime_error& e)	{
		std::cout << "Exception: " << e.what() << std::endl;
		exit(0);
	}
}

void NewTowerState::Init() {

    //LoadResources(); // Cargamos recursos
    rightPlace = true;
    posPlace = Vector( 0.0 , 0.0 ); 
    
    tower = new Tower(resourceManager->GetTexture("texTower"), Vector(sf::Mouse::getPosition(*window->renderWindow).x,sf::Mouse::getPosition(*window->renderWindow).y) ,50.0 );

}


void NewTowerState::Clean(){
    // liberamos recursos
    resourceManager->CleanResources();
    
}



//**************** BUCLES PRINCIPALES **************************

void NewTowerState::Update(const Time& timeElapsed)
{
    
    inputManager->Update();
        

    if(inputManager->IsClickedMouseLeft() && rightPlace)
        WorldState::Instance()->AddTower(tower);        
            
    
    if(inputManager->IsReleasedKeySpace())
        StateManager::Instance()->SetCurrentState(States::ID::WorldState);
    
}




void NewTowerState::Render(float interp)
{
        //window->Clear(sf::Color(255,255,255, 255)); // rgba
        
        tower->SetPosition(
                Vector(
                        sf::Mouse::getPosition(*window->renderWindow).x - ( tower->GetSprite()->GetTexture()->getSize().x/2)
                      , sf::Mouse::getPosition(*window->renderWindow).y - ( tower->GetSprite()->GetTexture()->getSize().y/2) 
                ) 
        );
        tower->Draw(*window);
 // HUD
	window->Display();
}

void NewTowerState::HandleEvents()
{
	sf::Event event = sf::Event();
	
	while (window->PollEvent(event))
		inputManager->Process(event);
}