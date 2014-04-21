/* 
 * File:   World.cpp
 * Author: linuxero
 * 
 * Created on March 15, 2014, 10:40 AM
 */

#include "World.h"
#include "../Otros/StringUtils.h"
#include <iostream>


//*************************  BORRAR ESTO, Y EN EL UPDATE y CONSTRUCTOR TAMBIÉN
Clock reloj = Clock();


//**************** SINGLETON
World* World::instance = 0;

World* World::Instance() {
	if(instance == 0)
		instance = new World();
	
	return instance;
}


World::World() : textColision(), textPlayerSpeed() {
	reloj.Restart();
	
	// Por realizar
	level = new Level();
	
	// Graficos
	window = new RenderWindow(1280,768,"Prueba Arquitectura");
    resourceManager = ResourceManager::Instance();
    
	vEntityStatic = new std::deque<EntPassive*>();
	vEntityColisionable = new std::deque<Colisionable*>();
	vEntityActive = new std::deque<EntActive*>();
	vBullets = new std::vector<Bullet*>();
	
	
	// Temporizadores
	timeUpdate = new Time(1.f/30.f);
	
	// Eventos
	inputManager = InputManager::Instance();
	vNonRealEvents = new std::vector<sf::Event>();
	vRealEvents = new std::vector<sf::Event>();
}

World::World(const World& orig) {
}

World::~World() {
	delete window;
	delete player;
	delete level;
	
	delete timeUpdate;
	
	while(!vEntityColisionable->empty()) 
		delete vEntityColisionable->back(), vEntityColisionable->pop_back();
	delete vEntityColisionable;

	while(!vEntityActive->empty()) 
		delete vEntityActive->back(), vEntityActive->pop_back();
	delete vEntityActive;
	
	while(!vEntityStatic->empty()) 
		delete vEntityStatic->back(), vEntityStatic->pop_back();
	delete vEntityStatic;
	
	while(!vBullets->empty()) 
		delete vBullets->back(), vBullets->pop_back();
	delete vBullets;
	
	vNonRealEvents->clear(); delete vNonRealEvents; // Como no contiene punteros, no habrá que eliminarlos
	vRealEvents->clear(); delete vRealEvents;
	
	window = NULL;
	vEntityColisionable=NULL;
	vEntityActive = NULL;
	vEntityStatic = NULL;
	player = NULL;
	level = NULL;
	timeUpdate = NULL;
	vBullets = NULL;
}

//************************  FUNCIONES INICIALES
// Cargamos las texturas del nivel, y las fuentes generales
void World::LoadResources(){
	if(level == NULL){
		std::cout << "Primero hay que cargar un nivel" << std::endl;
		return;
	}
	
	try{
		// Texturas
		for(int i = 0; i < level->vTextures->size(); i++)	// Del nivel
		{
			std::cout << "texLevel" + StringUtils::ConvertInt(i) << std::endl;
			resourceManager->AddTexture("texLevel" + StringUtils::ConvertInt(i) , level->vTextures->at(i));
		}
		
		resourceManager->AddTexture("texCharacter", "Recursos/Character.png");	// Del personaje (le asignamos la 20 por ejemplo)
		resourceManager->AddTexture("texBullet", "Recursos/Bullet.png");
		resourceManager->AddTexture("texGun", "Recursos/pistola.png");
		resourceManager->AddTexture("texRobot", "Recursos/robot.png");
		
		// Fuente
		resourceManager->AddFont("OpenSans", "Recursos/OpenSans-Regular.ttf");
	}
	catch (std::runtime_error& e)	{
		std::cout << "Exception: " << e.what() << std::endl;
		exit(0);
	}
}


void World::Init() {
	
	LoadResources(); // Cargamos recursos
	
	window->SetFrameLimit(60);
	window->SetVerticalSyncEnabled(true);
	
	// Mapa
    level->LoadMap("mapa1.tmx");
	
    std::vector<Rectangle*> vrec = level->map->getLayerCollitions("Colision suelo");
    
    for(int i=0; i < vrec.size(); i++)
        this->AddLevelColision(vrec.at(i));
    
	// Inicializamos Player
	player = new Player(resourceManager->GetTexture("texRobot"), Vector(108, 108), Vector(260.f, 350.f));
	player->AddGun(new Gun(resourceManager->GetTexture("texGun"), Vector(300.f, 300.f)));
	player->GetSelectedGun()->SetRelativePos(80.f, 50.f);
    player->GetSelectedGun()->SetLifeTime(1.f);
	player->GetSelectedGun()->SetReloadTime(0.25f);
    
  // ******* Aquí se debería cargar la interfaz (HUD) ************
	
	// Inicializamos fuentes
	textColision.setFont(resourceManager->GetFont("OpenSans"));
	textColision.setPosition(25.f, 25.f);
	textColision.setCharacterSize(13);
	textColision.setColor(sf::Color::Black);
	textColision.setString("Enemy life: 100" );
	
	textPlayerSpeed.setFont(resourceManager->GetFont("OpenSans"));
	textPlayerSpeed.setPosition(25.f, 60.f);
	textPlayerSpeed.setCharacterSize(13);
	textPlayerSpeed.setColor(sf::Color::Black);
	textPlayerSpeed.setString("PlayerSpeed: 0, 0");
        
        /*ANIMACIONES*/
        Animation* animationTest = new Animation("andar", player->GetSprite(), 3, 14, 0.05f, false, true);
        Animation* animationTest2 = new Animation("andar2", player->GetSprite(), 15, 26, 0.05f, false, true);

        player->AddAnimation(animationTest);
        player->AddAnimation(animationTest2);
        player->SetCurrentAnimation("andar", player->GetSprite());
        player->PlayAnimation();
}


