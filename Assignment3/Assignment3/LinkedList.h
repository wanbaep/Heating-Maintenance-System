#pragma once
#include"Gu_Vertex.h"
#include"Mechanic.h"

class LinkedList
{
private:
	int GVNum;
	Gu_Vertex* m_GVHead;	//Gu_Vertex Node의 1차원 Linked list Head를 가리키는 포인터
	Mechanic* m_MHead;	//Mechanic Node의 1차원 Linked list head를 가리키는 포인터
public:
	LinkedList(void);		//생성자
	~LinkedList(void);		//소멸자
	
	void IncreaseGVNum();	//Gu Vertex의 개수를 증가시키는 함수
	int GetGVNum();			//Gu Vertex의 개수를 Get하는 함수
	Gu_Vertex* GetGVHead();		//Gu_Vertex Node의 head를 Get하는 함수
	Mechanic* GetMHead();		//Mechanic Node의 head를 Get하는 함수


	bool InsertGuVertex(Gu_Vertex* pnode);		//구단위 Node 1차원 Linked List Insert
	bool InsertDongVertex(Dong_Vertex* pnode);	//동단위 Node 1차원 Circular List Insert
	bool InsertMechanic(Mechanic* pnode);		//정비사 1차원 Linked List Insert
	bool DeleteMechanic();				//Mechanic list를 동적할당 해제 하는 함수
	bool DeleteGuList();				//Gu_Vertex & Gu_Edge를 동적할당 해제 하는 함수
	bool DeleteDongList();				//Dong_Vertex & Dong_Edge를 동적할당 해제 하는 함수

	Gu_Vertex* FindGu(char* Guname);	//List 내에 존재하는 인자에 해당하는 Gu Vertex Node를 찾아서 반환하는 함수
	Dong_Vertex* FindDong(char* Guname, char* dongname);	//List내에 존재하는 인자와 일치하는 (구,동) Dong_Vertex를 찾아서 반환하는 함수
};

