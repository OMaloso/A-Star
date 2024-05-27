#include <SFML/Graphics.hpp>
#include <cmath>

#include "Board.h"
#include "Pathfinding.h"

int main()
{
	// window properties
	sf::RenderWindow window(sf::VideoMode(896, 1024), "A* Algorithm Implementation", sf::Style::Titlebar | sf::Style::Close);

	CBoard* board = new CBoard(); // create board

	CPathfinding pathfindingAlgorithm; // create instance of pathfinding

	// initialise bools so functions only run once unless programme is restarted
	bool bStartPlaced = false; 
	bool bEndPlaced = false;
	bool bObstaclesPlaced = false;
	bool bAlgorthimHasRun = false; 

	// load font
	sf::Font fontArial;
	if (!fontArial.loadFromFile("Fonts/arial.ttf"))
	{
		std::cout << "Failed to load font" << std::endl;
	}

	// create text
	sf::Text textOutput;
	textOutput.setFont(fontArial);
	textOutput.setString("Select tile for starting location");
	textOutput.setCharacterSize(24);
	textOutput.setPosition(50, 930);
	textOutput.setFillColor(sf::Color::White);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) // close event
				window.close();

			sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y); // mouse position - needed for buttons

			// adding tiles
			for (int i = 0; i < board->iBoardXSize; i++) // x position
			{
				for (int j = 0; j < board->iBoardYSize; j++) // y position
				{
					if (board->tiles[i][j]->m_boundingBox.contains(mousePosition)) // bounding box of tile
					{
						if (event.type == event.MouseButtonReleased)
						{
							if (event.key.code == sf::Mouse::Left)
							{
								if (bStartPlaced == false) // place start tile if not already placed
								{
									delete board->tiles[i][j];
									board->tiles[i][j] = new CTile(board->m_pTexture, 32, 1, 0, sf::Vector2f((i * 32) + 16, (j * 32) + 16), true);
									board->tiles[i][j]->m_bStart = true;
									bStartPlaced = true;
									textOutput.setString("Select tile for end location");
									pathfindingAlgorithm.m_startPos = sf::Vector2i(i, j);
								}
								else if (bEndPlaced == false) // place goal tile if not already placed
								{
									if (board->tiles[i][j]->m_bStart != true) 
									{
										delete board->tiles[i][j];
										board->tiles[i][j] = new CTile(board->m_pTexture, 32, 0, 1, sf::Vector2f((i * 32) + 16, (j * 32) + 16), false);
										board->tiles[i][j]->m_bGoal = true;
										bEndPlaced = true;
										textOutput.setString("Select tiles for impassable obstacles");
										pathfindingAlgorithm.m_endPos = sf::Vector2i(i, j);
									}
									else
									{
										textOutput.setString("Selected tile already in use");
									}
								}
							}
						}
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							if (bObstaclesPlaced == false && bStartPlaced == true && bEndPlaced == true) // place obsticle tile if not already placed
							{
								if (board->tiles[i][j]->m_bStart != true && board->tiles[i][j]->m_bGoal != true && bAlgorthimHasRun == false)
								{
									delete board->tiles[i][j];
									board->tiles[i][j] = new CTile(board->m_pTexture, 32, 1, 1, sf::Vector2f((i * 32) + 16, (j * 32) + 16), true);
									textOutput.setString("Press Spacebar when you have finished placing \nobstacles to run the A* Pathfinding Algorithm");

									pathfindingAlgorithm.AddNodeImpassableVector(sf::Vector2i(i, j), 0, 0);
								}
								else
								{
									textOutput.setString("Selected tile already in use");
								}
							}
						}
					}
				}
			}

			if (event.type == event.KeyReleased)
			{
				if (event.key.code == sf::Keyboard::R) // restart board and pathfinding programme
				{
					board->BoardReset();
					bStartPlaced = false;
					bEndPlaced = false;
					bObstaclesPlaced = false;
					pathfindingAlgorithm.m_openVector.clear();
					pathfindingAlgorithm.m_closeVector.clear();
					pathfindingAlgorithm.m_impassableVector.clear();
					bAlgorthimHasRun = false;
					textOutput.setString("Select tile for starting location");
				}

				if (event.key.code == sf::Keyboard::Space && bAlgorthimHasRun == false) // run A* alorogithm
				{
					bAlgorthimHasRun = true;
					textOutput.setString("A* Algorithm has completed \nPress 'R' to restart.");

					pathfindingAlgorithm.AStarAlgorithm(board);
				}
			}
		}

		window.clear();

		board->BoardDraw(&window); // draw board

		window.draw(textOutput); // draw text

		window.display();
	}

	return 0;
}