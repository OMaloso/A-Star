#pragma once

#include <vector>

#include "Node.h"
#include "Board.h"

///////////////////////////////////////
/// Name: Pathfinding.h
/// Description: Header file for Pathfinding class
///////////////////////////////////////


class CPathfinding
{
private:


public:

	sf::Vector2i m_startPos;
	sf::Vector2i m_endPos;

	std::vector<CNode> m_openVector;
	std::vector<CNode> m_closeVector;
	std::vector<CNode> m_impassableVector;

	// current node
	sf::Vector2i m_currentNodePos;
	float m_fCurrentGValue;

	CPathfinding();
	~CPathfinding();

	void AddNodeOpenVector(sf::Vector2i _arrayPos, float _fG, float _fH, sf::Vector2i _direction);

	void AddNodeCloseVector(sf::Vector2i _arrayPos, float _G, float _H, sf::Vector2i _direction);

	void AddNodeImpassableVector(sf::Vector2i _arrayPos, float _G, float _H);

	void AStarAlgorithm(CBoard* _board);

	float GValue(sf::Vector2i _position, sf::Vector2i _position2);

	float HValue(sf::Vector2i _position);


};

