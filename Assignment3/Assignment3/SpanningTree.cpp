#include "SpanningTree.h"

#define INFINITE 999999

SpanningTree::SpanningTree(void)	//������
{
}


SpanningTree::~SpanningTree(void)	//�Ҹ���
{
}

//////////////////////////////////
/////////MSP�� �籸�� �ϴ� ���, �籸���� �Ұ����� ��찡 ���� �� ������, �ش� ��쿡�� PIPEREPAIR�� ��û
//////////////////////////////////

void SpanningTree::InitialUseflag(Gu_Vertex* m_pHead)	//�ϳ��� ���� ���ؼ� �ش� dong vertex�� edge�� ������� useflag�� 0���� ����� �Լ�
{
	Dong_Vertex* pDCur=m_pHead->GetDNext();	//Dong Vertex Ÿ���� ������ m_pHead�� �ش��ϴ� ���� ù�� ° head Dong Vertex�� ����Ų��
	Dong_Edge* pDECur=NULL;	//Dong Edge�� ����ų ������

	do
	{
		pDECur=pDCur->GetDENext();	//Dong Vertex�� ù�� ° Edge�� ����Ų��
		while(pDECur!=NULL)	//Edge�� ���̻� ���� �� ����
		{
			pDECur->SetUseflag(0);	//useflag�� 0���� �ʱ�ȭ
			pDECur->SetOverlap(0);	//overlapflag�� 0���� �ʱ�ȭ
			
			pDECur=pDECur->GetENext();	//���� Edge�� �̵�
		}

		pDCur=pDCur->GetDVNext();	//Dong Vertex�� �������� �̵�
	}while(pDCur!=m_pHead->GetDNext());	//���� List�� ��� Ž�� �ϵ��� �Ѵ� ó�� head�� �� �� ����
	
}

