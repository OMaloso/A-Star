#include "Tile.h"

// constructor
CTile::CTile(sf::Texture* _pTexture, int _tileSize, int _tileXPosition, int _tileYPosition, sf::Vector2f _tilePosition, bool _bImpassable)
{
	m_pTileSprite = new sf::Sprite();
	m_pTileSprite->setTexture(*_pTexture);
	m_pTileSprite->setTextureRect(sf::IntRect(_tileXPosition * _tileSize, _tileYPosition * _tileSize, _tileSize, _tileSize));
	m_TilePosition = _tilePosition;

	m_bImpassable = _bImpassable;

	m_pTileSprite->setOrigin(sf::Vector2f(m_pTileSprite->getGlobalBounds().width / 2, m_pTileSprite->getGlobalBounds().height / 2));

	UpdateSprite();
}

// destructor
CTile::~CTile()
{
	delete m_pTileSprite;
}

// return tile sprite
sf::Sprite* CTile::GetSprite()
{
	return m_pTileSprite;
}

// update tile position
void CTile::UpdateSprite()
{
	m_pTileSprite->setPosition(m_TilePosition);

	m_boundingBox = m_pTileSprite->getGlobalBounds();
}
