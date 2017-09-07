#pragma once
#include<iostream>

using namespace std;
class Dong_Vertex;
class Dong_Edge
{
private:
	char* GuName;		//구 이름을 저장할 배열을 가리킬 포인터
	char* FromDong;		//from에 해당하는 dong의 이름을 저장할 배열을 가리킬 포인터
	char* ToDong;		//to에 해당하는 dong의 이름을 저장할 배열을 가리킬 포인터
	char* Pipestatus;	//해당 edge의 pipe 사용 가능 상태 USE인지 BROKEN인지
	int LossRate;		//파이프의 연손실율값을 저장할 변수
	int overlap;	//MST 구성시, Min heap에 반대되는 간선이 이미 추가 되었는지 확인하기 위한 flag
	int useflag;	//MST 구성시, 해당 Edge가 사용되었는지 확인하기 위한 flag
	Dong_Edge* E_Next;		//다음 edge를 가리킬 포인터
	Dong_Vertex* toDong_Next;	//to에 해당하는 dong Node를 가리킬 포인터
	Dong_Vertex* fromDong_Next;	//from에 해당하는 dong Node를 가리킬 포인터
public:
	Dong_Edge(void);	//생성자
	~Dong_Edge(void);	//소멸자

	void SetGuName(char* name);			//해당 동의 구이름을 Set하는 함수
	void SetFromDong(char* fromdong);	//From에 해당하는 Dong의 이름을 Set하는 함수
	void SetToDong(char* todong);		//To에 해당하는 Dong의 이름을 Set하는 함수
	void SetPipeStatus(char* pipe);		//pipe의 상태를 Set하는 함수
	void SetLossRate1(char* rate);		//char 변수형 열손실율의 값을 Set하는 함수
	void SetLossRate2(int rate);		//int 형열손실율의 값을 Set하는 함수
	void SetOverlap(int ov);			//Edge의 중복을 check하는 값을 overlap값을 set하는함수
	void SetUseflag(int flag);			//Edge의 사용여부를 set하는 함수
	void SetENext(Dong_Edge* next);		//Dong_Edge의 Next를 Set하는 함수
	void SetToDongNext(Dong_Vertex* next);	//To에 해당하는Dong_Vertex와의 연결을 Set하는 함수
	void SetFromDongNext(Dong_Vertex* next);	//From에 해당하는 Dong_Vertex와의 연결을 Set하는 함수

	char* GetGuName();		//해당 동의 구 이름을 Get하는 함수
	char* GetFromDong();	//From에 해당하는 Dong의 이름을 Get하는 함수
	char* GetToDong();		//To에 해당하는 Dong의 이름을 Get하는 함수
	char* GetPipeStatus();	//Pipe의 상태를 Get하는 함수
	int GetLossRate();		//열손실율의 값을 Get하는 함수
	int GetOverlap();		//overlap 값을 Get하는 함수
	int GetUseflag();		//useflag 값을 Get하는 함수
	Dong_Edge* GetENext();		//Dong_Edge의 Next를 Get하는 함수
	Dong_Vertex* GetToDongNext();	//To에 해당하는Dong_Vertex를 반환하는 함수
	Dong_Vertex* GetFromDongNext();	//From에 해당하는 Dong_Vertex를 반환하는 함수
};

