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
    
    topRect = sf::FloatRect(0,0,map.GetMapSize().x,0.01);
    bottomRect = sf::FloatRect(0,map.GetMapSize().y,map.GetMapSize().x,0.01);
    leftRect = sf::FloatRect(0,0,0.01,map.GetMapSize().y);
    rightRect = sf::FloatRect(map.GetMapSize().x,0,0.01,map.GetMapSize().y);//*/
    
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


/************ METODOS MOVE**/

void Mapa::move(float x, float y, float charx, float chary){

    // Vista con la que estamos trabajando    
    sf::View aux = window->getView();
    
    // Variables de direccion de movimiento.
    bool top = 0 , bottom = 0, left = 0, right = 0;
    
    // Variables para ver si es correcto el movimeinto en dicho eje
    bool rightx = 1 , righty = 1;
         
    
    // Sacamos direccion de X
    if(x > 0)
        right = 1;
    else
        left = 1;
    
    // Scacamos direccion de Y
    if(y > 0)
        bottom = 1;
    else
        top = 1;
    
    sf::FloatRect visibleScreen = sf::FloatRect(aux.getCenter().x-(aux.getSize().x/2.0),aux.getCenter().y-(aux.getSize().y/2.0),aux.getSize().x,aux.getSize().y);
    
    // Comprobamos colisiones en el eje X
    if( ( left && leftRect.intersects(visibleScreen) ) || ( right && rightRect.intersects(visibleScreen) )  ){
        rightx = 0;
    }
    
    // Comprobamos colisiones en el eje Y
    if( ( top && topRect.intersects(visibleScreen) ) || (bottom && bottomRect.intersects(visibleScreen) )  ){
        righty = 0;
    }
    
    
    // Comprobamso si se ha pasado la pos del pj y por defecto se movera si esta cerca del eje del viewport.
     bool  centerx = 0, centery = 0;
     
     // Se comprueba el eje X
     if(charx!=-1){
         if( right && charx > aux.getCenter().x 
          || left && charx < aux.getCenter().x)
                centerx = 1;
     }
     
     // Se comprueba el eje Y
     if(chary!=-1){
         if( bottom && chary > aux.getCenter().y 
          || top && chary < aux.getCenter().y)
                centery = 1;
     }
      
    aux.move(x*rightx*centerx,y*righty*centery);
    
    // Actualizamos la vista de la ventana con la resultante ya movida
    window->setView(aux);
    
    moveMiniMap(x , y , charx , chary);
    
    // Movimiento para el miniback (fondo del minimapa) que se quede en su sitio
    miniback.move(x*rightx*centerx,y*righty*centery);
}

void Mapa::move(sf::Vector2f vf, float charx, float chary){

    move(vf.x,vf.y,charx,chary);
    
}

void Mapa::moveMiniMap(float x, float y, float charx, float chary){

    // Variables de direccion de movimiento.
    bool top = 0 , bottom = 0, left = 0, right = 0;
    
    // Variables para ver si es correcto el movimeinto en dicho eje
    bool rightx = 1 , righty = 1;
         
    
    // Sacamos direccion de X
    if(x > 0)
        right = 1;
    else
        left = 1;
    
    // Scacamos direccion de Y
    if(y > 0)
        bottom = 1;
    else
        top = 1;
    
    sf::FloatRect visibleScreen = sf::FloatRect(minimap.getCenter().x-(minimap.getSize().x/2.0),minimap.getCenter().y-(minimap.getSize().y/2.0),minimap.getSize().x,minimap.getSize().y);
    
    // Comprobamos colisiones en el eje X
    if( ( left && leftRect.intersects(visibleScreen) ) || ( right && rightRect.intersects(visibleScreen) )  ){
        rightx = 0;
    }
    
    // Comprobamos colisiones en el eje Y
    if( ( top && topRect.intersects(visibleScreen) ) || (bottom && bottomRect.intersects(visibleScreen) )  ){
        righty = 0;
    }
    
    // Comprobamso si se ha pasado la pos del pj y por defecto se movera si esta cerca del eje del viewport.
     bool  centerx = 0, centery = 0;
     
     // Se comprueba el eje X
     if(charx!=-1){
         if( right && charx > minimap.getCenter().x-50 
          || left && charx < minimap.getCenter().x+50)
                centerx = 1;
     }
     
     // Se comprueba el eje Y
     if(chary!=-1){
         if( bottom && chary > minimap.getCenter().y-50 
          || top && chary < minimap.getCenter().y+50)
                centery = 1;
     }
      
    minimap.move(x*rightx*centerx,y*righty*centery);

}

/************** METODOS INIT (INICIALIZACION)*/

void Mapa::init(){

    initMiniMap();
    
}

void Mapa::initMiniMap(){
	
	fixed = window->getView();  // Esta nunca cambia
	standard = fixed;          // 'standard' sera la que se muestre siempre
    
    standard.move(100.f, 100.f);
 //** MINI-MAPA (seguirá a la vista 'standard')  *************
    
	unsigned int sizex = map.GetMapSize().x/6;
        unsigned int sizey = map.GetMapSize().y/3;
	minimap = sf::View(sf::FloatRect(standard.getCenter().x,standard.getCenter().y,static_cast<float>(sizex),static_cast<float>(window->getSize().y*sizey/window->getSize().x)));
    
    //Calculamos proporcion entre MiniMap y Pantalla. Asi podremos definir el tamaño con porcentajes
    sf::Vector2f proporcion(static_cast<float>(minimap.getSize().x)/window->getSize().x , static_cast<float>(minimap.getSize().y)/window->getSize().y);
    
    //El "Viewport" funciona con porcentajes representado con floats (0.0f = inicio , 1.0f = fin pantalla)
    minimap.setViewport(sf::FloatRect(
        1.f- proporcion.x -0.01f,     //InicioX
        1.f- proporcion.y -0.01f,     //InicioY
        proporcion.x,                 //Ancho
        proporcion.y                  //Alto
    )); //Lo situamos Abajo-Derecha
    minimap.zoom(6.0f); //Zoom funciona a la inversa
    
    //Dibujamos un rectangulo alrededor del minimapa
        miniback.setSize( sf::Vector2f( static_cast<float>(sizex)+6,static_cast<float>(window->getSize().y*sizey/window->getSize().x+6) ) );
        miniback.setPosition( minimap.getViewport().left*window->getSize().x-3, minimap.getViewport().top*window->getSize().y-3 );
        miniback.setFillColor(sf::Color(255,255,255));
        
}


/*************** METODOS UPDATE*/
// Metodo update
void Mapa::update(Player* pl, float interpolation){
    float x, y;
    x = pl->GetPreviousSpeed().GetX() + ((pl->GetSpeed().GetX() - pl->GetPreviousSpeed().GetX()) * interpolation);
    y = pl->GetPreviousSpeed().GetY() + ((pl->GetSpeed().GetY() - pl->GetPreviousSpeed().GetY()) * interpolation);
    move(x,y,pl->GetRenderPosition().GetX(),pl->GetRenderPosition().GetY());
}

/*************** METODOS DRAW*/
// Metodo alternativo para pintar todo el mapa, se le pasa la direccion de memoria del sf::RenderWindow
void Mapa::render(bool miniMapEnable){
    
    window->draw(map);
    
    if(miniMapEnable)
        renderMiniMap();
}

// Metodo para renderizar el minimapa
void Mapa::renderMiniMap(){ 
    
    
    //fixed = window->getView();
    window->setView(fixed);
       window->draw(miniback);
    
    window->setView(minimap);    // Mini-Mapa
        window->draw(map);       

    window->setView(standard); 
    
}

