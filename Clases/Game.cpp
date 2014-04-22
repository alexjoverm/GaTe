/* 
 * File:   Game.cpp
 * Author: alejandrojovermorales
 * 
 * Created on April 22, 2014, 1:04 PM
 */

#include "Game.h"

Game::Game() {
    timeUpdate = new Time(1.f/30.f);
    window = new RenderWindow(1280,768,"GaTe");
}

Game::Game(const Game& orig) {
}

Game::~Game() {
    delete timeUpdate;
    delete window;
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
    //stateManager.GetCurrentState().Update(timeElapsed);
}

void Game::Render(float interp){
    //stateManager.GetCurrentState().Render(interp);
}

void Game::HandleEvents(){
    //stateManager.GetCurrentState().HandleEvents();
}


