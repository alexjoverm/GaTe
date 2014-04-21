/******************************************/
/*             SPRITESHEET.HPP            */
/******************************************/

#ifndef SPRITESHEET_H
#define	SPRITESHEET_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "../Otros/Vector.h"
#include "../Otros/Rectangle.h"

namespace Transform{
	enum Orientation{
		Left,Right
	};
}

class SpriteSheet
{
    public:
        SpriteSheet(const sf::Texture& texture);
        ~SpriteSheet();
        
        void SetSprite(sf::Sprite& sprite) { *m_sprite = sprite; }
        
        void SetWidthTile(int widthTile);               //Función para fijar la anchura de los tiles del spritesheet      
        void SetHeightTile(int heightTile);             //Función para fijar la altura de los tiles del spritesheet
		
        const sf::Texture* GetTexture() const;                      //Función que devuelve la textura del spritesheet
		
        Vector GetSizeTile() const;                     //Función que devuelve la anchura(x) y altura(y) del spritesheet
        int GetColumns() const;                               //Función que devuelve el numero de columnas del spritesheet
        int GetRows() const;                                  //Función que devuelve el número de filas del spritesheet
        int GetTotalTiles() const;                            //Función que devuelve el número total de tiles del spritesheet
        sf::Sprite* GetSprite() const;
        
        // Transformaciones
	void SetOrientation(const Transform::Orientation orient);
	Transform::Orientation GetOrientation() const{ return orientation; }
	
	void Move(Vector& v){ m_sprite->move(v.GetX(), v.GetY()); }
	void SetPosition(const Vector& v){ m_sprite->setPosition(v.GetX(), v.GetY()); }
	Vector GetPosition() const{ return Vector(m_sprite->getPosition().x, m_sprite->getPosition().y); }
        
        // Funciones de Bordes
        Rectangle getLocalBounds() const{ return Rectangle(m_sprite->getLocalBounds()); }
        Rectangle getGlobalBounds() const{ return Rectangle(m_sprite->getGlobalBounds()); }
        
        void SetNumRowsColumns();

    private:
       
        sf::Sprite* m_sprite;
		
       Transform::Orientation orientation;              //Por defecto será Right
	std::string idTexture;	
        int m_widthTile;                                //Anchura de los tiles del spritesheet
        int m_heightTile;                               //Altura de los tiles del spritesheet
        int m_numColumns;                               //Numero de columnas del spriteshhet
        int m_numRows;                                  //Numero de filas del spritesheet
        int m_numTiles;                                 //Numero total de tiles del spriteshhet
            
};

#endif	/* SPRITESHEET_HPP */
