/* 
 * File:   World.cpp
 * Author: linuxero
 * 
 * Created on March 15, 2014, 10:40 AM
 */

#include "WorldState.h"
#include "../Managers/StateManager.h"
#include "../Otros/StringUtils.h"
#include <iostream>


//*************************  BORRAR ESTO, Y EN EL UPDATE y CONSTRUCTOR TAMBIÉN
Clock reloj = Clock();


//**************** SINGLETON
WorldState* WorldState::instance = 0;

WorldState* WorldState::Instance() {
	if(instance == 0)
		instance = new WorldState();
	
	return instance;
}


WorldState::WorldState() {
	window = RenderWindow::Instance();
    resourceManager = ResourceManager::Instance();
    inputManager = InputManager::Instance();
    
	vEntityStatic = new std::deque<EntPassive*>();
	vEntityColisionable = new std::deque<Colisionable*>();
	vEntityActive = new std::deque<EntActive*>();
	vBullets = new std::vector<Bullet*>();
	
	// Eventos
	vNonRealEvents = new std::vector<sf::Event>();
	vRealEvents = new std::vector<sf::Event>();
    
    id = States::ID::WorldState;
    hud = NULL;
    
    // Players
    musicPlayer = MusicPlayer::Instance();
    soundPlayer = SoundPlayer::Instance();
}

WorldState::WorldState(const WorldState& orig) {
}

WorldState::~WorldState() {
	delete player;
	delete level;

	while(!vEntityActive->empty()) 
		delete vEntityActive->back(), vEntityActive->pop_back();
	delete vEntityActive;
	
	while(!vEntityStatic->empty()) 
		delete vEntityStatic->back(), vEntityStatic->pop_back();
	delete vEntityStatic;
	
	delete vEntityColisionable;
	delete vBullets;
	
	vNonRealEvents->clear(); delete vNonRealEvents; // Como no contiene punteros, no habrá que eliminarlos
	vRealEvents->clear(); delete vRealEvents;
	
	window = NULL;
	vEntityColisionable=NULL;
	vEntityActive = NULL;
	vEntityStatic = NULL;
    vBullets = NULL;
	player = NULL;
	level = NULL;
	vBullets = NULL;
}



//************************  FUNCIONES INICIALES
// Cargamos las texturas del nivel, y las fuentes generales
void WorldState::LoadResources()
{

	try{
        
        //sf::Lock lock(mMutex);
        level = new Level();
        AddLevelTexture("Recursos/Foe.png");

        // Texturas
        for(int i = 0; i < level->vTextures->size(); i++)	// Del nivel
            resourceManager->AddTexture("texLevel" + StringUtils::ConvertInt(i) , level->vTextures->at(i));
        
        level->LoadMap("mapa1.tmx");

        resourceManager->AddTexture("texCharacter", "Recursos/Character.png");	// Del personaje (le asignamos la 20 por ejemplo)
        resourceManager->AddTexture("texBullet", "Recursos/Bullet.png");
        resourceManager->AddTexture("texGun", "Recursos/pistola.png");
        resourceManager->AddTexture("texRobot", "Recursos/robot.png");
        
        resourceManager->AddTexture("texCoins", "Recursos/dolar.png");
        resourceManager->AddTexture("texClock", "Recursos/time.png");
        resourceManager->AddTexture("texSounds", "Recursos/sounds.png");
        resourceManager->AddTexture("texMusic", "Recursos/music.png");

        //Texturas del HUD
        resourceManager->AddTexture("texHUD", "Recursos/hud.png");

        // Fuente
        resourceManager->AddFont("OpenSans", "Recursos/OpenSans-Regular.ttf");
        
        musicPlayer->Load(Music::ID::Level1Theme);
        soundPlayer->LoadGameSounds();
        
        
	}
	catch (std::runtime_error& e)	{
		std::cout << "Exception: " << e.what() << std::endl;
		exit(0);
	}
}


