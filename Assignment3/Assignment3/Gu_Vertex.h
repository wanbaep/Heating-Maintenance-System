#pragma once

#include"Gu_Edge.h"
#include"Dong_Vertex.h"


class Gu_Vertex
{
private:
	char* GuName;	//해당 구의 이름을 가리킬 포인터
	int dongnum;	//해당 구에 속하는 동의 개수를 count하는 변수
	int* arr;		//해당 구에 속하는 동의 개수에 따른 배열을 동적할당 하는 변수
	int cost;		//목표 Node에서 해당 Node까지 걸리는 거리의 합
	bool visit;		//Shortest Path tree 구현 간에 해당 Node를 방문했는지 확인하는 변수
	Gu_Vertex* GV_Next;	//다음 Gu Vertex를 가리킬 포인터
	Gu_Edge* GE_Next;	//해당 Gu Vertex의 Edge를 가리킬 포인터
	Dong_Vertex* D_Next;	//해당 Gu Vertex의 head인 Dong을 가리킬 포인터
	Gu_Vertex* S_Next;	//스택에서 사용 Next 포인터
public:
	Gu_Vertex(void);	//생성자
	~Gu_Vertex(void);	//소멸자

	//Set함수
	void SetGuName(char* name);	//해당 Gu의 이름을 Set하는 함수
	void IncreaseDongNum();		//삽입되는 Dong의 개수를 증가시키는 함수
	void SetArray(int num);		//MST에서 사용될 Array를 Set하는 함수
	void SetCost(int co);		//Dijkstra에서 사용될 Cost를 Set하는 함수
	void SetVisit(bool vis);	//Dijkstra에서 사용될 Visit에 대해서 Set하는 함수
	void SetGVNext(Gu_Vertex* next);	//Gu Vertex의 다음을 Set하는 함수
	void SetGENext(Gu_Edge* next);		//Gu Edge를 Set하는 함수
	void SetDNext(Dong_Vertex* next);	//head에 해당하는 Dong Vertex를 Set하는 함수
	void SetSNext(Gu_Vertex* next);		//stack에서 사용한 Gu Vertex를 가리키는 포인터를 Set하는 함수

	//Get함수
	char* GetGuName();	//GuName을 Get하는함수
	int GetDongNum();	//DongNum을 Get하는함수
	int* GetArray();	//Vertex의 array를 Get하는함수
	int GetCost();		//Cost 값을 Get하는 함수
	bool GetVisit();	//vidst값을 Get하는 함수
	Gu_Vertex* GetGVNext();	//다음 Gu Vertex를 Get하는 함수
	Gu_Edge* GetGENext();	//다음 Gu Edge를 Get하는 함수
	Dong_Vertex* GetDNext();	//head Dong을 Get하는 함수
	Gu_Vertex* GetSNext();		//Stack의 Next를 Get하는 함수
};

