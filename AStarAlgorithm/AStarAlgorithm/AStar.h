#pragma once


struct st_Node
{
	// Ÿ�� ��ġ
	int m_iXpos;
	int m_iYpos;
	
	st_Node *pParentNode;

	float m_F;
	float m_G;
	float m_H;
};
// �� �ּҴ� ���ּҰ� �ƴ� Ÿ���ּҸ� �ѱ��.
// Return : True �� False �̿ϼ�
bool PathFind(int startX, int startY, int endX, int endY);
void AxisEightAddNode(st_Node *pParent);

// ������ ������ִ°��� �Ǵܿ����̴�. �̹� ������� �ֵ� �������.
// ��, �������� ���⼭ ��ŵ�ϵ��� ����.
bool TileCheck(int Xpos, int Ypos);
void MakeNode(st_Node *pParent, int X, int Y);
void DrawMap();

bool compNode(const st_Node* a, const st_Node *b);


void Clear();

void PrintPath();