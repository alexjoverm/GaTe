/******************************************/
/*             SPRITESHEET.CPP            */
/******************************************/

#include <SFML/Graphics.hpp>
#include "SpriteSheet.h"
#include "../Managers/ResourceManager.h"

SpriteSheet::SpriteSheet(const sf::Texture& texture)
{
    m_heightTile = 0;
    m_widthTile = 0;
    m_numColumns = 1;
    m_numRows = 1;
    m_numTiles = m_numRows * m_numColumns;
    m_sprite = new sf::Sprite(texture);
}

SpriteSheet::~SpriteSheet() {
	delete m_sprite;
	m_sprite = NULL;
}

void SpriteSheet::SetNumRowsColumns()
{
    m_numRows = m_sprite->getTexture()->getSize().y / m_heightTile;
    m_numColumns = m_sprite->getTexture()->getSize().x / m_widthTile;
    m_numTiles = m_numRows * m_numColumns;
}

void SpriteSheet::SetOrientation(Transform::Orientation orient){
	if(orient == Transform::Orientation::Left && orientation == Transform::Orientation::Right){ // Orientar a la Izquierda
		m_sprite->setScale(-1, 1);
		orientation = Transform::Orientation::Left;
	}
	else if(orient == Transform::Orientation::Right && orientation == Transform::Orientation::Left){ // Orientar a la derecha
		m_sprite->setScale(1, 1);
		orientation = Transform::Orientation::Right;
	}
}

void SpriteSheet::SetWidthTile(int widthTile)
{
    m_widthTile = widthTile;
}

void SpriteSheet::SetHeightTile(int heightTile)
{
    m_heightTile = heightTile;
}

sf::Sprite* SpriteSheet::GetSprite() const
{
    return m_sprite;
}

Vector SpriteSheet::GetSizeTile() const
{
    Vector sizeTile(m_widthTile, m_heightTile);
    return sizeTile;
}

int SpriteSheet::GetRows() const
{
    return m_numRows;
}

int SpriteSheet::GetColumns() const
{
    return m_numColumns;
}

int SpriteSheet::GetTotalTiles() const
{
    return m_numTiles;
}

const sf::Texture*  SpriteSheet::GetTexture() const
{
    return m_sprite->getTexture();
}
