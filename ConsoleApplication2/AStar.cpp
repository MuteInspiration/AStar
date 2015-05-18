#include "Node.h"

//  �켱���� ť ���� �켱���� ��
bool operator<(const node & a, const node & b)
{
	return a.getPriority() > b.getPriority();
}

// A-star algorithm.
//  ������ ��Ÿ�� ���ڿ��� ����
string pathFind(const int & xStart, const int & yStart,
	const int & xFinish, const int & yFinish)
{
	static priority_queue<node> pq[2]; // list of open (not-yet-tried) nodes
	static int pqi; // pq index
	static node* n0;
	static node* m0;
	static int i, j, x, y, xdx, ydy;
	static char c;
	pqi = 0;

	// ��� ���� �ʱ�ȭ
	for (y = 0; y<m; y++)
	{
		for (x = 0; x<n; x++)
		{
			closed_nodes_map[x][y] = 0;
			open_nodes_map[x][y] = 0;
		}
	}
	// ��带 ����� �����Ѵ�.
	// OpenList���� ��带 �ִ´�.
	n0 = new node(xStart, yStart, 0, 0);
	n0->updatePriority(xFinish, yFinish);
	pq[pqi].push(*n0);		// �켱���� ť�� n0�� �ִ´�.
	open_nodes_map[x][y] = n0->getPriority(); // ����� �켱������  ���� ���ʿ� ��ũ�Ѵ�. 

	// A* search
	while (!pq[pqi].empty())		// pg[pgi]�� ��������ʴٸ�
	{
		// �켱������ ���� ���� ��带 OpenList���� �����´�.

		n0 = new node(pq[pqi].top().getxPos(),		// �켱����ť[pq index]�� x��
			pq[pqi].top().getyPos(),		// �켱����ť[pq index]�� y��
			pq[pqi].top().getLevel(),		// �켱����ť[pq index]�� G��
			pq[pqi].top().getPriority());		// �켱����ť[pq index] G+H��

		x = n0->getxPos();		// ������ ���� ����� X���� �����´�
		y = n0->getyPos();		// ������ ���� ����� Y���� �����´�.

		pq[pqi].pop(); // �켱������ ���� ���� Pop��Ų��.
		open_nodes_map[x][y] = 0;
		//  ClosedList�� �߰��Ѥ�.
		closed_nodes_map[x][y] = 1;

		// ���������� �����ϸ� Search�� ��������.
		if (x == xFinish && y == yFinish)
		{
			// ������������ �������� ���� �����.
			string path = "";
			while (!(x == xStart && y == yStart))		// x,y���� �������� �ƴҶ�����
			{
				j = dir_map[x][y];		// j = dir_map -> ������ �������ִ� ���� �迭
				c = '0' + (j + dir / 2) % dir;		// dir ��������̳� �����ִ� ������ ����
				path = c + path;				// Path �� ����Ѵ�.
				x += dx[j];		
				y += dy[j];
			}

	
			delete n0;
			while (!pq[pqi].empty()) pq[pqi].pop();
			return path;
		}

		// ��� �����ִ� ���⿡ ���ؼ� �����ִ� ������ ����
		for (i = 0; i<dir; i++)
		{
			xdx = x + dx[i];
			ydy = y + dy[i];

			if (!(xdx<0 || xdx>n - 1 || ydy<0 || ydy>m - 1 || map[xdx][ydy] == 1
				|| closed_nodes_map[xdx][ydy] == 1))
			{
				// �ڽ� ��带 ����
				m0 = new node(xdx, ydy, n0->getLevel(),
					n0->getPriority());
				m0->nextLevel(i);
				m0->updatePriority(xFinish, yFinish);

	
				// openList�� �ƹ��͵� ���ٸ�
				if (open_nodes_map[xdx][ydy] == 0)
				{
					// �ڽĳ���� �켱������ �ִ´�.
					open_nodes_map[xdx][ydy] = m0->getPriority();
					pq[pqi].push(*m0);
					// �θ� ��� ������ �ִ´�.
					dir_map[xdx][ydy] = (i + dir / 2) % dir;
				}
				// OpenList�ȿ� �ִ� ���� �ڽĳ���� �켱�������� ���ٸ�
				else if (open_nodes_map[xdx][ydy] > m0->getPriority())
				{
					// �켱���� ������ ������Ʈ
					open_nodes_map[xdx][ydy] = m0->getPriority();
					// �θ� ���� ������ ������Ʈ
					dir_map[xdx][ydy] = (i + dir / 2) % dir;

					// ��带 ����ִ� pq�� �ٸ� �ϳ��� �ٲ�

					while (!(pq[pqi].top().getxPos() == xdx		// pq[pgi]�� �� ���� ���� ���� x���� xdx���� ����
						&& pq[pqi].top().getyPos() == ydy))	 // pq[pgi]�� �� ���� ���� ���� y���� ydy���� ������
					{
						pq[1 - pqi].push(pq[pqi].top());  // pq[1 - pqindex]�ȿ� top�� ���� ���� �ִ´�.
						pq[pqi].pop();		// ���� �� ����
					}

					pq[pqi].pop(); // ���� �� ����


					if (pq[pqi].size() > pq[1 - pqi].size())
						pqi = 1 - pqi;

					while (!pq[pqi].empty())
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pqi = 1 - pqi;
					pq[pqi].push(*m0); // ���� ��带 �ִ´�.
				}
				else 
					delete m0; // garbage collection
			}
		}
		delete n0; // garbage collection
	}
	return ""; // no route found
}


