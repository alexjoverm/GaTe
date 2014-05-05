/* 
 * File:   World.cpp
 * Author: linuxero
 * 
 * Created on March 15, 2014, 10:40 AM
 */

#include "WorldState.h"
#include "../Managers/StateManager.h"
#include "../Managers/StatusManager.h"
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
    vChanges = new std::vector<TemporalChange*>();
    vPowers = new std::vector<PowerUp*>();
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
        
    while(!vPowers->empty())
		delete vPowers->back(), vPowers->pop_back();
	delete vPowers;
        
    while(!vChanges->empty())
		delete vChanges->back(), vChanges->pop_back();
	delete vChanges;
	
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
    delete paralax; paralax = NULL;
}



//************************  FUNCIONES INICIALES
// Cargamos las texturas del nivel, y las fuentes generales
void WorldState::LoadResources()
{

	try{
        
        //sf::Lock lock(mMutex);
        level = new Level();
        //AddLevelTexture("Recursos/enemy1.png");

        // Texturas
        for(int i = 0; i < level->vTextures->size(); i++)	// Del nivel
            resourceManager->AddTexture("texLevel" + StringUtils::ConvertInt(i) , level->vTextures->at(i));
        
        // Texturas PowerUps
        for(int i = 0 ; i < 5 ; i++)
            resourceManager->AddTexture("texPower" + StringUtils::ConvertInt(i), "Recursos/PowerUps/power"+StringUtils::ConvertInt(i)+".png");
        // Texturas PowerUps
        for(int i = 0 ; i < 5 ; i++)
                resourceManager->AddTexture("miniPower" + StringUtils::ConvertInt(i), "Recursos/PowerUps/activePower"+StringUtils::ConvertInt(i)+".png");

        //Texturas Seleccion Torretas 
        for(int i = 1 ; i <= 3 ; i++)
                resourceManager->AddTexture("texButtonTower" + StringUtils::ConvertInt(i), "Recursos/Buttons/SiNo.png");        
        
        level->LoadMap(mapName);

        // Enemies
        resourceManager->AddTexture("texEnemyOne", "Recursos/Sprites/enemyOne.png");
        resourceManager->AddTexture("texEnemyTwo", "Recursos/Sprites/enemyTwo.png");
        resourceManager->AddTexture("texEnemyThree", "Recursos/Sprites/enemyThree.png");
        
        // Towers
        resourceManager->AddTexture("texTowerOne1", "Recursos/Sprites/towerOne1.png");
        resourceManager->AddTexture("texTowerOne2", "Recursos/Sprites/towerOne2.png");
        resourceManager->AddTexture("texTowerOne3", "Recursos/Sprites/towerOne3.png");
        
        resourceManager->AddTexture("texTowerTwo1", "Recursos/Sprites/towerTwo1.png");
        resourceManager->AddTexture("texTowerTwo2", "Recursos/Sprites/towerTwo2.png");
        resourceManager->AddTexture("texTowerTwo3", "Recursos/Sprites/towerTwo3.png");
        
        resourceManager->AddTexture("texTowerThree1", "Recursos/Sprites/towerThree.png");
        resourceManager->AddTexture("texTowerThree2", "Recursos/Sprites/towerThree.png");
        resourceManager->AddTexture("texTowerThree3", "Recursos/Sprites/towerThree.png");
        
        resourceManager->AddTexture("texBullet", "Recursos/Bullet.png");
        
        resourceManager->AddTexture("texPj", "Recursos/Sprites/pj_final_200_148.png");
        
        
        
        resourceManager->AddTexture("texCoins", "Recursos/Icons/dolar.png");
        resourceManager->AddTexture("texClock", "Recursos/Icons/time.png");
        resourceManager->AddTexture("texSounds", "Recursos/Icons/sounds.png");
        resourceManager->AddTexture("texMusic", "Recursos/Icons/music.png");
        
        resourceManager->AddTexture("texPausaContinuar", "Recursos/Icons/ContinuarIcon.png");
        resourceManager->AddTexture("texPausaSeleccion", "Recursos/Icons/SeleccionNivelIcon.png");
        resourceManager->AddTexture("texPausaMenu", "Recursos/Icons/MenuIcon.png");
        resourceManager->AddTexture("texPausaBackground", "Recursos/Screens/pausa.png");

        //Texturas del HUD
        resourceManager->AddTexture("texHUD", "Recursos/hud.png");

        // Fuente
        resourceManager->AddFont("OpenSans", "Recursos/OpenSans-Regular.ttf");
        resourceManager->AddFont("Urban", "Recursos/Urban_Stone.otf");
        
        musicPlayer->Load(Music::ID::Level1Theme);
        soundPlayer->LoadGameSounds();
        
        
	}
	catch (std::runtime_error& e)	{
		std::cout << "Exception: " << e.what() << std::endl;
		exit(0);
	}
}


