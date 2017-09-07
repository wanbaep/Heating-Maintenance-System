#include "Dong_Edge.h"
#include "Dong_Vertex.h"

Dong_Edge::Dong_Edge(void)	//생성자
{
	GuName=NULL;	//변수들의 초기화
	FromDong=NULL;
	ToDong=NULL;
	Pipestatus=NULL;
	LossRate=0;
	overlap=0;
	useflag=0;
	E_Next=NULL;
	toDong_Next=NULL;
	fromDong_Next=NULL;
}


Dong_Edge::~Dong_Edge(void)	//소멸자
{
	delete[] GuName;	//동적할당한 값들에 대해서 동적할당 해제
	delete[] FromDong;
	delete[] ToDong;
	delete[] Pipestatus;
}

void Dong_Edge::SetGuName(char* name)			//해당 동의 구이름을 Set하는 함수
{
	int len=strlen(name);	//인자의 길이를 측정
	GuName=new char[len+1];	//인자의 길이만큼 동적할당
	memset(GuName,0,len+1);	//동적할당한 배열 초기화
	strcpy(GuName,name);	//인자의 값으로 배열을 copy
}

void Dong_Edge::SetFromDong(char* fromdong)	//From에 해당하는 Dong의 이름을 Set하는 함수
{
	int len=strlen(fromdong);	//인자의 길이를 측정
	FromDong=new char[len+1];	//인자의 길이만큼 동적할당
	memset(FromDong,0,len+1);	//동적할당한 배열 초기화
	strcpy(FromDong,fromdong);	//인자의 값으로 배열을 copy
}

void Dong_Edge::SetToDong(char* todong)		//To에 해당하는 Dong의 이름을 Set하는 함수
{
	int len=strlen(todong);	//인자의 길이를 측정
	ToDong=new char[len+1];	//인자의 길이만큼 동적할당
	memset(ToDong,0,len+1);	//동적할당한 배열 초기화
	strcpy(ToDong,todong);	//인자의 값으로 배열을 copy
}

void Dong_Edge::SetPipeStatus(char* pipe)	//pipe의 상태를 Set하는 함수
{
	int len=strlen(pipe);		//인자의 길이를 측정
	Pipestatus=new char[len+1];	//인자의 길이만큼 동적할당
	memset(Pipestatus,0,len+1);	//동적할당한 배열 초기화
	strcpy(Pipestatus,pipe);	//인자의 값으로 배열을 copy
}

void Dong_Edge::SetLossRate1(char* rate)	//열손실율의 값을 Set하는 함수
{
	LossRate=atoi(rate);
}

void Dong_Edge::SetLossRate2(int rate)	//int형 열손실율의 값을 Set하는 함수
{
	LossRate=rate;
}

void Dong_Edge::SetOverlap(int ov)	//Overlap의 값을 Set하는 함수
{
	overlap=ov;
}

void Dong_Edge::SetUseflag(int flag)	//useflag의 값을 Set하는 함수
{
	useflag=flag;
}

void Dong_Edge::SetENext(Dong_Edge* next)		//Dong_Edge의 Next를 Set하는 함수
{
	E_Next=next;
}

void Dong_Edge::SetToDongNext(Dong_Vertex* next)	//To에 해당하는Dong_Vertex와의 연결을 Set하는 함수
{
	toDong_Next=next;
}

void Dong_Edge::SetFromDongNext(Dong_Vertex* next)	//From에 해당하는 Dong_Vertex를 Set하는함수
{
	fromDong_Next=next;
}

char* Dong_Edge::GetGuName()		//해당 동의 구 이름을 Get하는 함수
{
	return GuName;
}

char* Dong_Edge::GetFromDong()	//From에 해당하는 Dong의 이름을 Get하는 함수
{
	return FromDong;
}

char* Dong_Edge::GetToDong()		//To에 해당하는 Dong의 이름을 Get하는 함수
{
	return ToDong;
}

char* Dong_Edge::GetPipeStatus()	//Pipe의 상태를 반환하는 함수
{
	return Pipestatus;
}

int Dong_Edge::GetLossRate()		//열손실율의 값을 Get하는 함수
{
	return LossRate;
}

int Dong_Edge::GetOverlap()		//overlap변수의 값을 get하는 함수
{
	return overlap;
}

int Dong_Edge::GetUseflag()		//useflag의 값을 Get하는 함수
{
	return useflag;
}

Dong_Edge* Dong_Edge::GetENext()		//Dong_Edge의 Next를 Get하는 함수
{
	return E_Next;
}

Dong_Vertex* Dong_Edge::GetToDongNext()	//To에 해당하는Dong_Vertex를 반환하는 Get함수
{
	return toDong_Next;
}

Dong_Vertex* Dong_Edge::GetFromDongNext()	//From에 해당하는 Dong_Vertex를 반환하는 Get함수
{
	return fromDong_Next;
}