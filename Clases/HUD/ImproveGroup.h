/* 
 * File:   ImproveGroup.h
 * Author: alejandrojovermorales
 *
 * Created on May 11, 2014, 7:17 PM
 */

#ifndef IMPROVEGROUP_H
#define	IMPROVEGROUP_H

#include "Improve.h"
#include "../Motor2D/RenderWindow.h"

class ImproveGroup {
public:
    ImproveGroup(const Vector& pos, std::string title, const sf::Texture& tex);
    virtual ~ImproveGroup();
    
    void Draw();
    void Update(const Time& timeElapsed);
    
    void CreateImprove(std::string title, Parameters::ID type);
    
    bool active=true;
    
private:
    
    Vector      *position;
    sf::Text    *textTitle;
    SpriteSheet *icon;
    
    std::vector<Improve*>   *vImproves;
};

#endif	/* IMPROVE_H */

