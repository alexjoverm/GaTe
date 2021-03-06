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
    
    mapSize = new Vector();
    
    posNext = new Vector();
    posPrev = new Vector();
    posRender = new Vector();
    posRenderPrev = new Vector();
    
    pos = new Vector();
    moved = new Vector();
}

Camera::Camera(const Camera& orig) {
}

Camera::~Camera() {
    delete miniback; miniback=NULL;
    delete mapSize; mapSize=NULL;
    
    delete posNext; posNext = NULL;
    delete posPrev; posPrev = NULL;
    delete posRender; posRender = NULL;
    delete posRenderPrev; posRenderPrev = NULL;
    
    delete pos; pos = NULL;
    delete moved; moved = NULL;
    
    delete topRect; topRect=NULL;
    delete bottomRect; bottomRect=NULL;
    delete rightRect; rightRect=NULL;
    delete leftRect; leftRect=NULL;
}


void Camera::Init(Player* player){
    
        mapSize = WorldState::Instance()->level->getMapSize();
        
        float offset = 15.f;
        
        // Rectangulos de colision borde de mapa
        topRect = new Rectangle(0, offset,mapSize->GetX(),0.01);
        bottomRect = new Rectangle(0,mapSize->GetY()-offset,mapSize->GetX(),0.01);
        leftRect = new Rectangle(offset,0,0.01,mapSize->GetY());
        rightRect = new Rectangle(mapSize->GetX()-offset,0,0.01,mapSize->GetY());
    
        fixed = window->getView();  // Esta nunca cambia
        standard = fixed;          // 'standard' sera la que se muestre siempre
        
    
        //** MINI-MAPA (seguirá a la vista 'standard')  *************
    
        unsigned int sizex = 375;
        unsigned int sizey = 280;
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
        miniback->setSize( sf::Vector2f( static_cast<float>(sizex)+10,static_cast<float>(window->getSize().y*sizey/window->getSize().x)+10 ) );
        miniback->setPosition( minimap.getViewport().left*window->getSize().x-5, minimap.getViewport().top*window->getSize().y-5 );
        miniback->setFillColor(sf::Color(255,0,0,100));
    
        
        
        
        Vector posPlayer = player->GetRectangleColisionAbsolute().GetTopLeft();
        
        // Posicion controlada de la view standard
        float posIniXCam = posPlayer.GetX();
        float posIniYCam = posPlayer.GetY();
        
        // Reajuste en X
        if( ((posPlayer.GetX() + standard.getSize().x / 2) - mapSize->GetX()) > 0 )
            posIniXCam -=  ( (posPlayer.GetX() + standard.getSize().x / 2) - mapSize->GetX() ) ;
        else if( (posPlayer.GetX() - standard.getSize().x / 2) < 0 )
            posIniXCam += std::abs(posPlayer.GetX() - standard.getSize().x / 2) + player->GetRectangleColisionAbsolute().GetWidth()/2 ;
        
        // Reajuste en Y
        if( (posPlayer.GetY() - standard.getSize().y / 2) < 0 )
            posIniYCam +=  std::abs( posPlayer.GetY() - standard.getSize().y / 2 ) ;
        else if( (posPlayer.GetY() + standard.getSize().y / 2) > mapSize->GetY() )
            posIniYCam -= std::abs((posPlayer.GetY() + standard.getSize().y / 2) - mapSize->GetY() ) ;
        
        
        posPrev->Set(player->GetPreviousPosition().GetX(), player->GetPreviousPosition().GetY());
        *posNext = *posPrev;
        *posRender = *posPrev;
        *posRenderPrev = *posPrev;
        
        standard.setCenter(posIniXCam , posIniYCam);
        
        // Posicion controlada de la view standard
        posIniXCam = posPlayer.GetX();
        posIniYCam = posPlayer.GetY();
        
        // Reajuste en X
        if( ((posPlayer.GetX() + minimap.getSize().x / 2) - mapSize->GetX()) > 0 )
            posIniXCam -=  ( (posPlayer.GetX() + minimap.getSize().x / 2) - mapSize->GetX() ) ;
        else if( (posPlayer.GetX() - minimap.getSize().x / 2) < 0 )
            posIniXCam += std::abs(posPlayer.GetX() - minimap.getSize().x / 2) + player->GetRectangleColisionAbsolute().GetWidth()/2 ;
        
        // Reajuste en Y
        if( (posPlayer.GetY() - minimap.getSize().y / 2) < 0 )
            posIniYCam +=  std::abs( posPlayer.GetY() - minimap.getSize().y / 2 ) ;
        else if( (posPlayer.GetY() + minimap.getSize().y / 2) > mapSize->GetY() )
            posIniYCam -= std::abs((posPlayer.GetY() + minimap.getSize().y / 2) - mapSize->GetY() ) ;
        
        minimap.setCenter(posIniXCam , posIniYCam);
}       



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

void Camera::Move(float velX, float velY, float posCharX, float posCharY, Player* pl){
    
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
         if( right && posCharX >= (standard.getCenter().x-pl->GetRectangleColisionAbsolute().GetWidth()) 
          || left && posCharX <= standard.getCenter().x-pl->GetRectangleColisionAbsolute().GetWidth()/2)
                centerx = 1;
     }
     
     // Se comprueba el eje Y
     if(posCharY!=-1){
         if( bottom && posCharY > standard.getCenter().y 
          || top && posCharY < standard.getCenter().y)
                centery = 1;
     }
    //Variable que indica si se mueve en x
    moved->Set(rightx*centerx,righty*centery);
    standard.move(velX*rightx*centerx,velY*righty*centery);
    
    // Actualizamos la vista de la ventana con la resultante ya movida
    window->setView(standard);
    
    MoveMinimap(velX , velY , posCharX , posCharY, pl);
    
}

void Camera::MoveMinimap(float x, float y, float charx, float chary, Player* pl){

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


void Camera::Update(Player* pl)
{
    *posPrev = pl->GetPreviousPosition();
    *posNext = pl->GetPosition();
}

void Camera::Render(Player* pl)
{
    posRender->SetX(posPrev->GetX() );
    posRender->SetY(posPrev->GetY() );
    
    pos->Set(posRender->GetX() - posRenderPrev->GetX() , posRender->GetY() - posRenderPrev->GetY());
    
    Move( pos->GetX(),  pos->GetY(), pl->GetRenderPosition().GetX() , pl->GetRenderPosition().GetY(), pl ) ;
    
    *posRenderPrev = *posRender;
}

void Camera::Render(float interp, Player* pl)
{
    posRender->SetX(posPrev->GetX() + ((posNext->GetX() - posPrev->GetX()) * interp));
    posRender->SetY(posPrev->GetY() + ((posNext->GetY() - posPrev->GetY()) * interp));
    
    pos->Set(posRender->GetX() - posRenderPrev->GetX() , posRender->GetY() - posRenderPrev->GetY());
    
    Move( pos->GetX(),  pos->GetY(), pl->GetRenderPosition().GetX() , pl->GetRenderPosition().GetY(), pl ) ;
    
    *posRenderPrev = *posRender;
}

