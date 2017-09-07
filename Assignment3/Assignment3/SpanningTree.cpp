#include "SpanningTree.h"

#define INFINITE 999999

SpanningTree::SpanningTree(void)	//생성자
{
}


SpanningTree::~SpanningTree(void)	//소멸자
{
}

//////////////////////////////////
/////////MSP를 재구성 하는 경우, 재구성이 불가능한 경우가 있을 수 있으며, 해당 경우에는 PIPEREPAIR를 요청
//////////////////////////////////

void SpanningTree::InitialUseflag(Gu_Vertex* m_pHead)	//하나의 구에 대해서 해당 dong vertex의 edge의 멤버변수 useflag를 0으로 만드는 함수
{
	Dong_Vertex* pDCur=m_pHead->GetDNext();	//Dong Vertex 타입의 변수는 m_pHead에 해당하는 구의 첫번 째 head Dong Vertex를 가리킨다
	Dong_Edge* pDECur=NULL;	//Dong Edge를 가리킬 포인터

	do
	{
		pDECur=pDCur->GetDENext();	//Dong Vertex의 첫번 째 Edge를 가리킨다
		while(pDECur!=NULL)	//Edge가 더이상 없을 때 까지
		{
			pDECur->SetUseflag(0);	//useflag를 0으로 초기화
			pDECur->SetOverlap(0);	//overlapflag를 0으로 초기화
			
			pDECur=pDECur->GetENext();	//다음 Edge로 이동
		}

		pDCur=pDCur->GetDVNext();	//Dong Vertex를 다음으로 이동
	}while(pDCur!=m_pHead->GetDNext());	//원형 List를 모두 탐색 하도록 한다 처음 head가 될 때 까지
	
}

