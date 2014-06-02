#include "Slider.h"


Slider::Slider(float x, float y, float width, float height) {
    valor = 0;
    int bordectrl = 3;
    
    barra = new sf::RectangleShape();
    barra->setSize(sf::Vector2f(width, height));
    barra->setFillColor(sf::Color(163, 163, 163, 255));
    barra->setPosition(x, y);
    barra->setOutlineThickness(3);
    barra->setOutlineColor(sf::Color::Black);
    
    control = new sf::RectangleShape();
    control->setSize(sf::Vector2f(width/25, height+height*0.4));
    control->setFillColor(sf::Color::White);
    control->setOutlineThickness(bordectrl);
    control->setOutlineColor(sf::Color::Black);
    control->setPosition(barra->getPosition().x, (barra->getPosition().y) - bordectrl);
}

Slider::Slider(const Slider& orig) {
}

Slider::~Slider() {
    delete barra;       barra = NULL;
    delete control;     control = NULL;
}


void Slider::Draw(RenderWindow& window){
    if(IsPressed()){
        Vector mousePos = CalculateMousePos();
        SetPositionControl(mousePos.GetX());
        valor = CalculateValue();
    }
    
    window.Draw(*barra);
    window.Draw(*control);
}

void Slider::Update(const Time& elapsedTime){
    
}
  

//Valor 
void Slider::SetValue(float value){
    valor = value;  
    
    float pos = barra->getPosition().x + barra->getSize().x*(valor/100);
    
    control->setPosition(pos, control->getPosition().y);
}

float Slider::CalculateValue(){
    float valor = (control->getPosition().x - barra->getPosition().x) / barra->getSize().x * 100;
    
    return valor;
}


//Posición
void Slider::SetPosition(float x, float y){
    barra->setPosition(x, y);
}

void Slider::SetPositionControl(float pos){
    if(pos < barra->getPosition().x)
        pos = barra->getPosition().x;
    else if(pos > (barra->getPosition().x + barra->getSize().x))
        pos = barra->getPosition().x + barra->getSize().x;
    
    control->setPosition(pos, control->getPosition().y);
}

Vector Slider::GetPosition() const{
    return Vector(barra->getPosition().x, barra->getPosition().y);
}

Vector Slider::GetPositionControl() const{
    return Vector(control->getPosition().x, control->getPosition().y);
}


//Ratón
bool Slider::IsHover() const{
    InputManager* im = InputManager::Instance();
    Vector mousePos = im->GetMousePosition();
    
    sf::FloatRect rect = barra->getGlobalBounds();
    
    rect.width += 30.f;
    rect.height += 40.f;
    rect.top -= 20.f;
    rect.left -= 15.f;

    return rect.contains(mousePos.GetX(), mousePos.GetY());
}

bool Slider::IsPressed() const{
    return (IsHover() && InputManager::Instance()->IsPressedMouseLeft());
}

Vector Slider::CalculateMousePos(){
    InputManager* im = InputManager::Instance();
    Vector mousePos = im->GetMousePosition();
    
    return mousePos;
}


