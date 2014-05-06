/* 
 * File:   Mapa.cpp
 * Author: jmsm30
 * 
 * Created on 19 de marzo de 2014, 11:00
 */

#include "Mapa.h"
#include "../States/WorldState.h"

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
tmx::MapLoader*  Mapa::GetMap(){
    
    return &map;
}

// Devuelve una capa concreta del mapa
tmx::MapLayer Mapa::GetLayer(std::string layerName){
    
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
std::vector<tmx::MapObject> Mapa::GetLayerObjects(std::string layerName){
    
    tmx::MapLayer res = Mapa::GetLayer(layerName);
    
    return res.objects;
}

// Metodo que devuelve todos los bounds de colision de una capa en concreto.
std::vector<Rectangle*> Mapa::GetLayerCollitions(std::string layerName){
    
    std::vector<Rectangle*> vres;
    tmx::MapLayer aux = GetLayer(layerName);
    
    for( int num = 0; num < aux.objects.size(); num++)
    {
        tmx::MapObject res = tmx::MapObject(aux.objects.at(num));
        vres.push_back(new Rectangle(res.GetAABB()));
    }
    return vres;
}

// Metodos de adquisicion de datos, uno para los metadatos y otro para los datos directos de una capa.

std::string Mapa::GetMetadata(std::string dataName){
    
    tmx::MapLayer data= GetLayer("Metadatos");

    std::map<std::string,std::string> dataInfo = data.properties;//guardo un mapa string,string con las propiedades
    std::map<std::string,std::string>::iterator par = dataInfo.find(dataName);//por ej cojo el valor de numOleadas

    if(par != dataInfo.end())
        return par->second;
    else
        return "";
    
}

std::string Mapa::GetLayerData(std::string layerName , std::string dataName){

    tmx::MapLayer data= GetLayer(layerName);

    std::map<std::string,std::string> layerInfo = data.properties;//guardo un mapa string,string con las propiedades
    std::map<std::string,std::string>::iterator par = layerInfo.find(dataName);//por ej cojo el valor de numOleadas

    if( par != layerInfo.end() )
        return par->second;
    else
        return "";
    
}


std::string Mapa::GetObjectData(std::string layerName ,int objectNumber , std::string dataName){
    
    tmx::MapLayer data= GetLayer(layerName);
    
    if( objectNumber < data.objects.size() ){

        return tmx::MapObject(data.objects[objectNumber]).GetPropertyString(dataName);
    }
    
    return "";
}




/************** METODOS INIT (INICIALIZACION)*/

void Mapa::Init(){
    
    LoadPath();
    
}


/*************** METODOS DRAW*/
// Metodo alternativo para pintar todo el mapa, se le pasa la direccion de memoria del sf::RenderWindow
void Mapa::Render(){
    
    WorldState::Instance()->GetCamera()->SetCurrentView(Views::Type::Standard);
    window->draw(map);
    

}

// Metodo para renderizar el minimapa
void Mapa::RenderMiniMap(){
    
    Rectangle aux = WorldState::Instance()->player->GetRectangleColisionAbsolute();
    Vector vecAbs = aux.GetTopLeft();
    sf::Vector2i vecRel = RenderWindow::Instance()->renderWindow->mapCoordsToPixel(sf::Vector2f(vecAbs.GetX(), vecAbs.GetY()) 
            , WorldState::Instance()->GetCamera()->standard);
    
    aux.SetX(vecRel.x - 10.f);
    aux.SetY(vecRel.y - 25.f);

    if(!aux.Intersects( Rectangle( WorldState::Instance()->GetCamera()->GetMiniback()->getGlobalBounds() ) ) ){
        
        WorldState::Instance()->GetCamera()->SetCurrentView(Views::Type::Fixed);
            window->draw(*WorldState::Instance()->GetCamera()->GetMiniback());
        WorldState::Instance()->GetCamera()->SetCurrentView(Views::Type::Minimap);    // Mini-Mapa
            window->draw(map);     


        for(int i = 0; i < WorldState::Instance()->vTowers->size(); i++)
            window->draw(*WorldState::Instance()->vTowers->at(i)->GetSprite()->GetSprite());

        for(int i = 0; i < WorldState::Instance()->vEnemies->size(); i++)
            window->draw(*WorldState::Instance()->vEnemies->at(i)->GetSprite()->GetSprite());


        window->draw(*WorldState::Instance()->player->GetSprite()->GetSprite());


        WorldState::Instance()->GetCamera()->SetCurrentView(Views::Type::Standard);      // Zelda y Controles (elementos de ultima capa
    }
}


void Mapa::LoadPath(){

    tmx::MapLayer layer = GetLayer("Camino");
    
    std::vector<sf::Vector2f> aux = tmx::MapObject(layer.objects.at(0)).PolyPoints();

    for (int i = 2 ; i < tmx::MapObject(layer.objects.at(0)).PolyPoints().size()-2 ; i++ ){
        WorldState::Instance()->AddTrace(new Vector(
                        sf::Vector2f(tmx::MapObject(layer.objects.at(0)).PolyPoints().at(i)).x,
                        sf::Vector2f(tmx::MapObject(layer.objects.at(0)).PolyPoints().at(i)).y
                ) 
        );
    }
    
}

