#pragma once

class Gu_Vertex;
class Gu_Edge
{
private:
	char* FromGu;	//출발점이 되는 Gu Vertex의 이름정보
	char* ToGu;		//도착점이 되는 Gu Vertex의 이름정보
	int distance;	//거리를 저장할 변수
	Gu_Edge* E_Next;	//다음 edge를 가리킬 변수
	Gu_Vertex* toGu_Next;	//to에 해당하는 Vertex를 가리키는 변수
public:
	Gu_Edge(void);	//생성자
	~Gu_Edge(void);	//소멸자

	void SetFromGu(char* fromgu);	//From에 해당하는 Gu의 이름을 set하는 함수
	void SetToGu(char* togu);		//to에 해당하는 Gu의 이름을 Set하는 함수
	void SetDist1(char* dist);		//char형 distance에 해당하는 값을 Set하는 함수
	void SetDist2(int dist);		//int형 distance에 해당하는 값을 set하는 함수
	void SetENext(Gu_Edge* next);	//다음 Gu Vertex의 edge를 가리킬 포인터
	void SetToGuNext(Gu_Vertex* next);	//to에 해당하는 vertex를 와 연결을 set하는 함수

	char* GetFromGu();	//from에 해당하는 gu이름을 get하는 함수
	char* GetToGu();	//to에 해당하는 gu의 이름을 Get하는 함수
	int GetDist();		//distance의 값을 Get하는 함수
	Gu_Edge* GetENext();	//다음 Edge를 가리킬 포인터
	Gu_Vertex* GetToGuNext();	//To에 해당하는 vertex를 get하는 함수
};

