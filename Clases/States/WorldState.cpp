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
    
    // NO SE DEBE ELIMINAR COLISIONABLE, ya se elimina en los demás vectores
	vEntityStatic = new std::deque<EntPassive*>();
	vEntityColisionable = new std::deque<Colisionable*>();
	vEntityActive = new std::deque<EntActive*>();
	
    vBullets = new std::vector<Bullet*>();
    vTowers = new std::vector<Tower*>();
    vPath = new std::vector<Vector*>();
    vEnemies = new std::deque<Enemy*>();
	
	// Eventos
	vNonRealEvents = new std::vector<sf::Event>();
	vRealEvents = new std::vector<sf::Event>();
    
    id = States::ID::WorldState;
    hud = NULL;
    showTowerRange = false;
    
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
    
    while(!vPath->empty()) 
		delete vPath->back(), vPath->pop_back();
	delete vPath;
    
    while(!vTowers->empty()) 
		delete vTowers->back(), vTowers->pop_back();
	delete vTowers;
    
    while(!vEnemies->empty()) 
		delete vEnemies->back(), vEnemies->pop_back();
	delete vEnemies;
	
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
    delete cam; cam = NULL;
}



//************************  FUNCIONES INICIALES
// Cargamos las texturas del nivel, y las fuentes generales
void WorldState::LoadResources()
{

	try{
        
        //sf::Lock lock(mMutex);
        level = new Level();
        AddLevelTexture("Recursos/enemy1.png");

        // Texturas
        for(int i = 0; i < level->vTextures->size(); i++)	// Del nivel
            resourceManager->AddTexture("texLevel" + StringUtils::ConvertInt(i) , level->vTextures->at(i));
        
        level->LoadMap("mapa2.tmx");

        resourceManager->AddTexture("texBullet", "Recursos/Bullet.png");
        resourceManager->AddTexture("texGun", "Recursos/pistola.png");
        
        resourceManager->AddTexture("texTower", "Recursos/tower.png");
        resourceManager->AddTexture("texPj", "Recursos/pj_final_200_148.png");
        
        
        
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
	firstUpdate=false;
    
    
    
//**************** Mapa y Level
    
    std::vector<Rectangle*> vrec = level->map->GetLayerCollitions("Colision suelo");
    
    for(int i=0; i < vrec.size(); i++)
        AddLevelColision(vrec.at(i));
    
    vrec = level->map->GetLayerCollitions("Colision plataformas");
    
    for(int i=0; i < vrec.size(); i++)
        AddLevelPlatform(vrec.at(i));
    
    
 //***************** WaveManager
    waveManager = new WaveManager();
    waveManager->Init(0.7f, 4.49f);
    
    std::vector<int> vec = std::vector<int>();   // Racha de 3
    for(int i=0; i<3; i++)
        vec.push_back(1);
    
    waveManager->AddWave(vec);
    
    vec = std::vector<int>();                   // Racha de 7
    for(int i=0; i<7; i++)
        vec.push_back(1);
    
    waveManager->AddWave(vec);
    
    vec = std::vector<int>();                   // // Racha de 12
    for(int i=0; i<12; i++)
        vec.push_back(1);
    
    waveManager->AddWave(vec);
    
	
//***************** Entities
    
	// Inicializamos Player
	player = new Player(resourceManager->GetTexture("texPj"), Vector(200, 148), Vector(1700.f, 220.f));
	player->AddGun(new Gun(0.95f, 0.27f));
    player->SetRectangleColision(70, 25, 70, 120);
    //player->SetColor(sf::Color(255,255,255, 105));
    

//****************** ANIMACIONES
        //Animaciones del personaje principal
    player->AddAnimation(new Animation("idle", player->GetSprite(), 1, 29, 0.05f, false, true));
    player->AddAnimation(new Animation("andar", player->GetSprite(), 30, 53, 0.05f, false, true));
    player->AddAnimation(new Animation("disparoCorrer", player->GetSprite(), 54, 77, 0.05f, false, true));
    player->AddAnimation(new Animation("disparoIdle", player->GetSprite(), 78, 78, 0.05f, false, true));
    player->AddAnimation(new Animation("saltar", player->GetSprite(), 79, 88, 0.05f, false, false ));
    player->AddAnimation(new Animation("disparoSaltar", player->GetSprite(), 89, 89, 0.05f, false, true));
    player->SetCurrentAnimation("idle", player->GetSprite());
    player->PlayAnimation();
    

//******************* HUD Y  CAMARA
    // Camera
    cam = new Camera(window->renderWindow);
    cam->Init(player);
    hud = new HUD(50.f, "OpenSans");
    
    if(musicPlayer->GetVolume()==0.f)
        hud->SetFrameMusicButton(0);
    else
        hud->SetFrameMusicButton(1);
    
    if(soundPlayer->active)
        hud->SetFrameSoundButton(1);
    else
        hud->SetFrameSoundButton(0);
    
    musicPlayer->Play();
}


void WorldState::Clean(){
    
//************* Recursos
    resourceManager->CleanResources();
    resourceManager->CleanGameSounds();
    
//************* Variables
    delete waveManager; waveManager = NULL;
    
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
    
    while(!vPath->empty()) 
		delete vPath->back(), vPath->pop_back();
    
    while(!vTowers->empty()) 
		delete vTowers->back(), vTowers->pop_back();

    while(!vEnemies->empty()) 
		delete vEnemies->back(), vEnemies->pop_back();

    
    // Los demás vectores sólo los limpiamos, ya que la memoria ya la hemos liberado
    // al liberar los vectores anteriores
    vEntityColisionable->clear();
    vBullets->clear();
    
    vNonRealEvents->clear();
    vRealEvents->clear();
    
    
 //**************** HUD
    delete hud; hud = NULL;
    musicPlayer->Stop();
  
    delete cam; cam = NULL;
}



//**************** BUCLES PRINCIPALES **************************

void WorldState::Update(const Time& timeElapsed)
{
    if(firstUpdate)
    {
     // MANAGERS
        InputManager::Instance()->Update();
        waveManager->Update(timeElapsed);

        
        
     // BULLETS, hacemos las colisiones aquí
        for(int i = 0; i < vBullets->size(); i++)
            vBullets->at(i)->DoColisions(timeElapsed, i);

    //******************************** UPDATE
        // Player
        player->Update(timeElapsed);

        // EntActive
        for(int i = 0; i < vEntityActive->size(); i++)
            vEntityActive->at(i)->Update(timeElapsed);
        
        // Towers
        for(int i = 0; i < vTowers->size(); i++)
            vTowers->at(i)->Update(timeElapsed);
        
                // Bullets
        for(int i = 0; i < vBullets->size(); i++)
            vBullets->at(i)->Update(timeElapsed);
        
        for(int i = 0; i < vEnemies->size(); i++)
        {
            if(vEnemies->at(i)->die)
            {
                CleanArrays(vEnemies->at(i));
                DeleteEnemy(i);
                i--;
            }
            else if(i<vEnemies->size() && vEnemies->at(i)->win)
            {
                hud->SubstractLife(vEnemies->at(i)->attack);
                CleanArrays(vEnemies->at(i));
                DeleteEnemy(i);
                i--;
            }
                
            if(i<vEnemies->size() && vEnemies->at(i) != NULL)
                vEnemies->at(i)->Update(timeElapsed);
        }
	
        

    //*************** HUD **
        hud->Update(timeElapsed);
        
        if(waveManager->state == Wave::State::Loading)
        {
            int tiempo = waveManager->GetTimeLeft();
            std::string tiempoAux = std::string((tiempo < 10 ? "0"+StringUtils::ConvertInt(tiempo) : StringUtils::ConvertInt(tiempo)));

            hud->SetTimeText(tiempoAux);

            hud->SetWaveText(std::string("Oleada: " + StringUtils::ConvertInt(waveManager->GetCurrentWave()) 
                                            + " / " + StringUtils::ConvertInt(waveManager->GetTotalWaves())));
        }
        
        soundPlayer->RemoveStoppedSounds();
        
        
        //************** MOSTRAR RANGO TORRETAS
        if(inputManager->IsClickedKeyR())
            showTowerRange = !showTowerRange;
        
        if(inputManager->IsClickedKeyM())
            cam->minimapActive = !cam->minimapActive;

        if(inputManager->IsPressedKeySpace())
            StateManager::Instance()->SetCurrentState(States::ID::TowerSelectionState);
    

	}
	   
}




void WorldState::Render(float interp)
{
    // Eventos de Tiempo Real
    if(StateManager::Instance()->currentState == States::ID::WorldState)
        ProcessRealEvent();
        
    
	window->Clear(sf::Color(255,255,255, 255)); // rgba
	
    cam->SetCurrentView(Views::Type::Standard);
    
    level->renderMap();
	
    /*
        Rectangle aux = vEnemies->at(0)->GetRectangleColisionAbsolute();

        sf::RectangleShape rec = sf::RectangleShape();
        rec.setPosition(aux.GetTopLeft().GetX(), aux.GetTopLeft().GetY());
        rec.setSize(sf::Vector2f(aux.GetWidth(), aux.GetHeight()));
        rec.setFillColor(sf::Color::Blue);

        window->Draw(rec);


        for(int i=0; i<vPath->size(); i++){
            cir = sf::CircleShape();
            cir.setPosition(vPath->at(i)->GetX(), vPath->at(i)->GetY());
            cir.setRadius(3.f);
            cir.setFillColor(sf::Color::Black);
            window->renderWindow->draw(cir);
        }
     */
    
	// Renderizamos entidades	
    for(int i = 0; i < vEntityStatic->size(); i++)
		vEntityStatic->at(i)->Draw(*window);
    
    for(int i = 0; i < vTowers->size(); i++)
		vTowers->at(i)->Draw(*window);
    
    // Sin INTERPOLACION
    if(StateManager::Instance()->currentState == States::ID::PauseState || StateManager::Instance()->currentState == States::ID::TowerSelectionState)
    {
        for(int i = 0; i < vEntityActive->size(); i++)
            vEntityActive->at(i)->Draw(*window); 

        for(int i = 0; i < vEnemies->size(); i++)
            vEnemies->at(i)->Draw(*window);

        for(int i = 0; i < vBullets->size(); i++)
            vBullets->at(i)->Draw(*window);

        player->Draw(*window);
    }
    else //Con interpolacion
    {
        for(int i = 0; i < vEntityActive->size(); i++)
            vEntityActive->at(i)->Draw(*window, interp); 

        for(int i = 0; i < vEnemies->size(); i++)
            vEnemies->at(i)->Draw(*window, interp);

        for(int i = 0; i < vBullets->size(); i++)
            vBullets->at(i)->Draw(*window, interp);

        player->Draw(*window, interp);
    }
    
    cam->Update();
    
 // HUD
    cam->SetCurrentView(Views::Type::Fixed);
    hud->Draw(*window);
    
    if(cam->minimapActive)
        level->renderMinimap();
	
    if(inputManager->IsReleasedKeySpace()){
        cam->SetCurrentView(Views::Type::Fixed);
        window->Display();
    }
    
    
    if(inputManager->IsClickedKeyT())
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



void WorldState::CleanArrays(Enemy* en)
{
    for(int i=0; i<vEntityColisionable->size(); i++)
        if(en == vEntityColisionable->at(i)){
            vEntityColisionable->erase(vEntityColisionable->begin()+i);
            break;
        }
    
    for(int i=0; i<vTowers->size(); i++)
        for(int j=0; j<vTowers->at(i)->vEnemies->size(); j++)
            if(en == vTowers->at(i)->vEnemies->at(j)){
                vTowers->at(i)->vEnemies->erase(vTowers->at(i)->vEnemies->begin()+j);
                break;
            }
}