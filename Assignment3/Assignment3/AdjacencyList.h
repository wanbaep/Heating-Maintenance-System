#pragma once
#include"LinkedList.h"

class AdjacencyList
{
private:
	
public:
	AdjacencyList(void);	//������
	~AdjacencyList(void);	//�Ҹ���

	bool InsertGuEdge(LinkedList &list, Gu_Edge* pnode);		//Gu�� ���� ��������Ʈ�� Insert�ϴ� �Լ�
	bool InsertDongEdge(LinkedList &list, Dong_Edge* pnode);	//Dong�� ���� ��������Ʈ�� Insert�ϴ� �Լ�
};

