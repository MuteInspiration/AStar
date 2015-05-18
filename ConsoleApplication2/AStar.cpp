#include "Node.h"

//  우선순위 큐 끼리 우선순위 비교
bool operator<(const node & a, const node & b)
{
	return a.getPriority() > b.getPriority();
}

// A-star algorithm.
//  방향을 나타낸 문자열을 리턴
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

	// 노드 맵을 초기화
	for (y = 0; y<m; y++)
	{
		for (x = 0; x<n; x++)
		{
			closed_nodes_map[x][y] = 0;
			open_nodes_map[x][y] = 0;
		}
	}
	// 노드를 만들고 시작한다.
	// OpenList에서 노드를 넣는다.
	n0 = new node(xStart, yStart, 0, 0);
	n0->updatePriority(xFinish, yFinish);
	pq[pqi].push(*n0);		// 우선순위 큐에 n0을 넣는다.
	open_nodes_map[x][y] = n0->getPriority(); // 노드의 우선순위를  오른 노드맵에 마크한다. 

	// A* search
	while (!pq[pqi].empty())		// pg[pgi]가 비어있지않다면
	{
		// 우선순위가 높은 현재 노드를 OpenList에서 가져온다.

		n0 = new node(pq[pqi].top().getxPos(),		// 우선순위큐[pq index]에 x값
			pq[pqi].top().getyPos(),		// 우선순위큐[pq index]에 y값
			pq[pqi].top().getLevel(),		// 우선순위큐[pq index]에 G값
			pq[pqi].top().getPriority());		// 우선순위큐[pq index] G+H값

		x = n0->getxPos();		// 위에서 만든 노드의 X값을 가져온다
		y = n0->getyPos();		// 위에서 만든 노드의 Y값을 가져온다.

		pq[pqi].pop(); // 우선순위가 높은 값을 Pop시킨다.
		open_nodes_map[x][y] = 0;
		//  ClosedList에 추가한ㄷ.
		closed_nodes_map[x][y] = 1;

		// 도착지점에 도착하면 Search는 끝을낸다.
		if (x == xFinish && y == yFinish)
		{
			// 시작지점부터 끝점까지 길을 만든다.
			string path = "";
			while (!(x == xStart && y == yStart))		// x,y값이 시작점이 아닐때까지
			{
				j = dir_map[x][y];		// j = dir_map -> 방향을 가지고있는 맵의 배열
				c = '0' + (j + dir / 2) % dir;		// dir 어느방향이나 갈수있는 방향의 개수
				path = c + path;				// Path 에 기록한다.
				x += dx[j];		
				y += dy[j];
			}

	
			delete n0;
			while (!pq[pqi].empty()) pq[pqi].pop();
			return path;
		}

		// 모든 갈수있는 방향에 대해서 갈수있는 방향을 만듬
		for (i = 0; i<dir; i++)
		{
			xdx = x + dx[i];
			ydy = y + dy[i];

			if (!(xdx<0 || xdx>n - 1 || ydy<0 || ydy>m - 1 || map[xdx][ydy] == 1
				|| closed_nodes_map[xdx][ydy] == 1))
			{
				// 자식 노드를 만듬
				m0 = new node(xdx, ydy, n0->getLevel(),
					n0->getPriority());
				m0->nextLevel(i);
				m0->updatePriority(xFinish, yFinish);

	
				// openList에 아무것도 없다면
				if (open_nodes_map[xdx][ydy] == 0)
				{
					// 자식노드의 우선순위를 넣는다.
					open_nodes_map[xdx][ydy] = m0->getPriority();
					pq[pqi].push(*m0);
					// 부모 노드 방향을 넣는다.
					dir_map[xdx][ydy] = (i + dir / 2) % dir;
				}
				// OpenList안에 있는 값이 자식노드의 우선순위보다 높다면
				else if (open_nodes_map[xdx][ydy] > m0->getPriority())
				{
					// 우선순위 정보를 업데이트
					open_nodes_map[xdx][ydy] = m0->getPriority();
					// 부모 방향 정보를 업데이트
					dir_map[xdx][ydy] = (i + dir / 2) % dir;

					// 노드를 비어있는 pq와 다른 하나를 바꿈

					while (!(pq[pqi].top().getxPos() == xdx		// pq[pgi]의 맨 상위 값에 대한 x값과 xdx값과 같고
						&& pq[pqi].top().getyPos() == ydy))	 // pq[pgi]의 맨 상위 값에 대한 y값과 ydy값과 같으면
					{
						pq[1 - pqi].push(pq[pqi].top());  // pq[1 - pqindex]안에 top에 대한 값을 넣는다.
						pq[pqi].pop();		// 맨위 값 제거
					}

					pq[pqi].pop(); // 맨위 값 제거


					if (pq[pqi].size() > pq[1 - pqi].size())
						pqi = 1 - pqi;

					while (!pq[pqi].empty())
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pqi = 1 - pqi;
					pq[pqi].push(*m0); // 좋은 노드를 넣는다.
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

	// 맵 초기화
	for (int y = 0; y<m; y++)
	{
		for (int x = 0; x<n; x++) 
			map[x][y] = 0;
	}

	// 벽 만들기
	for (int x = n / 8; x<n * 7 / 8; x++)
	{
		map[x][m / 2] = 1;
	}
	for (int y = m / 8; y<m * 7 / 8; y++)
	{
		map[n / 2][y] = 1;
	}

	// 랜덤적으로  A Start B End
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

	if (route == "")		// 만든 길이 없으면
		cout << "An empty route generated!" << endl;

	clock_t end = clock();		// 시간 측정
	double time_elapsed = double(end - start);
	cout << "길 만드는데 걸린 계산시간 (ms): " << time_elapsed << endl;
	cout << "Route:" << endl;
	cout << route << endl << endl;


	if (route.length() > 0)		// 만든 길이 있다면
	{
		int j; char c;
		int x = xA;
		int y = yA;
		map[x][y] = 2;

		for (int i = 0; i<route.length(); i++)
		{
			c = route.at(i);
			j = atoi(&c); // 문자열 -> int
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
				cout << "W"; //장해물
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