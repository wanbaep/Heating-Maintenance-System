#include "Gu_Edge.h"
#include"Gu_Vertex.h"

Gu_Edge::Gu_Edge(void)	//생성자
{
	FromGu=NULL;	//초기화
	ToGu=NULL;
	distance=0;
	E_Next=NULL;
	toGu_Next=NULL;
}


Gu_Edge::~Gu_Edge(void)	//소멸자
{
	delete[] FromGu;	//동적할당 해제
	delete[] ToGu;
}

void Gu_Edge::SetFromGu(char* fromgu)	//From에 해당하는 Gu의 이름을 저장하는 함수
{
	int len=strlen(fromgu);	//인자의 길이를 측정
	FromGu=new char[len+1];	//동적할당
	memset(FromGu,0,len+1);	//초기화
	strcpy(FromGu,fromgu);	//값을 copy한다
}

void Gu_Edge::SetToGu(char* togu)	//to에 해당하는 Gu의 이름을 저장하는 함수
{
	int len=strlen(togu);	//인자길이 측정
	ToGu=new char[len+1];	//동적 할당
	memset(ToGu,0,len+1);	//배열 초기화 한다
	strcpy(ToGu,togu);		//값을 copy한다
}

void Gu_Edge::SetDist1(char* dist)	//char형 dist의 값을 distance로 set하는 함수
{
	distance=atoi(dist);
}

void Gu_Edge::SetDist2(int dist)	//int형 dist의 값을 distance로 set하는 함수
{
	distance=dist;
}

void Gu_Edge::SetENext(Gu_Edge* next)	//Gu edge의 다음을 set하는 함수
{
	E_Next=next;
}

void Gu_Edge::SetToGuNext(Gu_Vertex* next)	//To에 해당하는 Gu에 대해서 연결하는 함수
{
	toGu_Next=next;
}

char* Gu_Edge::GetFromGu()	//from에 해당하는 Gu의 이름을 Get하는함수
{
	return FromGu;
}

char* Gu_Edge::GetToGu()	//to에 해당하는 Gu의 이름을 Get하는 함수
{
	return ToGu;
}

int Gu_Edge::GetDist()	//distance의 값을 Get하는 함수
{
	return distance;
}

Gu_Edge* Gu_Edge::GetENext()	//다음 Edge를 Get하는 함수
{
	return E_Next;
}

Gu_Vertex* Gu_Edge::GetToGuNext()	//To에 해당하는 Gu Vertex를 Get하는 함수
{
	return toGu_Next;
}