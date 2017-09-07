#include "MinHeap.h"


MinHeap::MinHeap(void)
{
	heapSize=0;	//0���� �ʱ�ȭ
	capacity=2;	//for Root�� ���ؼ� 1�� �ƴ� 2��
	heap=new Dong_Edge*[capacity];//�����Ҵ�
	int i=0;
	for(i=0;i<capacity;i++)	//NULL�� �ʱ�ȭ
		heap[i]=NULL;
}


MinHeap::~MinHeap(void)
{
	int i=0;	//i�� 0
	for(i=0;i<capacity;i++)	//heap�� ������ NULL�� �ٲپ� �ش�.
	{
		heap[i]=NULL;
		delete heap[i];//�����Ҵ� ����
	}
	delete[] heap;	//�����Ҵ� ����
}


bool MinHeap::IsEmpty()
{
	if(heapSize==0)//heapSize�� 0�̸� true��ȯ
		return true;
	else
		return false;
}

void MinHeap::Push(Dong_Edge* node)
{
	if(heapSize+1 == capacity)	//0index�� ���� ���� �ʱ� ������ 1���� ���� ���� ��
	{
		this->ChangeHeapSize(capacity,2*capacity);//�뷮�� 2��� �÷��ش�.
		capacity*=2;//���뷮 2��� ����
	}
	int Cur = ++heapSize;//heapSize ����
	
	//Root�� �ƴ� �� ����&&�ð��� �� Ŭ �� ����
	while(Cur!=1&&(heap[Cur/2]->GetLossRate()>node->GetLossRate()))
	{
		heap[Cur]=heap[Cur/2];	//�θ�� �ڸ��� �ٲ۴�.
		Cur/=2;	//�θ�� �̵�
	}
	heap[Cur]=node;//Cur index�� node Push
	
}

Dong_Edge* MinHeap::Pop()
{
	if(IsEmpty())	//�����
		return NULL;	//�׷��ٸ� NULL��ȯ
	Dong_Edge* pop=NULL;
	pop=heap[1];	//Root���� Pop

	Dong_Edge* Last=heap[heapSize];	//���� Node

	heap[heapSize]=NULL;	//NULL�� �ʱ�ȭ�Ѵ�

	heapSize--;//size�� ���δ�.

	int Cur=1;	//Root����
	int child=2;//���� �ڽĺ���
	while(child<=heapSize)	//Size�� child���� �۰ų� ���� �� ����
	{
		//������ �ڽ��� �ð��� �� ������ 
		if(child<heapSize && (heap[child]->GetLossRate()>heap[child+1]->GetLossRate()))
			child++;
		if(Last->GetLossRate()<=heap[child]->GetLossRate())	//Last�� Root���� �ڽİ� ��
			break;

		heap[Cur]=heap[child];//�θ�� �ڽ� �ڸ� �ٲ۴�.
		Cur=child;	//Cur�� child�� �̵�
		child*=2;	//child�� *2�� ���� �ȴ�

	}
	if(heapSize!=0)	//heapSIze�� 0�� �ƴ϶��
		heap[Cur]=Last;	//Cur�ڸ��� Last����
	
	return pop;	//pop Node��ȯ
}

void MinHeap::ChangeHeapSize(int capacity,int doublecap)
{
	int i=0;
	Dong_Edge** temp=NULL;	//heap�� ���� �ӽ� ������ ����
	temp=new Dong_Edge*[capacity];	//�����Ҵ�
	for(i=0;i<capacity;i++)	//�ʱ�ȭ
		temp[i]=NULL;

	for(i=0;i<capacity;i++)//temp�� heap�� ������ ����
		temp[i]=heap[i];

	heap=new Dong_Edge*[doublecap];	//heap�� ũ�⸦ 2���ؼ� �����Ҵ�
	for(i=0;i<doublecap;i++)	//�ʱ�ȭ
		heap[i]=NULL;
	for(i=0;i<capacity;i++)//���� �ִ´�.
		heap[i]=temp[i];

}