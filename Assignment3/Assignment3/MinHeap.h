#pragma once
#include"Dong_Edge.h"

class MinHeap
{
private:
	Dong_Edge** heap;	//heap 2���� ������
	int heapSize;	//heap Size ���� ����
	int capacity;	//���� ���� ����
public:
	MinHeap(void);
	~MinHeap(void);

	bool IsEmpty();	//������� Ȯ���ϴ� �Լ�
	void Push(Dong_Edge* node);//Node�� minheap�� Push�ϴ� �Լ�
	Dong_Edge* Pop();	//Node�� ������ Pop�Լ�
	void ChangeHeapSize(int capacity,int doublecap);//Node�� ��������, Size�� Ű��� �Լ�
};

