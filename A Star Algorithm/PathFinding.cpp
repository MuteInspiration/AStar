#include "PathFinding.h"


PathFinding::PathFinding()
{
	m_initalizedStartGoal = false;
	m_foundGoal = false;
}


PathFinding::~PathFinding()
{
}

void PathFinding::FindPath(Vector3 currentPos, Vector3 targetPos)
{
	if (!m_initalizedStartGoal)
	{
		for (int i = 0; i < m_openList.size(); i++)
		{
			delete m_openList[i];
		}

		m_openList.clear();

		for (int i = 0; i < m_vistedList.size(); i++)
		{
			delete m_vistedList[i];
		}

		m_vistedList.clear();

		for (int i = 0; m_PathToGoal.size(); i++)
		{
			delete m_PathToGoal[i];
		}

		m_PathToGoal.clear();

		// 초기화 시작
		SearchCell start;
		start.m_xcoord = currentPos.x;
		start.m_zcoord = currentPos.z;


		// initalize goal
		SearchCell goal;
		goal.m_xcoord = targetPos.x;
		goal.m_zcoord = targetPos.y;

		SetStartAndGoal(start, goal);
		m_initalizedStartGoal = true;
	}

	if (m_initalizedStartGoal)
	{
		ContinuePath();
	}

}

void PathFinding::SetStartAndGoal(SearchCell start, SearchCell goal)
{
	m_startCell = new SearchCell(start.m_xcoord, start.m_zcoord);

	m_goalCell = new SearchCell(goal.m_xcoord, goal.m_zcoord, &goal);


	m_startCell->G = 0;
	m_startCell->H = m_startCell->ManHattanDistance(m_goalCell);
	m_startCell->Parent = 0;



	m_openList.push_back(m_startCell);
}

SearchCell* PathFinding::GetNextCell()
{
	float bestF = 999999.0f;

	int cellindex = -1;
	SearchCell* nextCell = NULL;

	for (int i = 0; i < m_openList.size(); i++)
	{
		if (m_openList[i]->GetF() < bestF)
		{
			bestF = m_openList[i]->GetF();
			cellindex = i;

		}
	}


	if (cellindex >= 0)
	{
		nextCell = m_openList[cellindex];

		m_vistedList.push_back(nextCell);
		m_openList.erase(m_openList.begin() + cellindex);		// Vector의 begin과 earse함수는 뭐지?

	}

	return nextCell;
}


void PathFinding::PathOpened(int x, int z, float newCost, SearchCell *parent)
{
	/*
	if (CELL_BLOCKED)		벽이나 방해물로 인해 막혔을때
	{
		return;
	}
	*/

	int id = z * WORLD_SIZE + x;
	for (int i = 0; i < m_vistedList.size(); i++)
	{
		if (id == m_vistedList[i]->m_id)
		{
			return;
		}
	}


	SearchCell* newChild = new SearchCell(x, z, parent);
	newChild->G = newCost;
	newChild->H = parent->ManHattanDistance(m_goalCell);


	for (int i = 0; i < m_openList.size(); i++)
	{
		if (id == m_openList[i]->m_id)
		{
			float newF = newChild->G + newCost + m_openList[i]->H;


			if (m_openList[i]->GetF() > newF)
			{
				m_openList[i]->G = newChild->G + newCost;
				m_openList[i]->Parent = newChild;
			}
			else
			{
					// if the F is not Better
				delete newChild;
				return;
			}
	
		}
	}

	m_openList.push_back(newChild);
}

void PathFinding::ContinuePath()
{
	if (m_openList.empty())
	{
		return;
	}

	SearchCell* currentCell = GetNextCell();

	if (currentCell->m_id == m_goalCell->m_id)
	{
		// 도착
		m_goalCell->Parent = currentCell->Parent;

		SearchCell* getPath;

		for (getPath = m_goalCell; getPath != NULL; getPath = getPath->Parent)
		{
			m_PathToGoal.push_back(new Vector3(getPath->m_xcoord, 0, getPath->m_zcoord));
		}

		m_foundGoal = true;
		return;
	} 
	else {
		// 오른쪽으로
		PathOpened(currentCell->m_xcoord + 1, currentCell->m_zcoord, currentCell->G + 1, currentCell);
		// 왼쪽으로
		PathOpened(currentCell->m_xcoord - 1, currentCell->m_zcoord, currentCell->G + 1, currentCell);
		// 위로
		PathOpened(currentCell->m_xcoord, currentCell->m_zcoord + 1, currentCell->G + 1, currentCell);
		// 아래
		PathOpened(currentCell->m_xcoord, currentCell->m_zcoord - 1, currentCell->G + 1, currentCell);


		// 왼쪽-위 코스트는 루트2
		PathOpened(currentCell->m_xcoord - 1, currentCell->m_zcoord + 1, currentCell->G + 1.414f, currentCell);
		// 오른쪽 - 위
		PathOpened(currentCell->m_xcoord + 1, currentCell->m_zcoord + 1, currentCell->G + 1.414f, currentCell);
		// 왼쪽-아래
		PathOpened(currentCell->m_xcoord - 1, currentCell->m_zcoord - 1, currentCell->G + 1.414f, currentCell);
		// 오른쪽 아래
		PathOpened(currentCell->m_xcoord + 1, currentCell->m_zcoord - 1, currentCell->G + 1.414f, currentCell);

		for (int i = 0; i < m_openList.size(); i++)
		{
			if (currentCell->m_id == m_openList[i]->m_id)
			{
				m_openList.erase(m_openList.begin() + i);
			}
		}

	}
}

Vector3 PathFinding::NextPathPos()
{
	int index = 1;
	Vector3 nextPos;
	nextPos.x = m_PathToGoal[m_PathToGoal.size() - index]->x;
	nextPos.z = m_PathToGoal[m_PathToGoal.size() - index]->z;

	Vector3 distance = nextPos - pos;

	if (index < m_PathToGoal.size())
	{
		if (distance.length() < radius)
		{
			m_PathToGoal.erase(m_PathToGoal.end() - index);
		}
	}

	return nextPos;

}