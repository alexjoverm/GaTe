/* 
 * File:   Camera.cpp
 * Author: jmsm30
 * 
 * Created on 24 de abril de 2014, 20:43
 */

#include "Camera.h"
#include "Level.h"
#include "../States/WorldState.h"


Camera::Camera(sf::RenderWindow* win) {
    
    window = win;
    miniback = new  sf::RectangleShape();
    prevPosPlayer = new Vector();
    
    mapSize = new Vector();
}

Camera::Camera(const Camera& orig) {
}

Camera::~Camera() {
    delete miniback; miniback=NULL;
    delete prevPosPlayer; prevPosPlayer=NULL;
    
    delete mapSize; mapSize=NULL;
    
    delete topRect; topRect=NULL;
    delete bottomRect; bottomRect=NULL;
    delete rightRect; rightRect=NULL;
    delete leftRect; leftRect=NULL;
}


void Camera::Init(Player* player){
    
        mapSize = WorldState::Instance()->level->getMapSize();
        
        // Rectangulos de colision borde de mapa
        topRect = new Rectangle(0,0,mapSize->GetX(),0.01);
        bottomRect = new Rectangle(0,mapSize->GetY(),mapSize->GetX(),0.01);
        leftRect = new Rectangle(0,0,0.01,mapSize->GetY());
        rightRect = new Rectangle(mapSize->GetX(),0,0.01,mapSize->GetY());
    
        fixed = window->getView();  // Esta nunca cambia
        standard = fixed;          // 'standard' sera la que se muestre siempre
    
        //** MINI-MAPA (seguirá a la vista 'standard')  *************
    
        unsigned int sizex = mapSize->GetX()/6;
        unsigned int sizey = mapSize->GetY()/3;
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
        minimap.zoom(5.0f); //Zoom funciona a la inversa
    
        //Dibujamos un rectangulo alrededor del minimapa
        miniback->setSize( sf::Vector2f( static_cast<float>(sizex)+6,static_cast<float>(window->getSize().y*sizey/window->getSize().x)-15 ) );
        miniback->setPosition( minimap.getViewport().left*window->getSize().x-3, minimap.getViewport().top*window->getSize().y+15 );
        miniback->setFillColor(sf::Color(255,0,0,100));
    
        // Asignamos el player
        pl = player;
        
        Vector posPlayer = pl->GetRectangleColisionAbsolute().GetTopLeft();
        
        // Posicion controlada de la view standard
        float posIniXCam = posPlayer.GetX();
        float posIniYCam = posPlayer.GetY();
        
        // Reajuste en X
        if( ((posPlayer.GetX() + standard.getSize().x / 2) - mapSize->GetX()) > 0 )
            posIniXCam -=  ( (posPlayer.GetX() + standard.getSize().x / 2) - mapSize->GetX() ) ;
        else if( (posPlayer.GetX() - standard.getSize().x / 2) < 0 )
            posIniXCam += std::abs(posPlayer.GetX() - standard.getSize().x / 2)+pl->GetRectangleColisionAbsolute().GetWidth()/2 ;
        
        // Reajuste en Y
        if( (posPlayer.GetY() - standard.getSize().y / 2) < 0 )
            posIniYCam +=  std::abs( posPlayer.GetY() - standard.getSize().y / 2 ) ;
        else if( (posPlayer.GetY() + standard.getSize().y / 2) > mapSize->GetY() )
            posIniYCam -= std::abs((posPlayer.GetY() + standard.getSize().y / 2) - mapSize->GetY() ) ;
        
        standard.setCenter(posIniXCam , posIniYCam);
        
        
        // Esto es para el eje ARRIBA-DERECHA
        posIniXCam -= posIniXCam*proporcion.x;
        posIniYCam += posIniYCam*proporcion.y;
        
        minimap.setCenter(posIniXCam , posIniYCam);
        prevPosPlayer->Set(posPlayer);
        
}

/*void Camera::InitMove(){

    
    
}*/



void Camera::SetCurrentView(Views::Type view){
    currentView = view;
    window->setView( *this->GetCurrentView() );
}

sf::View* Camera::GetCurrentView(){
    
    switch(currentView){
    
        case Views::Type::Standard : 
            return &standard;
            break;
            
        case Views::Type::Fixed : 
            return &fixed;
            break;
            
        case Views::Type::Minimap : 
            return &minimap;
            break;   
    }
    
}

