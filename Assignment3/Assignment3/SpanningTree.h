#pragma once
#include"MinHeap.h"
#include"LinkedList.h"
#include"stack.h"

class SpanningTree
{
public:
	SpanningTree(void);	//생성자
	~SpanningTree(void);	//소멸자

	bool Kruskal(Gu_Vertex* m_pHead);	//Minimum spanning tree kruskal algorithm
	int Find(int* arr, int x);			//Union 하기 위해서 각 집합의 포함여부를 반환 하는 find함수
	void Union(int* arr, int u, int v);	//현재 집합을 나타내는 배열의 위치를 Gu_Vertex의 멤버 변수에 저장
	void InitialUseflag(Gu_Vertex* m_pHead);	//하나의 구에 대해서 해당 dong vertex의 edge의 멤버변수 useflag를 0으로 만드는 함수

	Gu_Vertex* MinDistance(LinkedList& list);	//list중에서 방문하지 않고, 제일 작은 cost를 가지는 Node를 반환
	int Dijkstra(LinkedList& list,Gu_Vertex* source, Gu_Vertex* destination);	//출발 Node source와 도착 Node destination을 받아서 해당 최단거리를 반환한다
	stack BackTrace(LinkedList& list, Gu_Vertex* source, Gu_Vertex* destination);	//이동경로 역추적 함수 for Dijkstra
};

