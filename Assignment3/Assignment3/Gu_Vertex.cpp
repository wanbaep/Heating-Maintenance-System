#include "Gu_Vertex.h"


Gu_Vertex::Gu_Vertex(void)	//생성자
{
	GuName=NULL;	//멤버변수 초기화
	dongnum=0;
	arr=0;
	cost=0;
	visit=false;
	GV_Next=NULL;
	GE_Next=NULL;
	D_Next=NULL;
	S_Next=NULL;
}


Gu_Vertex::~Gu_Vertex(void)	//소멸자
{
	delete[] GuName;	//동적할당 해제
	delete[] arr;
}

void Gu_Vertex::SetGuName(char* name)	//해당 Gu의 이름을 Set하는 함수
{
	int len=strlen(name);	//인자의 길이를 받는다
	GuName=new char[len+1];	//동적할당
	memset(GuName,0,len+1);	//배열 초기화
	strcpy(GuName,name);	//값을 copy
}

void Gu_Vertex::IncreaseDongNum()	//삽입되는 Dong의 개수를 증가시키는 함수
{
	dongnum++;	//dongnum값을 0부터 증가
}

void Gu_Vertex::SetArray(int num)	//MST에서 사용될 Array를 Set하는 함수
{
	arr=new int[num];		//인자의 길이를 받는다
	memset(arr,0,num);		//배열 1차원 초기화
	for(int i=0; i<num;i++)	//반복문을 통한 2차원 배열 초기화
		arr[i]=i;
}

void Gu_Vertex::SetCost(int co)//Dijkstra에서 사용될 Cost를 Set하는 함수
{
	cost=co;
}

void Gu_Vertex::SetVisit(bool vis)//Dijkstra에서 사용될 Visit에 대해서 Set하는 함수
{
	visit=vis;
}

void Gu_Vertex::SetGVNext(Gu_Vertex* next)//Gu Vertex의 다음을 Set하는 함수
{
	GV_Next=next;
}

void Gu_Vertex::SetGENext(Gu_Edge* next)//Gu Edge를 Set하는 함수
{
	GE_Next=next;
}

void Gu_Vertex::SetDNext(Dong_Vertex* next)//head에 해당하는 Dong Vertex를 Set하는 함수
{
	D_Next=next;
}

void Gu_Vertex::SetSNext(Gu_Vertex* next)//stack에서 사용한 Gu Vertex를 가리키는 포인터를 Set하는 함수
{
	S_Next=next;
}

char* Gu_Vertex::GetGuName()	//GuName을 Get하는함수
{
	return GuName;
}

int Gu_Vertex::GetDongNum()	//DongNum을 Get하는함수
{
	return dongnum;
}

int* Gu_Vertex::GetArray()	//Vertex의 array를 Get하는함수
{
	return arr;
}

int Gu_Vertex::GetCost()	//Cost 값을 Get하는 함수
{
	return cost;
}
bool Gu_Vertex::GetVisit()	//vidst값을 Get하는 함수
{
	return visit;
}

Gu_Vertex* Gu_Vertex::GetGVNext()	//다음 Gu Vertex를 Get하는 함수
{
	return GV_Next;
}

Gu_Edge* Gu_Vertex::GetGENext()	//다음 Gu Edge를 Get하는 함수
{
	return GE_Next;
}

Dong_Vertex* Gu_Vertex::GetDNext()	//head Dong을 Get하는 함수
{
	return D_Next;
}

Gu_Vertex* Gu_Vertex::GetSNext()	//Stack의 Next를 Get하는 함수
{
	return S_Next;
}