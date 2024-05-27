#include "Board.h"

// constructor
CBoard::CBoard()
{
	// load tilesheet
	m_pTexture = new sf::Texture();
	if (!m_pTexture->loadFromFile("Images/tiles.png"))
	{
		std::cout << "Failed to load object texture" << std::endl;
	}

	// load tiles based on above array
	for (int mapY = 0; mapY < iBoardYSize; mapY++)
	{
		for (int mapX = 0; mapX < iBoardXSize; mapX++)
		{
			tiles[mapX][mapY] = new CTile(m_pTexture, 32, 0, 0, sf::Vector2f((mapX * 32) + 16, (mapY * 32) + 16), false);
		}
	}
}

// destructor
CBoard::~CBoard()
{
	for (int i = 0; i < iBoardXSize; i++)
	{
		for (int j = 0; j < iBoardYSize; j++)
		{
			delete tiles[i][j];
		}
	}
}

// reset board to default 
void CBoard::BoardReset()
{
	// load tiles based on above array
	for (int mapX = 0; mapX < iBoardYSize; mapX++)
	{
		for (int mapY = 0; mapY < iBoardXSize; mapY++)
		{
			//delete tiles[mapX][mapY];
			tiles[mapX][mapY] = new CTile(m_pTexture, 32, 0, 0, sf::Vector2f((mapX * 32) + 16, (mapY * 32) + 16), false);
		}
	}
}

//Updates tile on board
void CBoard::UpdateTile(sf::Vector2i _position, int _iXPosTilemap, int _iYPosTilemap)
{
	delete tiles[_position.x][_position.y];
	tiles[_position.x][_position.y] = new CTile(m_pTexture, 32, _iXPosTilemap, _iYPosTilemap, sf::Vector2f((_position.x * 32) + 16, (_position.y * 32) + 16), false);
}

// draws the board
void CBoard::BoardDraw(sf::RenderWindow* _window)
{
	for (int i = 0; i < iBoardXSize; i++)
	{
		for (int j = 0; j < iBoardYSize; j++)
		{
			_window->draw(*tiles[i][j]->GetSprite());
		}
	}
}