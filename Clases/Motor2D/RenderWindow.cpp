/* 
 * File:   Window.cpp
 * Author: linuxero
 * 
 * Created on March 12, 2014, 10:00 AM
 */

#include "RenderWindow.h"
#include "../Entities/Entity.h"

RenderWindow* RenderWindow::instance = 0;

RenderWindow* RenderWindow::Instance() {
	if(instance == 0)
		instance = new RenderWindow(1080,720, "Gate - hito 2");
	
	return instance;
}

RenderWindow::RenderWindow(int width, int height, const std::string titulo, int color) {
	renderWindow = new sf::RenderWindow((sf::VideoMode(width, height, color)), titulo);
	this->width = width;
	this->height = height;
}

RenderWindow::RenderWindow(const RenderWindow& orig) {
}

RenderWindow::~RenderWindow() {
	delete renderWindow;
	renderWindow = NULL;
}

void RenderWindow::Draw(SpriteSheet& sp){
	renderWindow->draw(*sp.GetSprite());
}

void RenderWindow::Draw(const sf::Text& t){
	renderWindow->draw(t);
}
