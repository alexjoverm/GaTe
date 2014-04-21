/* 
 * File:   Colisionable.cpp
 * Author: linuxero
 * 
 * Created on March 11, 2014, 9:49 AM
 */

#include "Colisionable.h"
#include "../Entities/Entity.h"
#include "../Otros/StringUtils.h"
#include <iostream>


Colisionable::Colisionable(EntActive* ent) {
	rectColision = new std::vector<Rectangle*>();
	entity = ent;
}

Colisionable::Colisionable(const Colisionable& orig) {
}

Colisionable::~Colisionable() {
		
	while(!rectColision->empty()) 
		delete rectColision->back(), rectColision->pop_back();
	
	rectColision = NULL;
}


// *******************************  RECTÁNGULOS  **********************************
// ********************************************************************************

// Devuelven la posicion en la que se ha insertado
int Colisionable::CreateRectangle(float x, float y, float width, float height){
	rectColision->push_back(new Rectangle(x,y,width,height));
	return rectColision->size()-1;
}


Rectangle Colisionable::GetAbsoluteRectangle(const EntActive& ent, const Rectangle& recRelative)
{
	Rectangle rec = ent.GetSprite()->getGlobalBounds();
	
	float xRel = recRelative.GetTopLeft().GetX();
	float yRel = recRelative.GetTopLeft().GetY();
	
// Si la orientación del Sprite está invertida, Transformamos las coordenadas
	if(ent.GetSprite()->GetOrientation()==Transform::Orientation::Left){
		xRel = 1.f - xRel;
		yRel = 1.f - yRel;
	}
	
 // Creamos las coordenadas ABSOLUTAS, desde las Relativas
	float x = rec.GetTopLeft().GetX()  +  rec.GetTopLeft().GetX() * xRel;
	float y = rec.GetTopLeft().GetY()  +  rec.GetTopLeft().GetY() * yRel;
	float w = rec.GetTopLeft().GetX()  +  rec.GetWidth() * recRelative.GetWidth();
	float h = rec.GetTopLeft().GetY()  +  rec.GetHeight() * recRelative.GetHeight();

	rec.Set(x,y,w,h);
	return rec;
}

std::vector<Rectangle> Colisionable::GetAbsoluteRectangles(const EntActive& ent){
	std::vector<Rectangle> vec;
	
	for(int i=0; i < rectColision->size() ; i++)
		vec.push_back(*rectColision->at(i));
	
	return vec;
}


Rectangle Colisionable::CalculateNextRect(const Time& elapsedTime, float factor){
	
	Rectangle auxRect = entity->GetSprite()->getGlobalBounds();
	
	auxRect.SetX(auxRect.GetTopLeft().GetX() + entity->GetSpeed().GetX() * elapsedTime.AsSeconds() * factor);
	auxRect.SetY(auxRect.GetTopLeft().GetY() + entity->GetSpeed().GetY() * elapsedTime.AsSeconds() * factor);
	
	return auxRect;
}



// ********************* COLISIONES capa 2 (BAJO NIVEL)  **************************
// ********************************************************************************

bool Colisionable::CheckColision(const Colisionable& ent){
	return entity->GetSprite()->getGlobalBounds().Intersects(ent.entity->GetSprite()->getGlobalBounds());	
}

bool Colisionable::CheckColision(const Rectangle& rec){
	return entity->GetSprite()->getGlobalBounds().Intersects(rec);
}

bool Colisionable::CheckColision(const Colisionable& ent, const Time& elapsedTime){
	return CalculateNextRect(elapsedTime, nextRectFactor).Intersects(ent.entity->GetSprite()->getGlobalBounds());	
}

bool Colisionable::CheckColision(const Rectangle& rec, const Time& elapsedTime){
	return CalculateNextRect(elapsedTime, nextRectFactor).Intersects(rec);
}



// Devuelve un vector de Vectores Índice (indFrom, indTo)
int Colisionable::CheckDeepColision(const Colisionable& ent){
	/*
	for(int i=0; i < this->rectColision->size(); i++)
		for(int j=0; j < ent.rectColision->size(); j++)
			if(this->rectColision->at(i)->Intersects(*ent.rectColision->at(j)))
				return i;
		
	return -1;*/
}


//*** IMPLEMENTADO

