/* 
 * File:   RenderState.cpp
 * Author: linuxero
 * 
 * Created on March 5, 2014, 8:08 AM
 */

#include "RenderState.h"

RenderState::RenderState() {
	posRender = new Vector();
}

RenderState::RenderState(const RenderState& orig) {
}

RenderState::~RenderState() {
	delete posRender;
	posRender = NULL;
}


void RenderState::Draw(RenderWindow &window, SpriteSheet& sp)
{
	sp.SetPosition(*posRender);
	window.Draw(sp);
}



void RenderState::Draw(RenderWindow &window, const Vector& posPrev, const Vector& posNew, float interpolation, SpriteSheet& sp)
{
	// Seteamos X e Y de posRender (el real para dibujar)

    posRender->SetX(posPrev.GetX() + ((posNew.GetX() - posPrev.GetX()) * interpolation));
    posRender->SetY(posPrev.GetY() + ((posNew.GetY() - posPrev.GetY()) * interpolation));

	
	
	sp.SetPosition(*posRender);
	window.Draw(sp);
}