int main()
{
	srand(time(NULL));

	// �� �ʱ�ȭ
	for (int y = 0; y<m; y++)
	{
		for (int x = 0; x<n; x++) 
			map[x][y] = 0;
	}

	// �� �����
	for (int x = n / 8; x<n * 7 / 8; x++)
	{
		map[x][m / 2] = 1;
	}
	for (int y = m / 8; y<m * 7 / 8; y++)
	{
		map[n / 2][y] = 1;
	}

	// ����������  A Start B End
	int xA, yA, xB, yB;

	switch (rand() % 8)
	{
		case 0: xA = 0; yA = 0; xB = n - 1; yB = m - 1; break;
		case 1: xA = 0; yA = m - 1; xB = n - 1; yB = 0; break;
		case 2: xA = n / 2 - 1; yA = m / 2 - 1; xB = n / 2 + 1; yB = m / 2 + 1; break;
		case 3: xA = n / 2 - 1; yA = m / 2 + 1; xB = n / 2 + 1; yB = m / 2 - 1; break;
		case 4: xA = n / 2 - 1; yA = 0; xB = n / 2 + 1; yB = m - 1; break;
		case 5: xA = n / 2 + 1; yA = m - 1; xB = n / 2 - 1; yB = 0; break;
		case 6: xA = 0; yA = m / 2 - 1; xB = n - 1; yB = m / 2 + 1; break;
		case 7: xA = n - 1; yA = m / 2 + 1; xB = 0; yB = m / 2 - 1; break;
	}




	cout << "Map Size (X,Y): " << n << "," << m << endl;
	cout << "Start: " << xA << "," << yA << endl;
	cout << "Finish: " << xB << "," << yB << endl;

	// get the route
	clock_t start = clock();
	string route = pathFind(xA, yA, xB, yB);

	if (route == "")		// ���� ���� ������
		cout << "An empty route generated!" << endl;

	clock_t end = clock();		// �ð� ����
	double time_elapsed = double(end - start);
	cout << "�� ����µ� �ɸ� ���ð� (ms): " << time_elapsed << endl;
	cout << "Route:" << endl;
	cout << route << endl << endl;


	if (route.length() > 0)		// ���� ���� �ִٸ�
	{
		int j; char c;
		int x = xA;
		int y = yA;
		map[x][y] = 2;

		for (int i = 0; i<route.length(); i++)
		{
			c = route.at(i);
			j = atoi(&c); // ���ڿ� -> int
			x = x + dx[j];
			y = y + dy[j];
			map[x][y] = 3;
		}

		map[x][y] = 4;


		for (int y = 0; y<m; y++)
		{
			for (int x = 0; x<n; x++)
			if (map[x][y] == 0)
				cout << ".";
			else if (map[x][y] == 1)
				cout << "W"; //���ع�
			else if (map[x][y] == 2)
				cout << "S"; 
			else if (map[x][y] == 3)
				cout << "G";
			else if (map[x][y] == 4)
				cout << "F"; 
			cout << endl;
		}
	}
	getchar(); 
	return(0);
}