void WorldState::Init() {
	
    StatusManager::Instance()->DoCopyMap();
    
    
//**************** Inicializaciones
	firstUpdate=false;
    
    
        requestStateChange = std::make_pair(States::ID::LoadingState,false);
    
//**************** Mapa y Level
    
    std::vector<Rectangle*> vrec = level->map->GetLayerCollitions("Colision suelo");
    
    for(int i=0; i < vrec.size(); i++)
        AddLevelColision(vrec.at(i));
    
    vrec = level->map->GetLayerCollitions("Colision plataformas");
    
    for(int i=0; i < vrec.size(); i++)
        AddLevelPlatform(vrec.at(i));
    
        
 //**************** PowerUpManager
    powerUpManager = new PowerUpManager();
    
 //***************** WaveManager
    waveManager = new WaveManager();
    waveManager->Init(
    StringUtils::ParseFloat( level->map->GetMetadata("RespawnNPC") ),
    StringUtils::ParseFloat( level->map->GetMetadata("RespawnOleada") )
    );
    
    int waves = StringUtils::ParseInt( level->map->GetMetadata("NumOleadas") );
            
    for(int i = 0 ; i < waves ; i++)
        waveManager->AddWave( level->map->GetWave(i) );  
	
//***************** Entities
    
	// Inicializamos Player
	player = new Player(resourceManager->GetTexture("texPj"), Vector(200, 148), Vector(1700.f, 220.f));
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
    
    hud->SetCreditText(StatusManager::Instance()->GetValue(Parameters::credit) + " $");
    
    musicPlayer->Play();
    paralax = new Paralax(cam, level->map);
}


void WorldState::Clean(){
    
//************* Recursos
    resourceManager->CleanResources();
    resourceManager->CleanGameSounds();
    
//************* Variables
    delete waveManager; waveManager = NULL;
    delete powerUpManager; powerUpManager = NULL;
    
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

    while(!vPowers->empty()) 
		delete vPowers->back(), vPowers->pop_back();
        
    while(!vChanges->empty()) 
		delete vChanges->back(), vChanges->pop_back();
    
    
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
    delete paralax; paralax = NULL;
}



//**************** BUCLES PRINCIPALES **************************

void WorldState::Update(const Time& timeElapsed)
{
    if(firstUpdate)
    {
     // MANAGERS
        InputManager::Instance()->Update();
        waveManager->Update(timeElapsed);
        
        powerUpManager->Update(timeElapsed);
        requestStateChange = std::make_pair(States::ID::LoadingState,false);

        
        
     // BULLETS, hacemos las colisiones aquí
        for(int i = 0; i < vBullets->size(); i++)
            vBullets->at(i)->DoColisions(timeElapsed, i);
        
     // Comprobamos si powerUps se tienen que eliminar
        for(int i = 0; i < vPowers->size(); i++){
            if(vPowers->at(i)->UpdateBool(timeElapsed))
                DeletePowerUp(i);
        }
        
    // Comprobamos si alguna mejora temporal debe eliminarse
        for(int i = 0; i < vChanges->size(); i++){
            if(vChanges->at(i)->UpdateBool(timeElapsed))
                DeleteTemporalChange(i);
        }
        
        
    //******************************** UPDATE
        // Player
        player->Update(timeElapsed);
        cam->Update(player);

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
        
        hud->SetCreditText(StatusManager::Instance()->GetValue(Parameters::credit) + " $");
        
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
        
        if(inputManager->IsClickedKeyT())
            requestStateChange = std::make_pair(States::ID::MenuState, true);
        
        
        if(inputManager->IsClickedKeyP())
        {
            releaseMouse=false;
            estado = 0;
            requestStateChange = std::make_pair(States::ID::PauseState, true);
        }

        if(inputManager->IsPressedKeySpace())
            requestStateChange = std::make_pair(States::ID::TowerSelectionState, true);        
        
        if(hud->GetLife() <= 0.f){  // HAS PERDIDO
            estado = 1;
            requestStateChange = std::make_pair(States::ID::PauseState, true);
        }
        
        if(waveManager->state == Wave::Finished && vEnemies->size()==0){  // HAS GANADO
            estado = 2;
            StatusManager::Instance()->IncrementInt(Parameters::countingLevels, 1);
            requestStateChange = std::make_pair(States::ID::PauseState, true);
        }
        
        
        if(requestStateChange.second)
            StateManager::Instance()->SetCurrentState(requestStateChange.first);

	}
	   
}




