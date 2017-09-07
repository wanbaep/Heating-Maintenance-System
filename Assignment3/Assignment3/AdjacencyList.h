#pragma once
#include"LinkedList.h"

class AdjacencyList
{
private:
	
public:
	AdjacencyList(void);	//생성자
	~AdjacencyList(void);	//소멸자

	bool InsertGuEdge(LinkedList &list, Gu_Edge* pnode);		//Gu에 대한 인접리스트를 Insert하는 함수
	bool InsertDongEdge(LinkedList &list, Dong_Edge* pnode);	//Dong에 대한 인접리스트를 Insert하는 함수
};

