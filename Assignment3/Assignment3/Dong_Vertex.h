#pragma once
#include"Dong_Edge.h"

class Dong_Vertex
{
private:
	char* GuName;		//해당 동의 Gu의 이름을 가리킬 포인터
	char* DongName;		//동의 이름을 가리킬 포인터
	char* HeatCheck;	//열손실율을 가리킬 포인터
	int index;			//MST kruskal에서 사용할 배열에서의 index를 나타내는 변수
	Dong_Vertex* DV_Next;	//다음 Dong을 가리킬 포인터
	Dong_Edge* DE_Next;		//해당 Dong Vertex에 연결된 edge를 가리킬 포인터

public:
	Dong_Vertex(void);			//생성자
	~Dong_Vertex(void);			//소멸자

	void SetGuName(char* name);		//Gu의 이름을 Set하는 함수
	void SetDongName(char* name);	//Dong의 이름을 Set하는 함수
	void SetHeatCheck(char* check);	//난방 관제소 여부를 Set하는 함수
	void SetIndex(int num);				//index를 Set하는 함수
	void SetDVNext(Dong_Vertex* next);	//Dong Vertex의 Next인 DV_Next를 Set하는 함수
	void SetDENext(Dong_Edge* next);	//Dong Edge의 Next인 DE_Next를 Set하는 함수

	char* GetGuName();			//Gu의 이름을 Get하는 함수
	char* GetDongName();		//Dong의 이름을 Get하는 함수
	char* GetHeatCheck();		//난방 관제소 여부를 Get하는 함수
	int GetIndex();				//index값을 Get하는 함수
	Dong_Vertex* GetDVNext();	//Dong Vertex의 Next인 DV_Next를 Get하는 함수
	Dong_Edge* GetDENext();		//Dong Edge의 Next인 DE_Next를 Get하는 함수
};