void WorldState::Render(float interp)
{
    // Eventos de Tiempo Real
    if(StateManager::Instance()->currentState == States::ID::WorldState)
        ProcessRealEvent();
        
    
	window->Clear(sf::Color(255,255,255, 255)); // rgba
	
    paralax->Render(interp);
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
        
        for(int i = 0; i < vPowers->size(); i++)
            vPowers->at(i)->Draw(*window);

        for(int i = 0; i < vBullets->size(); i++)
            vBullets->at(i)->Draw(*window);

        player->Draw(*window);
        cam->Render(player);
    }
    else //Con interpolacion
    {
        for(int i = 0; i < vEntityActive->size(); i++)
            vEntityActive->at(i)->Draw(*window, interp); 

        for(int i = 0; i < vEnemies->size(); i++)
            vEnemies->at(i)->Draw(*window, interp);
        
        for(int i = 0; i < vPowers->size(); i++)
            vPowers->at(i)->Draw(*window,interp);
        
        for(int i = 0; i < vBullets->size(); i++)
            vBullets->at(i)->Draw(*window, interp);

        player->Draw(*window, interp);
        cam->Render(interp,player);
    }
    
    
    
 // HUD
    cam->SetCurrentView(Views::Type::Fixed);
    hud->Draw(*window);
    
    for(int i = 0; i < vChanges->size(); i++)
            vChanges->at(i)->Draw(window); 
    
    if(cam->minimapActive)
        level->renderMinimap();
	
    if(StateManager::Instance()->currentState == States::WorldState){
        cam->SetCurrentView(Views::Type::Fixed);
        window->Display();
    }
    
    
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
	
    if(inputManager->IsPressedMouseLeft() && releaseMouse)
    {
        // Disparar
        if(inputManager->GetMousePosition().GetY() > hud->GetHeight())
            player->Shot(inputManager->GetMousePosition().GetX(), inputManager->GetMousePosition().GetY());
    }
        
        if(inputManager->IsReleasedMouseLeft())
                releaseMouse = true;
	
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


void WorldState::DeleteEnemy(int i)
{ 
    if(vEnemies->at(i)->die)
    {
        float cred;
        if(vEnemies->at(i)->type == 1)
            cred = StatusManager::Instance()->GetEnemyOnePrice();
        else if(vEnemies->at(i)->type == 2)
            cred = StatusManager::Instance()->GetEnemyTwoPrice();
        else 
            cred = StatusManager::Instance()->GetEnemyThreePrice();
        
        StatusManager::Instance()->IncrementInt(Parameters::credit, (int)cred);
    }
    
    delete vEnemies->at(i); vEnemies->at(i)=NULL; 
    vEnemies->erase(vEnemies->begin()+i);
    
    
} 

void WorldState::DeleteBullet(int i)
{ 
    delete vBullets->at(i); vBullets->at(i)=NULL; 
    vBullets->erase(vBullets->begin()+i); 
}

void WorldState::DeletePowerUp(int i)
{ 
    delete vPowers->at(i); vPowers->at(i)=NULL; 
    vPowers->erase(vPowers->begin()+i);    
}

void WorldState::DeleteTemporalChange(int i)
{ 
    vChanges->at(i)->RemoveChange();
    delete vChanges->at(i); vChanges->at(i)=NULL; 
    vChanges->erase(vChanges->begin()+i);    
}