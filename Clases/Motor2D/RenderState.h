/* 
 * File:   Render.h
 * Author: linuxero
 *
 * Created on March 5, 2014, 8:08 AM
 */

#ifndef RENDER_H
#define	RENDER_H

#include "../Otros/Vector.h"
#include "RenderWindow.h"

class RenderState {
public:
	RenderState();
	RenderState(const RenderState& orig);
	virtual ~RenderState();
	
	void Draw(RenderWindow &window, const Vector& posPrev, const Vector& posNew, float interpolation, SpriteSheet& sp);
	Vector& GetRenderPosition() const { return *posRender; }

private:
	Vector*		posRender;
	
};

#endif	/* RENDER_H */

