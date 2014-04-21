/* 
 * File:   Window.h
 * Author: linuxero
 *
 * Created on March 12, 2014, 10:00 AM
 */

#ifndef WINDOW_H
#define	WINDOW_H

#include <SFML/Graphics.hpp>
#include "../Animations/SpriteSheet.h"


class RenderWindow {
public:
	RenderWindow(int width, int height, const std::string titulo, int color=24);
	RenderWindow(const RenderWindow& orig);
	virtual ~RenderWindow();
	
  // Acciones
	void Draw(SpriteSheet& sp);
	void Draw(const sf::Text& t);
	void Draw(const sf::RectangleShape& r) { renderWindow->draw(r); }
	void Clear(sf::Color cl){ renderWindow->clear(cl); }
	void Display(){ renderWindow->display(); }
	void Close(){ renderWindow->close(); }
	
  // Características
	bool IsOpen(){ return renderWindow->isOpen(); }
	void SetVerticalSyncEnabled(bool v){ renderWindow->setVerticalSyncEnabled(v); }
	void SetFrameLimit(unsigned int limit){ renderWindow->setFramerateLimit(limit); }
	
  // Eventos
	bool PollEvent(sf::Event& ev){ return renderWindow->pollEvent(ev); }
	
	int width, height;
    sf::RenderWindow*	renderWindow;
};

#endif	/* WINDOW_H */

