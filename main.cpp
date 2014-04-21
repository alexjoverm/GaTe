/**
* Proyecto de Colisiones, Movimientos y Físicas
*
*@todo    Se debe realizar casi todo todavía
*@version Versión 0.1
*@author  Alejandro Jover Morales
*@date    11-03-2014
*/
 
#include "Clases/Motor2D/World.h"

int main(int, char const**)
{
    World* world = World::Instance();
	
	// Crear nivel
	world->AddLevelTexture("Recursos/Foe.png");
	
	// Cargar recursos y inicializar
	world->Init();
	
	// Añadir un EntPassive y setear coordenadas
	
	Enemy* enemy = new Enemy(ResourceManager::Instance()->GetTexture("texLevel0"), Vector(530.f , 300.f), Vector(0.f, 0.f), Vector(500.f, 500.f));
	enemy->SetSpeed(220.f, 0.f);
	
	world->AddColisionableEntity(enemy);// Añadimos al array de colisionables
	world->AddActiveEntity(enemy);		// Añadimos al array de elementos activos, para que se pinte
	
	
	// Arrancamos el Juego
    world->Run();
}