bool SpanningTree::Kruskal(Gu_Vertex* m_pHead)	//MST�� �����ϱ� ���� Kruskal Algorithm �Լ�
{
	MinHeap minheap;	//Minheap Ÿ���� ���� ����

	Dong_Vertex* pDCur=m_pHead->GetDNext();	//Gu_Vertex�� ù ��° Dong_Vertex�� pDCur
	if(pDCur==NULL)	//dong vetex�� ���ٸ� return
		return false;

	Dong_Edge* pDECur=NULL;	//dong vetex�� edge�� ����ų ������
	pDECur=pDCur->GetDENext();	//DongVertex�� Edge�� ����Ų��

	//////////////////////edge�� minheap�� push
	Dong_Vertex* pTDCur=NULL;	//To�� �ش��ϴ� Dong Vertex�� ����ų ������
	Dong_Edge* pTDECur=NULL;	//From�� �ش��ϴ� Dong Vertex�� ����ų ������

	//1. edge�� minheap�� push
	//2. To�� �ش��ϴ� Vertex�� Edge�� ã�Ƽ� overlap flag�� 1�� ���ָ鼭 minheap�� �ֹ��� edge�߿��� �ϳ��� edge�� push�ϵ��� �Ѵ�
	do
	{
		while(pDECur!=NULL)	//��� edge�� ���ؼ� Ž��
		{
			/////minheap�� push�ϰ� to�� �ش��ϴ� vertex�� edge�� ã�Ƽ� overlap flag�� 1��
			if(pDECur->GetOverlap()==0&&strcmp(pDECur->GetPipeStatus(),"USE")==0)	//overlap�� �ȵǰ�, Broken�� �ƴ� Use������ edge�� ���ؼ� minheap�� push
			{
				minheap.Push(pDECur);	//minheap�� push

				/////////////////////////to�� �ش��ϴ� vertex�� edge�� ã�Ƽ� overlap flag�� 1��
				pTDCur=pDECur->GetToDongNext();	//to�� �ش��ϴ� vertex�� �̵�
				pTDECur=pTDCur->GetDENext();		//to�� �ش��ϴ� vertex�� edge

				while(pTDECur!=NULL)	//to vertex�� ��� edge�� Ž��
				{
					if(strcmp(pDECur->GetFromDong(),pTDECur->GetToDong())==0)	//���� pDECur�� dongname��, pTDECur�� to dongname�� ��
					{
						pTDECur->SetOverlap(1);	//�ߺ� overlap flag�� 1�� ���ش�.
						break;
					}
					pTDECur=pTDECur->GetENext();	//To�� �ش� �ϴ� Edge�� �������� �̵�
				}

			}
			pDECur=pDECur->GetENext();	//���� Edge�� ����Ų��
		}
		if(pDECur==NULL)	//Dong Edge�� ���ٸ�
		{
			pDCur=pDCur->GetDVNext();	//dong vertex�̵�
			pDECur=pDCur->GetDENext();	//edge�� ���� dong vertex�� edge
		}

	}while(pDCur!=m_pHead->GetDNext());	//dong vertex�� �ѹ��� ����.


	/////////////////////////////////////////////
	////Minheap Pop�ϸ鼭, union, find����
	////ã�� minimum edge�� useflag�� 1��
	/////////////////////////////////////////////

	int edgenum=0;	//MST�� edge ������ ��Ƹ� ����
	int u=0, v=0;	//�ΰ��� ���տ� ���� head ��, ���԰��踦 �޾ƿ� ���� find �Լ��� ������ return ��
	m_pHead->SetArray(m_pHead->GetDongNum());	//��� ������ ������ ���� �ϳ��� �������� �ʱ�ȭ

	Dong_Edge* pop=NULL;	//pop�� Dong Edge������ ����ų ������
	Dong_Vertex* from=NULL;	//Dong Vertex�� from�� �ش��ϴ� ����
	Dong_Vertex* to=NULL;	//Dong Vertex�� To�� �ش��ϴ� ����

	while(!minheap.IsEmpty())	//minheap���� edge Node�� ��� pop�� ������ �ݺ��Ѵ�.
	{
		pop=minheap.Pop();	//edge�� pop
		from=pop->GetFromDongNext();		//from �� �ش��ϴ� vertex�� ����Ų��.
		to=pop->GetToDongNext();			//to �� �ش��ϴ� vertex�� ����Ų��.

		u=this->Find(m_pHead->GetArray(),from->GetIndex());	//from�� �ش��ϴ� head ��, ���հ��踦 ���� ó�� head�� ��ȯ
		v=this->Find(m_pHead->GetArray(),to->GetIndex());	//to�� �ش��ϴ� head ��, ���հ��踦 ���� ó�� head�� ��ȯ

		if(u!=v)	//������ ���� head �� �ٸ� ��, �ٸ����հ����� ���
		{
			this->Union(m_pHead->GetArray(),u,v);	//�ϳ��� �������� ��Ÿ������ �Ѵ�.
			pop->SetUseflag(1);		//ã�� edge�� ��� ���θ� set�ϵ����Ѵ�(1==����Ѵٴ� �ǹ�)
			edgenum++;				//edge ���� ����
		}

	}
	
	////////////////////////////////////////////////////
	//3. To�� �ش��ϴ� Node�� edge�߿��� to�� Edge�� from�� �ش��ϴ� edge �� use flag=1, overlap flag�� 0����
	////////////////////////////////////////////////////

	pDCur=m_pHead->GetDNext();	//pDCur�� head Dong_Vertex�� ����Ų��.
	pDECur=pDCur->GetDENext();	//pDECur�� Dong_Vertex�� edge�� ����Ų��.
	
	do
	{
		while(pDECur!=NULL)	//��� Edge�� ���ؼ� �̵��ϸ� Ž��
		{
			////////////useflag�� 1�� edge�� ������ �̷�� edge�� ã�Ƽ� useflag�� 1�� set�Ѵ� overlap�� 0����
			if(pDECur->GetUseflag()==1)	//useflag�� 1�� edge�� ã�´�
			{
				pTDCur=pDECur->GetToDongNext();	//to�� �ش��ϴ� vertex�� �̵�
				pTDECur=pTDCur->GetDENext();		//to�� �ش��ϴ� vertex�� edge�� �̵�

				while(pTDECur!=NULL)	//to vertex�� ��� edge�� Ž��
				{
					///////////
					if(strcmp(pDECur->GetFromDong(),pTDECur->GetToDong())==0)	//���� pDECur�� dongname��, pTDECur�� to dongname�� ��
					{
						pTDECur->SetUseflag(1);	//useflag�� 1�� ���ش�. (�����Ǵ� edge�� ã�� ���̱� ������)
						pTDECur->SetOverlap(0);	//�ߺ� overlap flag�� 0���� ���ش�.
						break;
					}

					pTDECur=pTDECur->GetENext();	//���� Edge�� �̵�
				}
			}

			if(pDECur->GetOverlap()==1)	//�ߺ� ó���� edge�鿡 ���ؼ� 0���� �ʱ�ȭ
			{

				pDECur->SetOverlap(0);	//overlap�� 0���� �����
			}
			pDECur=pDECur->GetENext();
		}

		if(pDECur==NULL)
		{
			pDCur=pDCur->GetDVNext();	//dong vertex�̵�
			pDECur=pDCur->GetDENext();	//edge�� ���� dong vertex�� edge
		}

	}while(pDCur!=m_pHead->GetDNext());	//���� ����Ʈ �ѹ��� ����

	//////minheap�� empty�ε�, edgenum�� vertex���� - 1 ���� �ƴ� ��� return false��ȯ
	if(edgenum!=m_pHead->GetDongNum()-1)	//MST�� �̷�� ���� ���� ���
		return false;


	return true;	//Mst�� �����Ͽ��� ������ return true
	
}

