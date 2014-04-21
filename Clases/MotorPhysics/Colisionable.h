/* 
 * File:   Colisionable.h
 * Author: linuxero
 *
 * Created on March 11, 2014, 9:49 AM
 */

#ifndef COLISIONABLE_H
#define	COLISIONABLE_H
#include "../Entities/EntActive.h"

namespace Colision{
	enum Type{
		RIGHT, LEFT, BOTTOM, TOP, NONE
	};
}

class Colisionable {
public:
	Colisionable(EntActive* ent);
	Colisionable(const Colisionable& orig);
	virtual ~Colisionable();
	
	virtual const std::string GetClassName() { return "Colisionable";}
	
//************** RECTANGULOS
	
	/// Creará un Rectángulo con los valores RELATIVOS de los parámetros (entre 0.f y 1.f)
	int  CreateRectangle(float x, float y, float width, float height);
	
	// Realizan los cálculos para devolver el/los rectangulos ABSOLUTOS a las coordenadas globales
	Rectangle GetAbsoluteRectangle(const EntActive& ent, const Rectangle& recRelative);
	std::vector<Rectangle> GetAbsoluteRectangles(const EntActive& ent);
	
    
    
	// Calcula siguiente rectángulo. Se podrá usar factor para calcular rectángulos intermedios
	Rectangle CalculateNextRect(const Time& elapsedTime, float factor=1.f);

// ********* COLISIONES capa 1 (ALTO NIVEL)
	virtual void OnColision(Colision::Type type, const Rectangle& rec, const Time& elapsedTime) =0;
	virtual void MoveToEdge(Colision::Type type, const Rectangle& rec, const Time& elapsedTime);
	

protected:
	std::vector<Rectangle*>		*rectColision; // Rectangulos con coordenadas RELATIVAS (ENTRE 0.f y 1.f)
	EntActive*					entity;
	float		nextRectFactor = 1.0f;
	
	
//************** COLISIONES capa 2 (BAJO NIVEL)
 // Devuelven TRUE o FALSE, según si colisionan o no
	virtual bool CheckColision(const Colisionable& ent, const Time& elapsedTime);
	virtual bool CheckColision(const Rectangle& rec, const Time& elapsedTime);
	// y para colisiones intermedias
	virtual bool CheckColision(const Colisionable& ent);
	virtual bool CheckColision(const Rectangle& rec);
	
 // Devuelven el Índice del rectángulo
	virtual int CheckDeepColision(const Colisionable& ent); //** NO HECHA
 
	virtual Colision::Type TypeOfColision(const Rectangle& rec, const Time& elapsedTime);
	
};

#endif	/* COLISIONABLE_H */

