#pragma once
#include <cmath>

#define WORLD_SIZE 64

struct SearchCell
{
public:
	int m_xcoord, m_zcoord;
	int m_id;
	SearchCell* Parent;
	float G;
	float H;	// ÈÞ¸®½ºÆ½

	SearchCell() : Parent(0)
	{}
	SearchCell(int x, int z, SearchCell *_parent = 0) :
		m_xcoord(x), m_zcoord(z), Parent(_parent), m_id(z * WORLD_SIZE + z), G(0), H(0)
	{}

	float GetF()
	{
		return G + H;
	}

	float ManHattanDistance(SearchCell *nodeEnd)
	{
		float x = (fabs((float)(this->m_xcoord - nodeEnd->m_xcoord)));
		float z = (fabs((float)(this->m_zcoord - nodeEnd->m_zcoord)));

		return x + z;
	}


};