Colision::Type Colisionable::TypeOfColision(const Rectangle& rec, const Time& elapsedTime){
	Rectangle entRec = CalculateNextRect(elapsedTime, nextRectFactor);
	std::vector<Colision::Type> colisions;
	
	//***** Comprobamos en los ejes en los que colisiona
	if(rec.GetTopLeft().GetX() >= entRec.GetTopLeft().GetX() &&  rec.GetTopLeft().GetX() <= entRec.GetTopRight().GetX())
		colisions.push_back(Colision::Type::LEFT);
	if(rec.GetTopRight().GetX() >= entRec.GetTopLeft().GetX() &&  rec.GetTopRight().GetX() <= entRec.GetTopRight().GetX())
		colisions.push_back(Colision::Type::RIGHT);
	if(rec.GetTopLeft().GetY() <= entRec.GetBottomLeft().GetY() &&  rec.GetTopLeft().GetY() >= entRec.GetTopLeft().GetY())  // Suelo
		colisions.push_back(Colision::Type::BOTTOM);
	if(rec.GetBottomLeft().GetY() <= entRec.GetBottomLeft().GetY() &&  rec.GetBottomLeft().GetY() >= entRec.GetTopLeft().GetY())  // Techo
		colisions.push_back(Colision::Type::TOP);
        
    
    
	//***** COLISION 1 EJE: ya lo tenemos
	if(colisions.size() == 1)
		return colisions.at(0);
	
	//***** COLISION 3 EJES: si hay 2 verticales y 1 horizontal, será el horizontal, y viceversa.
	else if(colisions.size() == 3)
	{
		if(colisions.at(0) == Colision::Type::LEFT && colisions.at(1) == Colision::Type::BOTTOM && colisions.at(2) == Colision::Type::TOP)
			return Colision::Type::LEFT;
		else if(colisions.at(0) == Colision::Type::RIGHT && colisions.at(1) == Colision::Type::BOTTOM && colisions.at(2) == Colision::Type::TOP)
			return Colision::Type::RIGHT;
		else if(colisions.at(0) == Colision::Type::LEFT && colisions.at(1) == Colision::Type::RIGHT && colisions.at(2) == Colision::Type::TOP)
			return Colision::Type::TOP;
		else if(colisions.at(0) == Colision::Type::LEFT && colisions.at(1) == Colision::Type::RIGHT && colisions.at(2) == Colision::Type::BOTTOM)
			return Colision::Type::BOTTOM;
	}
	
	//***** COLISION 2 EJES: comprobación estadística respecto a la posición anterior
	else
	{
		Rectangle rectPrev = entity->GetSprite()->getGlobalBounds();
		Vector posAux = Vector();
		
		// Si es la esquina TOP-LEFT, comprobamos con la BOTTOM-RIGHT del Sprite, pero primero miramos la VELOCIDAD
		if(colisions.at(0) == Colision::Type::LEFT  &&  colisions.at(1) == Colision::Type::BOTTOM){
			posAux = rectPrev.GetBottomRight();
			
			if(posAux.GetX() > rec.GetTopLeft().GetX() && posAux.GetY() < rec.GetTopLeft().GetY() + 1.3f)
				return Colision::Type::BOTTOM;
			else 
                return Colision::Type::LEFT;
			
		}

		if(colisions.at(0) == Colision::Type::RIGHT  &&  colisions.at(1) == Colision::Type::BOTTOM){
			posAux = rectPrev.GetBottomLeft();
			
			if(posAux.GetX() < rec.GetTopRight().GetX() && posAux.GetY() < rec.GetTopLeft().GetY() + 1.3f)
				return Colision::Type::BOTTOM;
			else 
                return Colision::Type::RIGHT;
		}
		
		if(colisions.at(0) == Colision::Type::LEFT  &&  colisions.at(1) == Colision::Type::TOP){
			posAux = rectPrev.GetTopRight();
			
			if(posAux.GetX() > rec.GetBottomLeft().GetX() + 1.3f) //Si está arriba a la derecha de la esquina
				return Colision::Type::TOP;
			else 
                return Colision::Type::LEFT;
		}
        
         if(colisions.at(0) == Colision::Type::RIGHT  &&  colisions.at(1) == Colision::Type::TOP){
			posAux = rectPrev.GetTopLeft();
			
			if(posAux.GetX() < rec.GetBottomRight().GetX() -1.3f) //Si está arriba a la derecha de la esquina
				return Colision::Type::TOP;
			else 
                return Colision::Type::RIGHT;
		}       
	}
}
	

void Colisionable::MoveToEdge(Colision::Type type, const Rectangle& rec, const Time& elapsedTime)
{
	Vector nextPos, currentPos;
    float offset = 0.5f;
    float value = 0.f;
	
	if(type == Colision::Type::BOTTOM){
        nextPos = CalculateNextRect(elapsedTime, nextRectFactor).GetBottomLeft();
        currentPos = entity->GetSprite()->getGlobalBounds().GetBottomLeft();
        float distY = nextPos.GetY() - rec.GetTopLeft().GetY();

        // Calculamos el limite de abajo, pero RESTAMOS la altura
        value = nextPos.GetY() - distY + offset;
        while (value <= rec.GetTopLeft().GetY())
            value += offset;
        
        value -= entity->GetSprite()->getGlobalBounds().GetHeight();
        std::cout << "Limit Bottom: " << value << std::endl;
        entity->SetBottomLimitValue(value);
        entity->SetBottomLimited(true);
	}
	
	else if(type == Colision::Type::RIGHT){
		nextPos = CalculateNextRect(elapsedTime, nextRectFactor).GetTopLeft();
		currentPos = entity->GetSprite()->getGlobalBounds().GetTopLeft();
		float distX = nextPos.GetX() - rec.GetTopRight().GetX();
		
        value = nextPos.GetX() - distX + offset;
        while (value <= rec.GetTopRight().GetX())
            value += offset;
        
        entity->SetLeftLimitValue(value);
        entity->SetLeftLimited(true);
	}
	
	else if(type == Colision::Type::LEFT){
		nextPos = CalculateNextRect(elapsedTime, nextRectFactor).GetTopRight();
		currentPos = entity->GetSprite()->getGlobalBounds().GetTopRight();
		float distX = nextPos.GetX() - rec.GetTopLeft().GetX();
		
        value = nextPos.GetX() - distX - offset;
        while (value >= rec.GetTopLeft().GetX())
            value -= offset;
        
        value -= entity->GetSprite()->getGlobalBounds().GetWidth();
        
        entity->SetRightLimitValue(value);
        entity->SetRightLimited(true);
	}
	
	else if(type == Colision::Type::TOP){
		nextPos = CalculateNextRect(elapsedTime, nextRectFactor).GetTopLeft();
		currentPos = entity->GetSprite()->getGlobalBounds().GetTopLeft();
		float distY = nextPos.GetY() - rec.GetBottomLeft().GetY();
			
        value = nextPos.GetY() - distY + offset;
        while (value <= rec.GetBottomLeft().GetY())
            value += offset;
        
        entity->SetTopLimitValue(value);
        entity->SetTopLimited(true);
	}
	
	
}


