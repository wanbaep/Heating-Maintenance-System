#include "Dong_Vertex.h"


Dong_Vertex::Dong_Vertex(void)	//생성자
{
	GuName=NULL;	//변수들의 초기화
	DongName=NULL;
	HeatCheck=NULL;
	index=0;
	DV_Next=NULL;
	DE_Next=NULL;
}


Dong_Vertex::~Dong_Vertex(void)	//소멸자
{
	delete[] GuName;		//동적할당 해제
	delete[] DongName;
	delete[] HeatCheck;
}

void Dong_Vertex::SetGuName(char* name)		//Gu의 이름을 Set하는 함수
{
	int len=strlen(name);	//name인자의 길이측정
	GuName=new char[len+1];	//길이만큼 동적할당
	memset(GuName,0,len+1);	//배열 초기화
	strcpy(GuName,name);	//값을 copy
}

void Dong_Vertex::SetDongName(char* name)	//Dong의 이름을 Set하는 함수
{
	int len=strlen(name);		//name인자의 길이측정
	DongName=new char[len+1];	//길이만큼 동적할당
	memset(DongName,0,len+1);	//배열 초기화
	strcpy(DongName,name);		//값을 copy
}

void Dong_Vertex::SetHeatCheck(char* check)	//난방 관제소 여부를 Set하는 함수
{
	int len=strlen(check);		//check인자의 길이 측정
	HeatCheck=new char[len+1];	//길이만큼 동적할당
	memset(HeatCheck,0,len+1);	//배열 초기화
	strcpy(HeatCheck,check);	//값을 copy
}

void Dong_Vertex::SetIndex(int num)	//index의 값을 Set하는 함수
{
	index=num;
}

void Dong_Vertex::SetDVNext(Dong_Vertex* next)	//Dong Vertex의 Next인 DV_Next를 Set하는 함수
{
	DV_Next=next;
}

void Dong_Vertex::SetDENext(Dong_Edge* next)	//Dong Edge의 Next인 DE_Next를 Set하는 함수
{
	DE_Next=next;
}

char* Dong_Vertex::GetGuName()			//Gu의 이름을 Get하는 함수
{
	return GuName;
}

char* Dong_Vertex::GetDongName()		//Dong의 이름을 Get하는 함수
{
	return DongName;
}

char* Dong_Vertex::GetHeatCheck()		//난방 관제소 여부를 Get하는 함수
{
	return HeatCheck;
}

int Dong_Vertex::GetIndex()		//index의 값을 Get하는 함수
{
	return index;
}

Dong_Vertex* Dong_Vertex::GetDVNext()	//Dong Vertex의 Next인 DV_Next를 Get하는 함수
{
	return DV_Next;
}

Dong_Edge* Dong_Vertex::GetDENext()		//Dong Edge의 Next인 DE_Next를 Get하는 함수
{
	return DE_Next;
}