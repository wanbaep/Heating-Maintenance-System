#include "MinHeap.h"


MinHeap::MinHeap(void)
{
	heapSize=0;	//0으로 초기화
	capacity=2;	//for Root를 위해서 1이 아닌 2로
	heap=new Dong_Edge*[capacity];//동적할당
	int i=0;
	for(i=0;i<capacity;i++)	//NULL로 초기화
		heap[i]=NULL;
}


MinHeap::~MinHeap(void)
{
	int i=0;	//i는 0
	for(i=0;i<capacity;i++)	//heap의 값들을 NULL로 바꾸어 준다.
	{
		heap[i]=NULL;
		delete heap[i];//동적할당 해제
	}
	delete[] heap;	//동적할당 해제
}


bool MinHeap::IsEmpty()
{
	if(heapSize==0)//heapSize가 0이면 true반환
		return true;
	else
		return false;
}

void MinHeap::Push(Dong_Edge* node)
{
	if(heapSize+1 == capacity)	//0index에 값을 넣지 않기 때문에 1더한 값과 같을 때
	{
		this->ChangeHeapSize(capacity,2*capacity);//용량을 2배로 늘려준다.
		capacity*=2;//수용량 2배로 정정
	}
	int Cur = ++heapSize;//heapSize 증가
	
	//Root가 아닐 때 까지&&시간이 더 클 때 까지
	while(Cur!=1&&(heap[Cur/2]->GetLossRate()>node->GetLossRate()))
	{
		heap[Cur]=heap[Cur/2];	//부모와 자리를 바꾼다.
		Cur/=2;	//부모로 이동
	}
	heap[Cur]=node;//Cur index에 node Push
	
}

Dong_Edge* MinHeap::Pop()
{
	if(IsEmpty())	//비엇나
		return NULL;	//그렇다면 NULL반환
	Dong_Edge* pop=NULL;
	pop=heap[1];	//Root부터 Pop

	Dong_Edge* Last=heap[heapSize];	//말단 Node

	heap[heapSize]=NULL;	//NULL로 초기화한다

	heapSize--;//size를 줄인다.

	int Cur=1;	//Root부터
	int child=2;//왼쪽 자식부터
	while(child<=heapSize)	//Size가 child보다 작거나 같을 때 까지
	{
		//오른쪽 자식의 시간이 더 작으면 
		if(child<heapSize && (heap[child]->GetLossRate()>heap[child+1]->GetLossRate()))
			child++;
		if(Last->GetLossRate()<=heap[child]->GetLossRate())	//Last를 Root부터 자식과 비교
			break;

		heap[Cur]=heap[child];//부모와 자식 자리 바꾼다.
		Cur=child;	//Cur는 child로 이동
		child*=2;	//child는 *2한 값이 된다

	}
	if(heapSize!=0)	//heapSIze가 0이 아니라면
		heap[Cur]=Last;	//Cur자리에 Last삽입
	
	return pop;	//pop Node반환
}

void MinHeap::ChangeHeapSize(int capacity,int doublecap)
{
	int i=0;
	Dong_Edge** temp=NULL;	//heap의 값을 임시 저장할 변수
	temp=new Dong_Edge*[capacity];	//동적할당
	for(i=0;i<capacity;i++)	//초기화
		temp[i]=NULL;

	for(i=0;i<capacity;i++)//temp에 heap의 값들을 저장
		temp[i]=heap[i];

	heap=new Dong_Edge*[doublecap];	//heap을 크기를 2배해서 동적할당
	for(i=0;i<doublecap;i++)	//초기화
		heap[i]=NULL;
	for(i=0;i<capacity;i++)//값을 넣는다.
		heap[i]=temp[i];

}