int SpanningTree::Find(int* arr, int x)	//Gu_Vertex���� ������ ��Ÿ���� array, Dong_Vertex�� index�� ��Ÿ���� ���� ���ڷ� �Ѱ��ش�
{
	if(arr[x]==x)	//�迭�� index�� ���� ���� ���, �ش� index�� ��ȯ
		return x;
	else			//�迭�� index�� ���� �ٸ� ���, �迭�� ���� ���ڷ� �ٽ� Find�Լ� ȣ��
		return this->Find(arr,arr[x]);
}

void SpanningTree::Union(int* arr, int u, int v)	//���� ������ ��Ÿ���� �迭�� ��ġ�� MST���� ������ų ��, Gu_Vertex�� ��� ������ �� �� ����.
{
	if(u < v)		// ���� ���� ������ ǥ���ϵ���
		arr[v]=u;	//�� ���� ���� �ش� index�� �迭 ������ set
	else if(u > v)	//�ݴ��� ���
		arr[u]=v;
}

Gu_Vertex* SpanningTree::MinDistance(LinkedList& list)	//list�߿��� �湮���� �ʰ�, ���� ���� cost�� ������ Node�� ��ȯ
{
	int min=INFINITE;	//min�� ���� 999999�� ���� �� ���� INFINITE������ ����

	Gu_Vertex* pCur=list.GetGVHead();	//pCur�� list�� Gu Vertex�� head�� ����Ų��
	Gu_Vertex* minNode=NULL;			//cost���� �ּ��� Gu Vertex�� ����ų ������
	
	while(pCur!=NULL)	//List�� ��� Ž��
	{
		if(pCur->GetVisit()==false && pCur->GetCost()<=min)	//visit���� �ʾҰ�, cost���� ���� ���� Gu Vertex���
		{
			min=pCur->GetCost();	//�ּҰ��� �ش� Gu Vertex�� ������ ��ü
			minNode=pCur;		//Cost���� �ּ��� Gu Vertex�� ����Ų��
		}
		pCur=pCur->GetGVNext();	//���� Gu Vertex�� �̵�
	}

	return minNode;	//cost�� �ּ��� Gu Vertex ��ȯ
}

