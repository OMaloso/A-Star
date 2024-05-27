#pragma once
#include <SFML/Graphics.hpp>

///////////////////////////////////////
/// Name: Node.h
/// Description: Header file for Node class
///////////////////////////////////////

class CNode
{

private:

public:

	sf::Vector2i m_arrayPosition; // node position relative to board (x,y)
	float m_G; // movement cost from one node to another nearby node.
	float m_H; // movement cost from given node to destination node, ignoring all the obstacles. Often referred as heuristic.
	float m_F; // G + H
	sf::Vector2i m_iDirection; // direction to source

	/// default constructor
	CNode();

	/// Function: constructor
	/// Param: sf::Vector2i _arrayPos, float _fG, float _fH, sf::Vector2i _direction
	CNode(sf::Vector2i _arrayPos, float _fG, float _fH, sf::Vector2i _direction);

	/// destructor
	~CNode();
};

