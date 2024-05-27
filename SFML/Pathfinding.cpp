#include "Pathfinding.h"

CPathfinding::CPathfinding()
{
	m_currentNodePos = m_startPos;
	m_fCurrentGValue = 0;
}

CPathfinding::~CPathfinding()
{
}

void CPathfinding::AddNodeOpenVector(sf::Vector2i _arrayPos, float _fG, float _fH, sf::Vector2i _direction)
{
	CNode* newNode = new CNode(_arrayPos, _fG, _fH, _direction);
	m_openVector.push_back(*newNode);
}

void CPathfinding::AddNodeCloseVector(sf::Vector2i _arrayPos, float _fG, float _fH, sf::Vector2i _direction)
{
	CNode* newNode = new CNode(_arrayPos, _fG, _fH, _direction);
	m_closeVector.push_back(*newNode);
}

void CPathfinding::AddNodeImpassableVector(sf::Vector2i _arrayPos, float _fG, float _fH)
{
	CNode* newNode = new CNode(_arrayPos, _fG, _fH, sf::Vector2i(0, 0));
	m_impassableVector.push_back(*newNode);
}

void CPathfinding::AStarAlgorithm(CBoard* _board)
{
	CPathfinding::AddNodeCloseVector(sf::Vector2i(m_startPos.x, m_startPos.y), CPathfinding::GValue(m_startPos, m_startPos), CPathfinding::HValue(m_startPos), sf::Vector2i(0, 0)); // place start into close vector
	m_currentNodePos = m_startPos;
	float fLowestF = 1000;//m_closeVector[0].m_F;

	while (m_currentNodePos != m_endPos) // keep running algorithm until goal is reached
	{
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if ((i != 0 || j != 0) && (m_currentNodePos.x + j >= 0 && m_currentNodePos.y + i >= 0) && (m_currentNodePos.x + j < _board->iBoardXSize && m_currentNodePos.y + i < _board->iBoardYSize))
				{
					bool bNotInImpassableVector = true;
					for (unsigned int k = 0; k < m_impassableVector.size(); k++) // check if adjacent tile is impassable
					{
						if (m_currentNodePos.x + j == m_impassableVector[k].m_arrayPosition.x && m_currentNodePos.y + i == m_impassableVector[k].m_arrayPosition.y)
						{
							bNotInImpassableVector = false;
						}
					}
					bool bNotInCloseVector = true;
					for (unsigned int k = 0; k < m_closeVector.size(); k++) // check if adjacent tile is already in close vector
					{
						if (m_currentNodePos.x + j == m_closeVector[k].m_arrayPosition.x && m_currentNodePos.y + i == m_closeVector[k].m_arrayPosition.y)
						{
							bNotInCloseVector = false;
						}
					}
					bool bNotInOpenVector = true;
					for (unsigned int k = 0; k < m_openVector.size(); k++) // check if adjacent tile is already in open vector
					{
						if (m_currentNodePos.x + j == m_openVector[k].m_arrayPosition.x && m_currentNodePos.y + i == m_openVector[k].m_arrayPosition.y)
						{
							bNotInOpenVector = false;
							if (CPathfinding::GValue(sf::Vector2i(m_currentNodePos.x + j, m_currentNodePos.y + i), m_currentNodePos) + m_fCurrentGValue < m_openVector[k].m_G) // check if G value is less than previous
							{
								m_openVector[k].m_G = CPathfinding::GValue(sf::Vector2i(m_currentNodePos.x + j, m_currentNodePos.y + i), m_currentNodePos) + m_fCurrentGValue; // if yes, update new G value
								m_openVector[k].m_F = m_openVector[k].m_G + m_openVector[k].m_H; // update F value if G changes
								m_openVector[k].m_iDirection = sf::Vector2i(-j, -i);
							}
						}
					}
					if (bNotInCloseVector == true && bNotInOpenVector == true && bNotInImpassableVector == true) // if adjacent tile not in either vector, add to open vector
					{
						bool bObsticleDiagonal = false;
						if (j == -1 && i == -1)
						{
							for (unsigned int k = 0; k < m_impassableVector.size(); k++)
							{
								if (m_impassableVector[k].m_arrayPosition.x == m_currentNodePos.x - 1 && m_impassableVector[k].m_arrayPosition.y == m_currentNodePos.y)
								{
									bObsticleDiagonal = true;
								}
								if (m_impassableVector[k].m_arrayPosition.x == m_currentNodePos.x && m_impassableVector[k].m_arrayPosition.y == m_currentNodePos.y - 1)
								{
									bObsticleDiagonal = true;
								}
							}
						}
						if (j == 1 && i == -1)
						{
							for (unsigned int k = 0; k < m_impassableVector.size(); k++)
							{
								if (m_impassableVector[k].m_arrayPosition.x == m_currentNodePos.x + 1 && m_impassableVector[k].m_arrayPosition.y == m_currentNodePos.y)
								{
									bObsticleDiagonal = true;
								}
								if (m_impassableVector[k].m_arrayPosition.x == m_currentNodePos.x && m_impassableVector[k].m_arrayPosition.y == m_currentNodePos.y - 1)
								{
									bObsticleDiagonal = true;
								}
							}
						}
						if (j == -1 && i == 1)
						{
							for (unsigned int k = 0; k < m_impassableVector.size(); k++)
							{
								if (m_impassableVector[k].m_arrayPosition.x == m_currentNodePos.x - 1 && m_impassableVector[k].m_arrayPosition.y == m_currentNodePos.y)
								{
									bObsticleDiagonal = true;
								}
								if (m_impassableVector[k].m_arrayPosition.x == m_currentNodePos.x && m_impassableVector[k].m_arrayPosition.y == m_currentNodePos.y + 1)
								{
									bObsticleDiagonal = true;
								}
							}
						}
						if (j == 1 && i == 1)
						{
							for (unsigned int k = 0; k < m_impassableVector.size(); k++)
							{
								if (m_impassableVector[k].m_arrayPosition.x == m_currentNodePos.x + 1 && m_impassableVector[k].m_arrayPosition.y == m_currentNodePos.y)
								{
									bObsticleDiagonal = true;
								}
								if (m_impassableVector[k].m_arrayPosition.x == m_currentNodePos.x && m_impassableVector[k].m_arrayPosition.y == m_currentNodePos.y + 1)
								{
									bObsticleDiagonal = true;
								}
							}
						}

						if (bObsticleDiagonal == false)
						{
							CPathfinding::AddNodeOpenVector(sf::Vector2i(m_currentNodePos.x + j, m_currentNodePos.y + i),
								CPathfinding::GValue(sf::Vector2i(m_currentNodePos.x + j, m_currentNodePos.y + i), m_currentNodePos) + m_fCurrentGValue,
								CPathfinding::HValue(sf::Vector2i(m_currentNodePos.x + j, m_currentNodePos.y + i)),  sf::Vector2i(-j, -i)); // place into open vector

							// change tile colour for open list
							delete _board->tiles[m_currentNodePos.x + j][m_currentNodePos.y + i];
							_board->tiles[m_currentNodePos.x + j][m_currentNodePos.y + i] = new CTile(_board->m_pTexture, 32, 0, 2, sf::Vector2f(((m_currentNodePos.x + j) * 32) + 16, ((m_currentNodePos.y + i) * 32) + 16), true);
						}
					}
				}
			}
		}
	
		int iNodePosition = 0; // counter for node position in vector
		fLowestF = 1000; // give variable F value of first node in vector
		for (unsigned int i = 0; i < m_openVector.size(); i++) // check through vector list to see if any vector has lower F value
		{
			if (m_openVector[i].m_F < fLowestF)
			{
				fLowestF = m_openVector[i].m_F;
				iNodePosition = i;
				m_currentNodePos = m_openVector[i].m_arrayPosition;
				m_fCurrentGValue = m_openVector[i].m_G;

			}
		}
		if (m_currentNodePos != m_endPos)
		{
			_board->UpdateTile(m_currentNodePos, 2, 0); // change tile colour
		}
	
		// add to close vector
		if (!m_openVector.empty())
		{
			CPathfinding::AddNodeCloseVector(sf::Vector2i(m_currentNodePos.x, m_currentNodePos.y), m_openVector[iNodePosition].m_G, m_openVector[iNodePosition].m_H, m_openVector[iNodePosition].m_iDirection); // place start into close vector
			
			m_openVector.erase(m_openVector.begin() + iNodePosition); // delete from open vector
		}

		if (m_openVector.empty() == true) // stop if cannot find a way to the goal
		{
			std::cout << "Cannot reach goal. Exiting A* Algorithm." << std::endl;
			break;
		}
	}
	std::cout << "Close vector size: " << m_closeVector.size() << std::endl;

	if (m_openVector.empty() == false)
	{
		int iCount = m_closeVector.size() - 1;

		sf::Vector2i iPosition = m_closeVector[m_closeVector.size() - 1].m_arrayPosition;

		for (std::vector<CNode>::iterator it = m_closeVector.end(); it != m_closeVector.begin(); --it) // check through vector list to see if any vector has lower F value
		{
			if (m_closeVector[iCount].m_arrayPosition == iPosition)
			{
				if (m_closeVector[iCount].m_arrayPosition != m_startPos && m_closeVector[iCount].m_arrayPosition != m_endPos)
				{
					_board->UpdateTile(m_closeVector[iCount].m_arrayPosition, 2, 1); // change tile colour
				}

				iPosition = iPosition + m_closeVector[iCount].m_iDirection;
			}
			iCount--;
		}
	}
	// show end tile image even though in open list
	delete _board->tiles[m_endPos.x][m_endPos.y];
	_board->tiles[m_endPos.x][m_endPos.y] = new CTile(_board->m_pTexture, 32, 0, 1, sf::Vector2f((m_endPos.x * 32) + 16, (m_endPos.y * 32) + 16), false);
}

float CPathfinding::GValue(sf::Vector2i _position, sf::Vector2i _position2) // calculate G value
{
	float GValue = (float)sqrt(pow(_position.x - _position2.x, 2) + pow(_position.y - _position2.y, 2));
	return GValue;
}


float CPathfinding::HValue(sf::Vector2i _position) // calculate H value
{
	float HValue = (float)abs(_position.x - m_endPos.x) + abs(_position.y - m_endPos.y);
	return HValue;
}