bool SpanningTree::Kruskal(Gu_Vertex* m_pHead)	//MST를 구성하기 위한 Kruskal Algorithm 함수
{
	MinHeap minheap;	//Minheap 타입의 변수 선언

	Dong_Vertex* pDCur=m_pHead->GetDNext();	//Gu_Vertex의 첫 번째 Dong_Vertex는 pDCur
	if(pDCur==NULL)	//dong vetex가 없다면 return
		return false;

	Dong_Edge* pDECur=NULL;	//dong vetex의 edge를 가리킬 포인터
	pDECur=pDCur->GetDENext();	//DongVertex의 Edge를 가리킨다

	//////////////////////edge를 minheap에 push
	Dong_Vertex* pTDCur=NULL;	//To에 해당하는 Dong Vertex를 가리킬 포인터
	Dong_Edge* pTDECur=NULL;	//From에 해당하는 Dong Vertex를 가리킬 포인터

	//1. edge를 minheap에 push
	//2. To에 해당하는 Vertex의 Edge를 찾아서 overlap flag를 1로 해주면서 minheap에 쌍방의 edge중에서 하나의 edge만 push하도록 한다
	do
	{
		while(pDECur!=NULL)	//모든 edge에 대해서 탐색
		{
			/////minheap에 push하고 to에 해당하는 vertex의 edge를 찾아서 overlap flag를 1로
			if(pDECur->GetOverlap()==0&&strcmp(pDECur->GetPipeStatus(),"USE")==0)	//overlap이 안되고, Broken이 아닌 Use가능한 edge에 대해서 minheap에 push
			{
				minheap.Push(pDECur);	//minheap에 push

				/////////////////////////to에 해당하는 vertex의 edge를 찾아서 overlap flag를 1로
				pTDCur=pDECur->GetToDongNext();	//to에 해당하는 vertex로 이동
				pTDECur=pTDCur->GetDENext();		//to에 해당하는 vertex의 edge

				while(pTDECur!=NULL)	//to vertex의 모든 edge를 탐색
				{
					if(strcmp(pDECur->GetFromDong(),pTDECur->GetToDong())==0)	//현재 pDECur의 dongname과, pTDECur의 to dongname을 비교
					{
						pTDECur->SetOverlap(1);	//중복 overlap flag를 1로 해준다.
						break;
					}
					pTDECur=pTDECur->GetENext();	//To에 해당 하는 Edge를 다음으로 이동
				}

			}
			pDECur=pDECur->GetENext();	//다음 Edge를 가리킨다
		}
		if(pDECur==NULL)	//Dong Edge가 없다면
		{
			pDCur=pDCur->GetDVNext();	//dong vertex이동
			pDECur=pDCur->GetDENext();	//edge는 다음 dong vertex의 edge
		}

	}while(pDCur!=m_pHead->GetDNext());	//dong vertex를 한바퀴 돈다.


	/////////////////////////////////////////////
	////Minheap Pop하면서, union, find실행
	////찾은 minimum edge의 useflag를 1로
	/////////////////////////////////////////////

	int edgenum=0;	//MST의 edge 개수를 헤아릴 변수
	int u=0, v=0;	//두개의 집합에 대한 head 즉, 포함관계를 받아올 변수 find 함수로 부터의 return 값
	m_pHead->SetArray(m_pHead->GetDongNum());	//모든 집합을 독립된 각각 하나의 집합으로 초기화

	Dong_Edge* pop=NULL;	//pop한 Dong Edge변수를 가리킬 포인터
	Dong_Vertex* from=NULL;	//Dong Vertex중 from에 해당하는 변수
	Dong_Vertex* to=NULL;	//Dong Vertex중 To에 해당하는 변수

	while(!minheap.IsEmpty())	//minheap안의 edge Node를 모두 pop할 때까지 반복한다.
	{
		pop=minheap.Pop();	//edge를 pop
		from=pop->GetFromDongNext();		//from 에 해당하는 vertex를 가리킨다.
		to=pop->GetToDongNext();			//to 에 해당하는 vertex를 가리킨다.

		u=this->Find(m_pHead->GetArray(),from->GetIndex());	//from에 해당하는 head 즉, 집합관계를 위해 처음 head값 반환
		v=this->Find(m_pHead->GetArray(),to->GetIndex());	//to에 해당하는 head 즉, 집합관계를 위해 처음 head값 반환

		if(u!=v)	//서로의 집합 head 가 다른 즉, 다른집합관계의 경우
		{
			this->Union(m_pHead->GetArray(),u,v);	//하나의 집합으로 나타내도록 한다.
			pop->SetUseflag(1);		//찾은 edge의 사용 여부를 set하도록한다(1==사용한다는 의미)
			edgenum++;				//edge 개수 증가
		}

	}
	
	////////////////////////////////////////////////////
	//3. To에 해당하는 Node의 edge중에서 to에 Edge의 from에 해당하는 edge 의 use flag=1, overlap flag를 0으로
	////////////////////////////////////////////////////

	pDCur=m_pHead->GetDNext();	//pDCur는 head Dong_Vertex를 가리킨다.
	pDECur=pDCur->GetDENext();	//pDECur는 Dong_Vertex의 edge를 가리킨다.
	
	do
	{
		while(pDECur!=NULL)	//모든 Edge에 대해서 이동하며 탐색
		{
			////////////useflag가 1인 edge와 대조를 이루는 edge를 찾아서 useflag를 1로 set한다 overlap은 0으로
			if(pDECur->GetUseflag()==1)	//useflag가 1인 edge를 찾는다
			{
				pTDCur=pDECur->GetToDongNext();	//to에 해당하는 vertex로 이동
				pTDECur=pTDCur->GetDENext();		//to에 해당하는 vertex의 edge로 이동

				while(pTDECur!=NULL)	//to vertex의 모든 edge를 탐색
				{
					///////////
					if(strcmp(pDECur->GetFromDong(),pTDECur->GetToDong())==0)	//현재 pDECur의 dongname과, pTDECur의 to dongname을 비교
					{
						pTDECur->SetUseflag(1);	//useflag를 1로 해준다. (대조되는 edge를 찾은 것이기 때문에)
						pTDECur->SetOverlap(0);	//중복 overlap flag를 0으로 해준다.
						break;
					}

					pTDECur=pTDECur->GetENext();	//다음 Edge로 이동
				}
			}

			if(pDECur->GetOverlap()==1)	//중복 처리한 edge들에 대해서 0으로 초기화
			{

				pDECur->SetOverlap(0);	//overlap을 0으로 만든다
			}
			pDECur=pDECur->GetENext();
		}

		if(pDECur==NULL)
		{
			pDCur=pDCur->GetDVNext();	//dong vertex이동
			pDECur=pDCur->GetDENext();	//edge는 다음 dong vertex의 edge
		}

	}while(pDCur!=m_pHead->GetDNext());	//원형 리스트 한바퀴 돌기

	//////minheap이 empty인데, edgenum이 vertex개수 - 1 개가 아닌 경우 return false반환
	if(edgenum!=m_pHead->GetDongNum()-1)	//MST가 이루어 지지 않은 경우
		return false;


	return true;	//Mst를 구성하였기 때문에 return true
	
}

