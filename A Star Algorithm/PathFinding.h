#pragma once

#include "Vector3.h"
#include "Search.h"
#include <vector>
using namespace std;


class PathFinding
{

private:
	void SetStartAndGoal(SearchCell start, SearchCell goal);
	void PathOpened(int x, int z, float newCost, SearchCell *parent);
	SearchCell *GetNextCell();
	void ContinuePath();

	SearchCell* m_startCell;
	SearchCell* m_goalCell;
	std::vector<SearchCell*> m_openList;
	std::vector<SearchCell*> m_vistedList;
	std::vector<Vector3*> m_PathToGoal;

public:
	PathFinding();
	~PathFinding();

	void FindPath(Vector3 currentPos, Vector3 targetPos);
	Vector3 NextPathPos();
	void ClearOpenList()
	{
		m_openList.clear();
	}
	void ClearVistedList()
	{
		m_vistedList.clear();
	}
	void ClearPathToGoal()
	{
		m_PathToGoal.clear();
	}

	bool m_initalizedStartGoal;
	bool m_foundGoal;


};

