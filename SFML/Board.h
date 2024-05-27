#pragma once

#include <iostream>

#include "Tile.h"

///////////////////////////////////////
/// Name: Board.h
/// Description: Header file for Board class
///////////////////////////////////////

class CBoard
{
private:


public:
	sf::Texture* m_pTexture; // member texture - tilemap texture to be used for the board

	static const int iBoardXSize = 28; // board width
	static const int iBoardYSize = 28; // board height

	sf::Vector2f m_BoardPosition; // position of board

	CTile* tiles[iBoardXSize][iBoardYSize]; // create array of tiles

	/// Function: Constructor
	CBoard();

	/// Function: Destructor
	~CBoard();

	/// Function: BoardReset
	/// Returns: Void
	/// Param: None
	/// Description: Resets board to default
	void BoardReset();

	/// Function: UpdateTile
	/// Returns: Void
	/// Param: sf::Vector2i _position, int _iXPosTilemap, int _iYPosTilemap
	/// Description: Updates tile on board
	void UpdateTile(sf::Vector2i _position, int _iXPosTilemap, int _iYPosTilemap);

	/// Function: BoardDraw
	/// Returns: Void
	/// Param: sf::RenderWindow* _window
	/// Description: Draws the board to the window
	void BoardDraw(sf::RenderWindow* _window);

};

