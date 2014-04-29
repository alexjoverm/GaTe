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
    posPlace = new Vector(); 
    overlay = new sf::RectangleShape();
    overlay->setFillColor(sf::Color(0,0,0 , 50));
        
    sf::Vector2f pos(0, WorldState::Instance()->hud->GetHeight());
    sf::Vector2f size(RenderWindow::Instance()->renderWindow->getSize());
    
    overlay->setPosition(pos);
    overlay->setSize(size);
    
    tower = new Tower(resourceManager->GetTexture("texTower"), Vector(sf::Mouse::getPosition(*window->renderWindow).x,sf::Mouse::getPosition(*window->renderWindow).y) ,50.0 );

}


void NewTowerState::Clean(){
    // liberamos recursos
    //resourceManager->CleanResources();
    
    delete tower; tower=NULL;
    delete posPlace; posPlace=NULL;
    delete overlay; overlay=NULL;
}



//**************** BUCLES PRINCIPALES **************************

void NewTowerState::Update(const Time& timeElapsed)
{
    
    inputManager->Update();
        

    if(inputManager->IsClickedMouseLeft() && rightPlace)
        WorldState::Instance()->AddTower(tower);        
            
    
    
    
    rightPlace = true;
    
    // Que no intersecte con ninguna otra torre y ningún rectángulo de colisión
    for(int i=0; i<WorldState::Instance()->vTowers->size() && rightPlace; i++)
        if(tower->GetSprite()->getGlobalBounds().Intersects(WorldState::Instance()->vTowers->at(i)->GetSprite()->getGlobalBounds()))
            rightPlace=false;
        
    
    float y_aux = -1.f;
    
    // Que esté entre los límites en X de los suelos
    // Que el BottomLeft.Y sea mayor o igual a cualquier Rectángulo de colision (hasta un límite de Factor)
    for(int i=0; i<WorldState::Instance()->level->vRectColision->size() && rightPlace; i++){
        
        float dif = tower->GetSprite()->getGlobalBounds().GetBottomLeft().GetY() - WorldState::Instance()->level->vRectColision->at(i)->GetTopLeft().GetY();
        
        if(tower->GetSprite()->getGlobalBounds().Intersects(*WorldState::Instance()->level->vRectColision->at(i)))
            rightPlace=false;
        else if(dif <= 0.f && dif > -30.f
             && tower->GetSprite()->getGlobalBounds().GetBottomLeft().GetX() >= WorldState::Instance()->level->vRectColision->at(i)->GetTopLeft().GetX() - 10.f
             && tower->GetSprite()->getGlobalBounds().GetBottomRight().GetX() <= WorldState::Instance()->level->vRectColision->at(i)->GetTopRight().GetX() + 10.f
            )
            y_aux = WorldState::Instance()->level->vRectColision->at(i)->GetTopLeft().GetY();
    }
    
    rightPlace = (rightPlace && y_aux != -1.f);
    
    if(rightPlace)
        tower->SetRangeColor(sf::Color(0,255,0, 100));
    else
        tower->SetRangeColor(sf::Color(255,0,0, 100));
    
    
    if(inputManager->IsReleasedKeySpace())
        StateManager::Instance()->SetCurrentState(States::ID::WorldState);
}




void NewTowerState::Render(float interp)
{
        
        sf::Vector2f aux = RenderWindow::Instance()->renderWindow->mapPixelToCoords(
            sf::Vector2i(inputManager->GetMousePosition().GetX(), inputManager->GetMousePosition().GetY()) , 
            WorldState::Instance()->GetCamera()->standard
        );
        
        WorldState::Instance()->GetCamera()->SetCurrentView(Views::Type::Fixed);
        
        window->Draw(*overlay);
        
        WorldState::Instance()->GetCamera()->SetCurrentView(Views::Type::Standard);
        
        tower->SetColor(sf::Color(255,255,255, 200));       
        
        aux.x -= tower->GetSprite()->getGlobalBounds().GetWidth()/2;
        aux.y -= tower->GetSprite()->getGlobalBounds().GetHeight()/2;
    
        tower->SetPosition(Vector(aux.x, aux.y));
        
        tower->Draw(*window);
        
        WorldState::Instance()->GetCamera()->SetCurrentView(Views::Type::Fixed);
        
 // HUD
	window->Display();
}

void NewTowerState::HandleEvents()
{
	sf::Event event = sf::Event();
	
	while (window->PollEvent(event))
		inputManager->Process(event);
}