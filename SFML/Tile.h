#pragma once

#include <SFML/Graphics.hpp>

///////////////////////////////////////
/// Name: Tile.h
/// Description: Header file for Tile class
///////////////////////////////////////

class CTile
{
private:
	// tile positional and rendering data here
	sf::Sprite* m_pTileSprite; // member sprite
	sf::Vector2f m_TilePosition; // member position

public:

	sf::Vector2i m_TileGridPosition; // tile grid position

	sf::FloatRect m_boundingBox; // bounding box of tile

	/// Function: Constructor
	/// Param: sf::Texture* _pTexture, int _tileSize, int _tileXStart, int _tileYStart, sf::Vector2f _tilePosition, bool _bImpassable
	CTile(sf::Texture* _pTexture, int _tileSize, int _tileXStart, int _tileYStart, sf::Vector2f _tilePosition, bool _bImpassable);

	/// Function: Destructor
	~CTile();

	/// Function: GetSprite
	/// Returns: sf::Sprite*
	/// Param: None
	/// Description: Returns tile sprite 
	sf::Sprite* GetSprite();

	/// Function: UpdateSprite
	/// Returns: Void
	/// Param: None
	/// Description: Updates sprite position 
	void UpdateSprite();

	// occupant data
	bool m_bImpassable = false; // impassable tiles
	bool m_bStart = false; // start location for algorithm
	bool m_bGoal = false; // end goal for algorithm
};