//**************** BUCLES PRINCIPALES **************************

void World::Run(){
	
	Clock clock = Clock();
	Time timeSinceLastUpdate = Time();  //Tiempo desde el ultimo cambio de frame
	Time timeElapsed = Time();
	float interpolation;
	
	while (window->IsOpen())
	{		
		timeElapsed = clock.Restart();
		timeSinceLastUpdate += timeElapsed;
		
		MoveEvents();
		
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




void World::Update(const Time& timeElapsed)
{
	InputManager::Instance()->Update();
	
 // BULLETS, hacemos las colisiones aquí
	for(int i = 0; i < vBullets->size(); i++)
		vBullets->at(i)->DoColisions(timeElapsed, i);
	
//******************************** UPDATE
	// Player
	player->Update(timeElapsed);
	
	// EntActive
	for(int i = 0; i < vEntityActive->size(); i++)
		vEntityActive->at(i)->Update(timeElapsed);
	
	// Bullets
	for(int i = 0; i < vBullets->size(); i++)
		vBullets->at(i)->Update(timeElapsed);
	

	
	//********** MOVIMIENTO DEL ENEMIGO (¡¡¡¡ SOLO PARA ESTE EJECUTABLE !!!!)
	if(reloj.GetElapsedTime().AsSeconds() >= 0.8f){
		
		reloj.Restart();
		if(vEntityActive->at(0)->GetSpeed().GetX() > 0){
			vEntityActive->at(0)->SetSpeed(-220.f, vEntityActive->at(0)->GetSpeed().GetY());
			vEntityActive->at(0)->GetSprite()->SetOrientation(Transform::Orientation::Left);
		}
		else{
			vEntityActive->at(0)->SetSpeed(220.f, vEntityActive->at(0)->GetSpeed().GetY());
			vEntityActive->at(0)->GetSprite()->SetOrientation(Transform::Orientation::Right);
		}
	}
    
    
    
	
	
//*************** HUD **
	
	textPlayerSpeed.setString("Player\n\tSpeed: "+StringUtils::ConvertVector(player->GetSpeed()) 
								+ "\n\tGravity: "+StringUtils::ConvertVector(player->GetGravity())
								+ "\n\tMaxSpeed: "+StringUtils::ConvertVector(player->GetMaxSpeed())
								+ "\n\tForceJump: "+StringUtils::ConvertFloat(player->forceJump)
	);
	
}




void World::Render(float interp)
{
    // Eventos de Tiempo Real
	ProcessRealEvent();
    
    //level->map->update(player, interp);
    
	window->Clear(sf::Color(255,255,255, 255)); // rgba
	
    level->map->render(true);
	
	// Renderizamos entidades	
	for(int i = 0; i < vEntityStatic->size(); i++)
		vEntityStatic->at(i)->Draw(*window);
    
    for(int i = 0; i < vEntityActive->size(); i++)
		vEntityActive->at(i)->Draw(*window, interp);
	
	for(int i = 0; i < vBullets->size(); i++)
		vBullets->at(i)->Draw(*window, interp);
	
    player->Draw(*window, interp);
    
 // HUD
	window->Draw(textColision);
	window->Draw(textPlayerSpeed);
	
	window->Display();
}





// ***************************  EVENTOS ***************

void World::MoveEvents()
{
	sf::Event event = sf::Event();
	
	while (window->PollEvent(event))
		InputManager::Instance()->Process(event);
}

void World::ProcessRealEvent(){
	bool buttonLeft , buttonRight;
	buttonLeft = buttonRight = false;
	
	sf::Event ev;
	
	for (int i = 0; i < vRealEvents->size(); i++) {
		ev = vRealEvents->at(i);
		
		if(ev.type == sf::Event::MouseButtonPressed)
		{
			if(ev.mouseButton.button == sf::Mouse::Left && !buttonLeft){
				player->Shot(ev.mouseButton.x, ev.mouseButton.y);
				buttonLeft = true;
			}
		}	
	}
	
	vRealEvents->clear();
}