sf::View* Camera::GetView(Views::Type view){

    switch(view){
    
        case Views::Type::Standard : 
            return &standard;
            break;
            
        case Views::Type::Fixed : 
            return &fixed;
            break;
            
        case Views::Type::Minimap : 
            return &minimap;
            break;   
    }
    
}




/************ METODOS MOVE**/

void Camera::Move(float numberOfSeconds){
    
    this->SetCurrentView(Views::Type::Standard);
    standard.setCenter(pl->GetRenderPosition().GetX(),pl->GetRenderPosition().GetY());  
    MoveMinimap(pl->GetSpeed().GetX() * numberOfSeconds , pl->GetSpeed().GetY() * numberOfSeconds , pl->GetRenderPosition().GetX() , pl->GetRenderPosition().GetY());
}

void Camera::Move(Vector velChar, Vector posChar){

    Move(velChar.GetX(),velChar.GetY(),posChar.GetX(),posChar.GetY());
    
}

void Camera::Move(float velX, float velY, float posCharX, float posCharY){
    
    // Variables de direccion de movimiento.
    bool top = 0 , bottom = 0, left = 0, right = 0;
    
    // Variables para ver si es correcto el movimeinto en dicho eje
    bool rightx = 1 , righty = 1;
         
    
    // Sacamos direccion de X
    if(velX > 0)
        right = 1;
    else
        left = 1;
    
    // Scacamos direccion de Y
    if(velY > 0)
        bottom = 1;
    else
        top = 1;
    
    Rectangle visibleScreen = Rectangle(standard.getCenter().x-(standard.getSize().x/2.0),standard.getCenter().y-(standard.getSize().y/2.0),standard.getSize().x,standard.getSize().y);
    
    // Comprobamos colisiones en el eje X
    if( ( left && leftRect->Intersects(visibleScreen) ) || ( right && rightRect->Intersects(visibleScreen) )  ){
        rightx = 0;
    }
    
    // Comprobamos colisiones en el eje Y
    if( ( top && topRect->Intersects(visibleScreen) ) || (bottom && bottomRect->Intersects(visibleScreen) )  ){
        righty = 0;
    }
    
    
    // Comprobamso si se ha pasado la pos del pj y por defecto se movera si esta cerca del eje del viewport.
     bool  centerx = 0, centery = 0;
     
     // Se comprueba el eje X
     if(posCharX!=-1){
         if( right && posCharX >= standard.getCenter().x 
          || left && posCharX <= standard.getCenter().x)
                centerx = 1;
     }
     
     // Se comprueba el eje Y
     if(posCharY!=-1){
         if( bottom && posCharY > standard.getCenter().y-15 
          || top && posCharY < standard.getCenter().y+15)
                centery = 1;
     }
      
    standard.move(velX*rightx*centerx,velY*righty*centery);
    
    // Actualizamos la vista de la ventana con la resultante ya movida
    window->setView(standard);
    
    MoveMinimap(velX , velY , posCharX , posCharY);
    
}

void Camera::MoveMinimap(){

    this->SetCurrentView(Views::Type::Minimap);
    minimap.setCenter(pl->GetRenderPosition().GetX(),pl->GetRenderPosition().GetY());
    
}

void Camera::MoveMinimap(float x, float y, float charx, float chary){

    this->SetCurrentView(Views::Type::Minimap);
    
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
    
    Rectangle visibleScreen = Rectangle(minimap.getCenter().x-(minimap.getSize().x/2.0),minimap.getCenter().y-(minimap.getSize().y/2.0),minimap.getSize().x,minimap.getSize().y);
    
    // Comprobamos colisiones en el eje X
    if( ( left && leftRect->Intersects(visibleScreen) ) || ( right && rightRect->Intersects(visibleScreen) )  ){
        rightx = 0;
    }
    
    // Comprobamos colisiones en el eje Y
    if( ( top && topRect->Intersects(visibleScreen) ) || (bottom && bottomRect->Intersects(visibleScreen) )  ){
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


void Camera::Update(){

    //Move(numberOfSeconds);
    float vX = pl->GetRenderPosition().GetX() - prevPosPlayer->GetX() ;
    float vY =  pl->GetRenderPosition().GetY() - prevPosPlayer->GetY() ;
        
    Move( vX,  vY, pl->GetRenderPosition().GetX() , pl->GetRenderPosition().GetY() ) ;
    //Move( pl->GetSpeed().GetX() * numberOfSeconds , pl->GetSpeed().GetY() * numberOfSeconds , pl->GetPosition().GetX() , pl->GetPosition().GetY() );
    
    prevPosPlayer->Set(pl->GetRenderPosition());
    
}