int SpanningTree::Find(int* arr, int x)	//Gu_Vertex안의 집합을 나타내는 array, Dong_Vertex의 index를 나타내는 값을 인자로 넘겨준다
{
	if(arr[x]==x)	//배열의 index와 값이 같은 경우, 해당 index를 반환
		return x;
	else			//배열의 index와 값이 다른 경우, 배열의 값을 인자로 다시 Find함수 호출
		return this->Find(arr,arr[x]);
}

void SpanningTree::Union(int* arr, int u, int v)	//현재 집합을 나타내는 배열의 위치를 MST에만 한정시킬 지, Gu_Vertex의 멤버 변수로 할 지 미정.
{
	if(u < v)		// 작은 값이 집합을 표시하도록
		arr[v]=u;	//더 작은 값을 해당 index의 배열 값으로 set
	else if(u > v)	//반대의 경우
		arr[u]=v;
}

Gu_Vertex* SpanningTree::MinDistance(LinkedList& list)	//list중에서 방문하지 않고, 제일 작은 cost를 가지는 Node를 반환
{
	int min=INFINITE;	//min의 값을 999999로 정의 해 놓은 INFINITE값으로 선언

	Gu_Vertex* pCur=list.GetGVHead();	//pCur는 list의 Gu Vertex의 head를 가리킨다
	Gu_Vertex* minNode=NULL;			//cost값이 최소인 Gu Vertex를 가리킬 포인터
	
	while(pCur!=NULL)	//List를 모두 탐색
	{
		if(pCur->GetVisit()==false && pCur->GetCost()<=min)	//visit하지 않았고, cost값이 제일 작은 Gu Vertex라면
		{
			min=pCur->GetCost();	//최소값을 해당 Gu Vertex의 값으로 교체
			minNode=pCur;		//Cost값이 최소인 Gu Vertex를 가리킨다
		}
		pCur=pCur->GetGVNext();	//다음 Gu Vertex로 이동
	}

	return minNode;	//cost가 최소인 Gu Vertex 반환
}

