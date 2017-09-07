#pragma once
#include"MinHeap.h"
#include"LinkedList.h"
#include"stack.h"

class SpanningTree
{
public:
	SpanningTree(void);	//������
	~SpanningTree(void);	//�Ҹ���

	bool Kruskal(Gu_Vertex* m_pHead);	//Minimum spanning tree kruskal algorithm
	int Find(int* arr, int x);			//Union �ϱ� ���ؼ� �� ������ ���Կ��θ� ��ȯ �ϴ� find�Լ�
	void Union(int* arr, int u, int v);	//���� ������ ��Ÿ���� �迭�� ��ġ�� Gu_Vertex�� ��� ������ ����
	void InitialUseflag(Gu_Vertex* m_pHead);	//�ϳ��� ���� ���ؼ� �ش� dong vertex�� edge�� ������� useflag�� 0���� ����� �Լ�

	Gu_Vertex* MinDistance(LinkedList& list);	//list�߿��� �湮���� �ʰ�, ���� ���� cost�� ������ Node�� ��ȯ
	int Dijkstra(LinkedList& list,Gu_Vertex* source, Gu_Vertex* destination);	//��� Node source�� ���� Node destination�� �޾Ƽ� �ش� �ִܰŸ��� ��ȯ�Ѵ�
	stack BackTrace(LinkedList& list, Gu_Vertex* source, Gu_Vertex* destination);	//�̵���� ������ �Լ� for Dijkstra
};