int SpanningTree::Dijkstra(LinkedList& list,Gu_Vertex* source, Gu_Vertex* destination)	//��� Node source�� ���� Node destination�� �޾Ƽ� �ش� �ִܰŸ��� ��ȯ�Ѵ�
{
	//1. list�� ��� Node�� cost, visit�� �ʱ�ȭ
	Gu_Vertex* pCur=list.GetGVHead();

	while(pCur!=NULL)	//Gu Vertex�� ��� listŽ���� cost, visit�� ���ؼ� �ʱ�ȭ
	{
		pCur->SetCost(INFINITE);		//cost���� ���Ѵ�� �ʱ�ȭ
		pCur->SetVisit(false);	//visit���� false�� �ʱ�ȭ

		pCur=pCur->GetGVNext();	//�������� �̵�
	}

	//source �������� �Ǵ� Node�� cost�� 0���� �ʱ�ȭ
	source->SetCost(0);

	//int Vertexnum=0;	//vertex�� ������ ��Ƹ��� ���� �۾�
	pCur=list.GetGVHead();	//pCur�� Gu Head�� ����Ų��
	Gu_Vertex* pUCur=NULL;	//Update �� Gu Vertex�� ����ų ������
	Gu_Edge* pECur=NULL;	//Gu Edge�� ����ų ������

	int presentedge=0;	//���� Edge�� ����
	int count;			//count
	
	for(count=0; count<list.GetGVNum()-1;count++)	//���� ���� -1 �� ��ŭ �ݺ��� ����
	{
		pUCur=MinDistance(list);	//Min Distance�� ���� Gu Vertex�� �޾ƿ´� Min Distance�Լ��� ����

		pUCur->SetVisit(true);		//�ش� Gu Vertex�� ���ؼ� �湮 �� ǥ�ø� �Ѵ�
		pECur=pUCur->GetGENext();	//pECur�� pUCur�� ������ ����Ų��

		pCur=list.GetGVHead();		//list�� head�� ����Ų��
		while(pCur!=NULL)
		{
			///////1. pCur�� pUCur ���̿� edge�� �����ϴ����� ���ؼ� �ľ��Ѵ�

			pECur=pUCur->GetGENext();	//pECur�� pUCur�� ������ ����Ų��
			while(pECur!=NULL)	//��� ���� Ž��
			{
				if(strcmp(pECur->GetToGu(),pCur->GetGuName())==0)	//from�� pUCur�� ��ġ�ϱ� ������, to �� ���� Gu�� �̸��� ��
				{
					break;	//pECur�� pUCur�� pCur�� �����ϴ� edge�� �ȴ�.
				}
				pECur=pECur->GetENext();
			}
			//pECur�� NULL�̸�, pCur�� ���� ������ �������� �ʴ´ٴ� ��

			///////2. (1) �ش� Node�� edge�� �����ϰ�, (2) pCur Node�� visit�� false�̰�,
			///////   (3) pUCur�� cost�� INFINITE�� �ƴϰ�, (4) pUCur�� cost�� edge�� ���� ��<pCur�� cost�̸� pCur�� cost update
			if(pCur->GetVisit()==false && pECur!=NULL && pUCur->GetCost()!=INFINITE && (pUCur->GetCost()+pECur->GetDist())<pCur->GetCost())
			{
				pCur->SetCost(pUCur->GetCost()+pECur->GetDist());	//pCur�� cost�� ���� update�Ѵ�
			}

			pCur=pCur->GetGVNext();	//pCur�� ���� Gu Vertex�� �̵�
		}
	}

	return destination->GetCost();	//������ ������ Cost���� ��ȯ

}

stack SpanningTree::BackTrace(LinkedList& list, Gu_Vertex* source, Gu_Vertex* destination)	//�̵���� ������ �Լ� for Dijkstra
{
	stack sp;	//stack type�� ���� ����

	Gu_Vertex* pCur= destination;	//pCur�� destination Gu Vertex �� ����Ų��
	Gu_Edge* pECur=NULL;			//Gu �� Edge�� ����ų ������
	Gu_Vertex* pCom=NULL;			//Destination���� ����, source�� �̵��ϸ鼭 ��� �������� �̵��ߴ��� ���� ������

	////////0. destination�� stack�� push
	sp.Push(pCur);

	int count=0;	//Gu Vertex�� ������ ���ؼ� �ݺ��� ������ ������ ����

	for(count=0; count<list.GetGVNum();count++)	//�ִ� Gu_Vertex ������ŭ Loop�� �����ؾ� �Ѵ�
	{
		pECur=pCur->GetGENext();	//Edge�� to�� �ش��ϴ� Gu Vertex�� ����Ų��
		while(pECur!=NULL)
		{
			//Edge�� �ϳ��� ã�Ƽ� to�� �ش��ϴ� Node�� ��
			pCom=pECur->GetToGuNext();	//to�� �ش��ϴ� Gu�� ����Ų��

			////////1. pCur�� destination���� ���� �����ؼ� Edge���� ��� ã�Ƽ�  pCur�� cost - edge�� toGu�� cost�� ��ġ�ϴ� Gu_Vertex�� �̵�
			if(pCur->GetCost()-pECur->GetDist()==pCom->GetCost())
			{
				////////2. ��ġ�ϴ� Gu_Vertex�� Node�� stack �� push,
				pCur=pCom;
				sp.Push(pCur);	//stack�� �ش� Gu Vertex�� push
				break;	//Gu Vertex�� �ٲ��ֱ� ���ؼ� �ݺ��� ����
			}

			pECur=pECur->GetENext();	//���� Gu Edge�� �̵�
		}

		////////3. �ش� ���� �ݺ��� pCur�� source�� �Ǹ� stack�� �ְ� ����
		if(pCur==source)	//�ݺ� �����߿��� pCur�� source�� �Ǹ�, stack ��ȯ
			return sp;	////////4. ���� stack ��ȯ �ؼ� ���Ͽ� ��� ����!

	}
	
	return sp;	//��� ���� ��ο��� ���� ��ȯ
}