void WorldState::Init() {
	
//**************** Inicializaciones
    reloj.Restart();
    //LoadResources();
	firstUpdate=false;
    
    musicPlayer->Play();
    
//**************** Mapa y Level
    
    
    std::vector<Rectangle*> vrec = level->map->getLayerCollitions("Colision suelo");
    
    for(int i=0; i < vrec.size(); i++)
        this->AddLevelColision(vrec.at(i));
    
	
//***************** Entities
    
	Enemy* enemy = new Enemy(ResourceManager::Instance()->GetTexture("texLevel0"), Vector(100.f , 100.f), Vector(0.f, 0.f), Vector(500.f, 500.f));
	enemy->SetSpeed(220.f, 0.f);
	
	AddColisionableEntity(enemy);// Añadimos al array de colisionables
	AddActiveEntity(enemy);		// Añadimos al array de elementos activos, para que se pinte
    
	// Inicializamos Player
	player = new Player(resourceManager->GetTexture("texRobot"), Vector(108, 108), Vector(100.f, 100.f));
	player->AddGun(new Gun(resourceManager->GetTexture("texGun"), Vector(300.f, 300.f)));
	player->GetSelectedGun()->SetRelativePos(80.f, 50.f);
    player->GetSelectedGun()->SetLifeTime(1.f);
	player->GetSelectedGun()->SetReloadTime(0.25f);
    
    player->SetColor(sf::Color(255,255,255, 105));
    

//****************** ANIMACIONES
    player->AddAnimation(new Animation("andar", player->GetSprite(), 3, 14, 0.05f, false, true));
    player->AddAnimation(new Animation("andar2", player->GetSprite(), 15, 26, 0.05f, false, true));
    player->SetCurrentAnimation("andar", player->GetSprite());
    player->PlayAnimation();
    
    
//******************* HUD
    hud = new HUD(50.f, "OpenSans");
}


void WorldState::Clean(){
    
//************* Recursos
    resourceManager->CleanResources();
    resourceManager->CleanGameSounds();
    
//************* Variables
	delete player;  player = NULL;
	delete level;   level = NULL;
    
    
//************* Vaciamos Contenedores
    
    // Liberamos memoria SOLO en estos dos vectores, ya que cada elemento
    // estará en Activo o en Pasivo
	while(!vEntityActive->empty()) 
		delete vEntityActive->back(), vEntityActive->pop_back();

	while(!vEntityStatic->empty()) 
		delete vEntityStatic->back(), vEntityStatic->pop_back();
    
    while(!vBullets->empty()) 
		delete vBullets->back(), vBullets->pop_back();
    
    
    // Los demás vectores sólo los limpiamos, ya que la memoria ya la hemos liberado
    // al liberar los vectores anteriores
    vEntityColisionable->clear();
    vBullets->clear();
    
    vNonRealEvents->clear();
    vRealEvents->clear();
    
    
 //**************** HUD
    delete hud; hud = NULL;
    musicPlayer->Stop();
}



//**************** BUCLES PRINCIPALES **************************

void WorldState::Update(const Time& timeElapsed)
{
    if(firstUpdate)
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

        hud->Update(timeElapsed);
        soundPlayer->RemoveStoppedSounds();
	}
	   
}




void WorldState::Render(float interp)
{
    // Eventos de Tiempo Real
    ProcessRealEvent();
        
    //level->map->update(player, interp);
    
	window->Clear(sf::Color(255,255,255, 255)); // rgba
	
    window->renderWindow->setView(level->map->standard);
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
    window->renderWindow->setView(level->map->fixed);
    hud->Draw(*window);
	
	window->Display();
    
    
    if(InputManager::Instance()->keyT)
        StateManager::Instance()->SetCurrentState(States::ID::MenuState);
    
    firstUpdate=true; 
}





// ***************************  EVENTOS ***************

void WorldState::HandleEvents()
{
	sf::Event event = sf::Event();
	
	while (window->PollEvent(event))
		InputManager::Instance()->Process(event);
}

void WorldState::ProcessRealEvent(){
	bool buttonLeft , buttonRight;
	buttonLeft = buttonRight = false;
	
	//sf::Event ev;
	
	if(inputManager->IsPressedMouseLeft())
    {
        // Disparar
        if(inputManager->GetMousePosition().GetY() > hud->GetHeight())
            player->Shot(inputManager->GetMousePosition().GetX(), inputManager->GetMousePosition().GetY());
    }
	
	//vRealEvents->clear();
}