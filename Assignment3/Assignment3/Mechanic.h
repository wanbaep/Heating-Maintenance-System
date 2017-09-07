#pragma once

#include<iostream>

using namespace std;

class Mechanic
{
private:
	char* Name;	//정비사 이름
	char* Workplace;	//현재 근무지
	int dist;
	Mechanic* pNext;
public:
	Mechanic(void);	//생성자& 소멸자
	~Mechanic(void);

	//Set함수
	void SetName(char* pname);		//정비사의 이름을 Set하는 함수
	void SetWorkPlace(char* place);	//정비사의 근무지를 Set하는 함수
	void SetDist(int d);			//정비사가 출발지에서 도착지까지의 거리를 Set하는 함수
	void SetNext(Mechanic* next);	//다음 정비사를 Set하는 함수

	//Get함수
	char* GetName();		//정비사의 이름을 Get하는 함수
	char* GetWorkPlace();	//정비사의 근무지를 Get하는 함수
	int GetDist();			//정비사의 이동 거리를 Get하는 함수
	Mechanic* GetNext();	//다음 정비사 Node를 Get하는 함수
};

