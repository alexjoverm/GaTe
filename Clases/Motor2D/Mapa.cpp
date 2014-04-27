/* 
 * File:   Mapa.cpp
 * Author: jmsm30
 * 
 * Created on 19 de marzo de 2014, 11:00
 */

#include "Mapa.h"
#include "../States/WorldState.h"


// Mapa
        /*level->LoadMap("mapa1.tmx");

        std::vector<Rectangle*> vrec = level->map->getLayerCollitions("Colision suelo");

        tmx::MapLayer metaDatos= level->map->getLayer("Metadatos");

        std::map<std::string,std::string> mapInfo= metaDatos.properties;//guardo un mapa string,string con las propiedades
        std::map<std::string,std::string>::iterator par = mapInfo.find("NumOleadas");//por ej cojo el valor de numOleadas
        std::string aux=par->first;
        std::string auxx=par->second;
        
        std::cout<<aux<<std::endl;
        std::cout<<auxx<<std::endl; */

Mapa::Mapa(sf::RenderWindow* win, std::string fileName)
: map("Maps//")
{
    window = win;
    
    map.Load(fileName);
    
}

Mapa::Mapa(sf::RenderWindow* win, std::string fileName,const Mapa& orig)
: map("Maps//")
{
}

Mapa::~Mapa() {

}
/************ METODOS GET*/

//Devuelve una referencia al mapa completo.
tmx::MapLoader*  Mapa::getMap(){
    
    return &map;
}

// Devuelve una capa concreta del mapa
tmx::MapLayer Mapa::getLayer(std::string layerName){
    
    for( int num = 0; num < map.GetLayers().size(); num++)
    {
        tmx::MapLayer res = tmx::MapLayer(map.GetLayers().at(num));
        
        if(res.name == layerName)
        {
            return res;
        }
    }
     
    
    return tmx::MapLayer(map.GetLayers().at(0));
}

// Metodo que devuelve todos los objetos de una capa concreta
std::vector<tmx::MapObject> Mapa::getLayerObjects(std::string layerName){
    
    tmx::MapLayer res = Mapa::getLayer(layerName);
    
    return res.objects;
}

// Metodo que devuelve todos los bounds de colision de una capa en concreto.
std::vector<Rectangle*> Mapa::getLayerCollitions(std::string layerName){
    
    std::vector<Rectangle*> vres;
    tmx::MapLayer aux = getLayer(layerName);
    
    for( int num = 0; num < aux.objects.size(); num++)
    {
        tmx::MapObject res = tmx::MapObject(aux.objects.at(num));
        vres.push_back(new Rectangle(res.GetAABB()));
    }
    return vres;
}


/************** METODOS INIT (INICIALIZACION)*/

void Mapa::init(){

    
    
    
    tmx::MapLayer layer = getLayer("Camino");
    
    std::vector<sf::Vector2f> aux = tmx::MapObject(layer.objects.at(0)).PolyPoints();

    for (int i = 2 ; i < tmx::MapObject(layer.objects.at(0)).PolyPoints().size()-2 ; i++ ){
        WorldState::Instance()->AddTrace(new Vector(
                        sf::Vector2f(tmx::MapObject(layer.objects.at(0)).PolyPoints().at(i)).x,
                        sf::Vector2f(tmx::MapObject(layer.objects.at(0)).PolyPoints().at(i)).y
                ) 
        );
    }
    
}


/*************** METODOS DRAW*/
// Metodo alternativo para pintar todo el mapa, se le pasa la direccion de memoria del sf::RenderWindow
void Mapa::render(){
    
    WorldState::Instance()->GetCamera()->SetCurrentView(Views::Type::Standard);
    window->draw(map);

}

// Metodo para renderizar el minimapa
void Mapa::renderMiniMap(){ 

    WorldState::Instance()->GetCamera()->SetCurrentView(Views::Type::Fixed);
        window->draw(*WorldState::Instance()->GetCamera()->GetMiniback());
    WorldState::Instance()->GetCamera()->SetCurrentView(Views::Type::Minimap);    // Mini-Mapa
        window->draw(map);       

    WorldState::Instance()->GetCamera()->SetCurrentView(Views::Type::Standard);      // Zelda y Controles (elementos de ultima capa
    
}

