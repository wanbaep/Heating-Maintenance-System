#pragma once
#include"Dong_Edge.h"

class MinHeap
{
private:
	Dong_Edge** heap;	//heap 2차원 포인터
	int heapSize;	//heap Size 저장 변수
	int capacity;	//수용 가능 변수
public:
	MinHeap(void);
	~MinHeap(void);

	bool IsEmpty();	//비엇는지 확인하는 함수
	void Push(Dong_Edge* node);//Node를 minheap에 Push하는 함수
	Dong_Edge* Pop();	//Node를 꺼내는 Pop함수
	void ChangeHeapSize(int capacity,int doublecap);//Node가 많아지면, Size를 키우는 함수
};

