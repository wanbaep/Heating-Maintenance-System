#include "Mechanic.h"


Mechanic::Mechanic(void)
{
	Name=NULL;
	Workplace=NULL;
	dist=0;
	pNext=NULL;
}


Mechanic::~Mechanic(void)
{
}

void Mechanic::SetName(char* pname)	//정비사의 이름을 Set하는 함수
{
	int len=strlen(pname);	//인자의 길이를 받아온다
	Name=new char[len+1];	//동적할당
	memset(Name,0,len+1);	//배열 초기화
	strcpy(Name,pname);		//값을 copy
}

void Mechanic::SetWorkPlace(char* place)	//정비사의 근무지를 Set하는 함수
{
	int len=strlen(place);		//인자의 길이를 받아온다
	Workplace=new char[len+1];	//동적할당
	memset(Workplace,0,len+1);	//배열 초기화
	strcpy(Workplace,place);	//값을 copy
}

void Mechanic::SetDist(int d)		//정비사가 출발지에서 도착지까지의 거리를 Set하는 함수
{
	dist=d;
}

void Mechanic::SetNext(Mechanic* next)	//다음 정비사를 Set하는 함수
{
	pNext=next;
}

char* Mechanic::GetName()	//정비사의 이름을 Get하는 함수
{
	return Name;
}

char* Mechanic::GetWorkPlace()	//정비사의 근무지를 Get하는 함수
{
	return Workplace;
}

int Mechanic::GetDist()		//정비사의 이동 거리를 Get하는 함수
{
	return dist;
}

Mechanic* Mechanic::GetNext()	//다음 정비사 Node를 Get하는 함수
{
	return pNext;
}
