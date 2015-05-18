#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
using namespace std;

const int n = 30; // 맵의 가로사이즈
const int m = 30; // 맵의 세로사이즈
static int map[n][m];		// 맵의 정의
static int closed_nodes_map[n][m]; // CloseList 맵의 정의
static int open_nodes_map[n][m]; // OpenList맵의 정의
static int dir_map[n][m]; // 방향 맵의 정의
const int dir = 8; // 갈수있는 8가지방향


// 현재 index에서 이 값을 더하면 해당위치로 간다.
static int dx[dir] = { 1, 1, 0, -1, -1, -1, 0, 1 };
static int dy[dir] = { 0, 1, 1, 1, 0, -1, -1, -1 };


class node
{
	int xPos;
	int yPos;
	// 이 노드까지간 총 거리
	int level;
	// 우선순위 = level + 휴리스틱 남은 거리
	int priority;  

public:
	node(int xp, int yp, int d, int p)
	{
		xPos = xp; 
		yPos = yp; 
		level = d; 
		priority = p;
	}

	int getxPos() const { return xPos; }
	int getyPos() const { return yPos; }
	int getLevel() const { return level; }
	int getPriority() const { return priority; }


	void updatePriority(const int & xDest, const int & yDest)
	{
		priority = level + estimate(xDest, yDest) * 10; // estimate 휴리스틱적 목적지까지 남은 거리
	}

	// 대각선으로 이동하는데에 우선순위 부여
	void nextLevel(const int & i) // i: direction
	{
		level += (dir == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
	}

	// 휴리스틱적으로 목적지 까지 남은 거리
	const int & estimate(const int & xDest, const int & yDest) const
	{
		static int xd, yd, d;
		xd = xDest - xPos;
		yd = yDest - yPos;

		// Euclidian Distance
		d = static_cast<int>(sqrt(xd*xd + yd*yd));


		return(d);
	}
};

#endif