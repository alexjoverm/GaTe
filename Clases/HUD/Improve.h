/* 
 * File:   Improve.h
 * Author: alejandrojovermorales
 *
 * Created on May 11, 2014, 7:17 PM
 */

#ifndef IMPROVE_H
#define	IMPROVE_H

#include "ImageButton.h"
#include "Lifebar.h"
#include "../Otros/Vector.h"
#include "../Managers/StatusManager.h"

class Improve {
public:
    Improve(const Vector& pos, std::string title, Parameters::ID type);
    virtual ~Improve();
    
    void Draw();
    void Update(const Time& elapsedTime);
    
    bool IsClickedButtonPlus(){ return buttonPlus->IsClicked();}
    
    //void AddLevel(int level, int price);
    void SetLevel(int level, int price);
    
    Vector      *position;
    
private:
    sf::Text    *textTitle, *textPrice;
    ImageButton *buttonPlus;
    Lifebar     *levelBar;
    
    
    Parameters::ID  improveType;
};

#endif	/* IMPROVE_H */

