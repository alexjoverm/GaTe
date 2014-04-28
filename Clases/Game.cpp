/* 
 * File:   Game.cpp
 * Author: alejandrojovermorales
 * 
 * Created on April 22, 2014, 1:04 PM
 */

#include "Game.h"

Game::Game() {
    timeUpdate = new Time(1.f/50.f);
    window = RenderWindow::Instance();
    window->SetFrameLimit(60);
	window->SetVerticalSyncEnabled(true);
    
    stateManager = StateManager::Instance();
}

Game::Game(const Game& orig) {
}

Game::~Game() {
    delete timeUpdate;
}

void Game::Run(){
	
	Clock clock = Clock();
	Time timeSinceLastUpdate = Time();  //Tiempo desde el ultimo cambio de frame
	Time timeElapsed = Time();
	float interpolation;
	
	while (window->IsOpen())
	{		
		timeElapsed = clock.Restart();
		timeSinceLastUpdate += timeElapsed;
		
		HandleEvents();
		
        //Llevamos control en las actualizaciones por frame
		while (timeSinceLastUpdate > *timeUpdate)   // 15 veces/segundo
		{
			timeSinceLastUpdate -= *timeUpdate;
			Update(*timeUpdate); // Realizamos actualizaciones
		}
		
		// Render
		interpolation = (float)std::min(1.f, timeSinceLastUpdate.AsSeconds() / timeUpdate->AsSeconds());
		Render(interpolation);
	}
}


void Game::Update(const Time& timeElapsed){
    stateManager->GetCurrentState()->Update(timeElapsed);
}

void Game::Render(float interp){
    // Si es el de Pausa, renderizamos también el de WorldState
    if(stateManager->GetCurrentState()->id == States::ID::PauseState)
        stateManager->GetState(States::ID::WorldState)->Render(interp);
    
    stateManager->GetCurrentState()->Render(interp);
}

void Game::HandleEvents(){
    stateManager->GetCurrentState()->HandleEvents();
}