int SpanningTree::Dijkstra(LinkedList& list,Gu_Vertex* source, Gu_Vertex* destination)	//출발 Node source와 도착 Node destination을 받아서 해당 최단거리를 반환한다
{
	//1. list의 모든 Node의 cost, visit를 초기화
	Gu_Vertex* pCur=list.GetGVHead();

	while(pCur!=NULL)	//Gu Vertex의 모든 list탐색과 cost, visit에 대해서 초기화
	{
		pCur->SetCost(INFINITE);		//cost값을 무한대로 초기화
		pCur->SetVisit(false);	//visit값을 false로 초기화

		pCur=pCur->GetGVNext();	//다음으로 이동
	}

	//source 시작점이 되는 Node의 cost를 0으로 초기화
	source->SetCost(0);

	//int Vertexnum=0;	//vertex의 개수를 헤아리기 위한 작업
	pCur=list.GetGVHead();	//pCur는 Gu Head를 가리킨다
	Gu_Vertex* pUCur=NULL;	//Update 될 Gu Vertex를 가리킬 포인터
	Gu_Edge* pECur=NULL;	//Gu Edge를 가리킬 포인터

	int presentedge=0;	//현재 Edge의 개수
	int count;			//count
	
	for(count=0; count<list.GetGVNum()-1;count++)	//구의 개수 -1 번 만큼 반복문 실행
	{
		pUCur=MinDistance(list);	//Min Distance를 갖는 Gu Vertex를 받아온다 Min Distance함수로 부터

		pUCur->SetVisit(true);		//해당 Gu Vertex에 대해서 방문 한 표시를 한다
		pECur=pUCur->GetGENext();	//pECur는 pUCur의 간선을 가리킨다

		pCur=list.GetGVHead();		//list의 head를 가리킨다
		while(pCur!=NULL)
		{
			///////1. pCur와 pUCur 사이에 edge가 존재하는지에 대해서 파악한다

			pECur=pUCur->GetGENext();	//pECur는 pUCur의 간선을 가리킨다
			while(pECur!=NULL)	//모든 간선 탐색
			{
				if(strcmp(pECur->GetToGu(),pCur->GetGuName())==0)	//from은 pUCur과 일치하기 때문에, to 에 대한 Gu의 이름만 비교
				{
					break;	//pECur는 pUCur과 pCur를 연결하는 edge가 된다.
				}
				pECur=pECur->GetENext();
			}
			//pECur이 NULL이면, pCur에 대한 간선이 존재하지 않는다는 뜻

			///////2. (1) 해당 Node의 edge가 존재하고, (2) pCur Node의 visit가 false이고,
			///////   (3) pUCur의 cost가 INFINITE가 아니고, (4) pUCur의 cost와 edge를 더한 값<pCur의 cost이면 pCur의 cost update
			if(pCur->GetVisit()==false && pECur!=NULL && pUCur->GetCost()!=INFINITE && (pUCur->GetCost()+pECur->GetDist())<pCur->GetCost())
			{
				pCur->SetCost(pUCur->GetCost()+pECur->GetDist());	//pCur의 cost를 새로 update한다
			}

			pCur=pCur->GetGVNext();	//pCur는 다음 Gu Vertex로 이동
		}
	}

	return destination->GetCost();	//도착지 까지의 Cost값을 반환

}

stack SpanningTree::BackTrace(LinkedList& list, Gu_Vertex* source, Gu_Vertex* destination)	//이동경로 역추적 함수 for Dijkstra
{
	stack sp;	//stack type의 변수 선언

	Gu_Vertex* pCur= destination;	//pCur는 destination Gu Vertex 를 가리킨다
	Gu_Edge* pECur=NULL;			//Gu 의 Edge를 가리킬 포인터
	Gu_Vertex* pCom=NULL;			//Destination으로 부터, source로 이동하면서 어느 방향으로 이동했는지 비교할 포인터

	////////0. destination을 stack에 push
	sp.Push(pCur);

	int count=0;	//Gu Vertex의 개수와 비교해서 반복문 실행을 조절할 변수

	for(count=0; count<list.GetGVNum();count++)	//최대 Gu_Vertex 개수만큼 Loop를 실행해야 한다
	{
		pECur=pCur->GetGENext();	//Edge의 to에 해당하는 Gu Vertex를 가리킨다
		while(pECur!=NULL)
		{
			//Edge를 하나씩 찾아서 to에 해당하는 Node와 비교
			pCom=pECur->GetToGuNext();	//to에 해당하는 Gu를 가리킨다

			////////1. pCur를 destination으로 부터 시작해서 Edge들을 모두 찾아서  pCur의 cost - edge가 toGu의 cost와 일치하는 Gu_Vertex로 이동
			if(pCur->GetCost()-pECur->GetDist()==pCom->GetCost())
			{
				////////2. 일치하는 Gu_Vertex의 Node를 stack 에 push,
				pCur=pCom;
				sp.Push(pCur);	//stack에 해당 Gu Vertex를 push
				break;	//Gu Vertex를 바꿔주기 위해서 반복문 종료
			}

			pECur=pECur->GetENext();	//다음 Gu Edge로 이동
		}

		////////3. 해당 과정 반복중 pCur가 source가 되면 stack에 넣고 종료
		if(pCur==source)	//반복 과정중에서 pCur가 source가 되면, stack 반환
			return sp;	////////4. 이후 stack 반환 해서 파일에 출력 가능!

	}
	
	return sp;	//모든 제어 경로에서 값을 반환
}