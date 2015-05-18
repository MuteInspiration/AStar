#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
using namespace std;

const int n = 30; // ���� ���λ�����
const int m = 30; // ���� ���λ�����
static int map[n][m];		// ���� ����
static int closed_nodes_map[n][m]; // CloseList ���� ����
static int open_nodes_map[n][m]; // OpenList���� ����
static int dir_map[n][m]; // ���� ���� ����
const int dir = 8; // �����ִ� 8��������


// ���� index���� �� ���� ���ϸ� �ش���ġ�� ����.
static int dx[dir] = { 1, 1, 0, -1, -1, -1, 0, 1 };
static int dy[dir] = { 0, 1, 1, 1, 0, -1, -1, -1 };


class node
{
	int xPos;
	int yPos;
	// �� �������� �� �Ÿ�
	int level;
	// �켱���� = level + �޸���ƽ ���� �Ÿ�
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
		priority = level + estimate(xDest, yDest) * 10; // estimate �޸���ƽ�� ���������� ���� �Ÿ�
	}

	// �밢������ �̵��ϴµ��� �켱���� �ο�
	void nextLevel(const int & i) // i: direction
	{
		level += (dir == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
	}

	// �޸���ƽ������ ������ ���� ���� �Ÿ�
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