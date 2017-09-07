#pragma once
#include"Gu_Vertex.h"
#include"Mechanic.h"

class LinkedList
{
private:
	int GVNum;
	Gu_Vertex* m_GVHead;	//Gu_Vertex Node�� 1���� Linked list Head�� ����Ű�� ������
	Mechanic* m_MHead;	//Mechanic Node�� 1���� Linked list head�� ����Ű�� ������
public:
	LinkedList(void);		//������
	~LinkedList(void);		//�Ҹ���
	
	void IncreaseGVNum();	//Gu Vertex�� ������ ������Ű�� �Լ�
	int GetGVNum();			//Gu Vertex�� ������ Get�ϴ� �Լ�
	Gu_Vertex* GetGVHead();		//Gu_Vertex Node�� head�� Get�ϴ� �Լ�
	Mechanic* GetMHead();		//Mechanic Node�� head�� Get�ϴ� �Լ�


	bool InsertGuVertex(Gu_Vertex* pnode);		//������ Node 1���� Linked List Insert
	bool InsertDongVertex(Dong_Vertex* pnode);	//������ Node 1���� Circular List Insert
	bool InsertMechanic(Mechanic* pnode);		//����� 1���� Linked List Insert
	bool DeleteMechanic();				//Mechanic list�� �����Ҵ� ���� �ϴ� �Լ�
	bool DeleteGuList();				//Gu_Vertex & Gu_Edge�� �����Ҵ� ���� �ϴ� �Լ�
	bool DeleteDongList();				//Dong_Vertex & Dong_Edge�� �����Ҵ� ���� �ϴ� �Լ�

	Gu_Vertex* FindGu(char* Guname);	//List ���� �����ϴ� ���ڿ� �ش��ϴ� Gu Vertex Node�� ã�Ƽ� ��ȯ�ϴ� �Լ�
	Dong_Vertex* FindDong(char* Guname, char* dongname);	//List���� �����ϴ� ���ڿ� ��ġ�ϴ� (��,��) Dong_Vertex�� ã�Ƽ� ��ȯ�ϴ� �Լ�
};

