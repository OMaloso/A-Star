#include "Node.h"

// default constructor
CNode::CNode() 
{
	m_arrayPosition = sf::Vector2i(0,0);
	m_G = 0;
	m_H = 0;
	m_F = m_G + m_H;
	m_iDirection = sf::Vector2i(0,0);
}

// constructor
CNode::CNode(sf::Vector2i _arrayPos, float _fG, float _fH, sf::Vector2i _direction) /// Function: constructor
{
	m_arrayPosition = _arrayPos;
	m_G = _fG;
	m_H = _fH;
	m_F = m_G + m_H;
	m_iDirection = _direction;
}

// destructor
CNode::~CNode()
{
}
