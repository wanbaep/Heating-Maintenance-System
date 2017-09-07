#include "AdjacencyList.h"


AdjacencyList::AdjacencyList(void)	//생성자
{
}


AdjacencyList::~AdjacencyList(void)	//소멸자
{
}


bool AdjacencyList::InsertGuEdge(LinkedList &list, Gu_Edge* pnode)		//Gu에 대한 인접리스트를 Insert하는 함수
{
	Gu_Vertex* pVCur=list.GetGVHead();

	Gu_Edge* pNew=new Gu_Edge();	//동적할당 후 삽입할 Node의 값을 Set한다.
	pNew->SetFromGu(pnode->GetFromGu());
	pNew->SetToGu(pnode->GetToGu());
	pNew->SetDist2(pnode->GetDist());
	
	Gu_Vertex* pFVCur=NULL;	//From의 구를 가리키는 포인터
	Gu_Vertex* pTVCur=NULL;	//To의 구를 가리키는 포인터
	int count=0;

	while(pVCur!=NULL)
	{
		if(strcmp(pVCur->GetGuName(),pNew->GetFromGu())==0)	//From 구를 찾는다.
		{
			pFVCur=pVCur;
			count++;
		}
		if(strcmp(pVCur->GetGuName(),pNew->GetToGu())==0)	//To 구를 찾는다.
		{
			pTVCur=pVCur;
			count++;
		}
		if(count==2)	//From 구와 To 구를 모두 찾았으면
			break;

		pVCur=pVCur->GetGVNext();
	}
	if(pVCur==NULL)	//From 구와 To 구를 찾지 못한 경우 count가 2가 되지 않아서, pVCur는 NULL이 되면 실패 반환
		return false;

	if(pFVCur->GetGENext()==NULL)	//From구에 대해서 먼저 연결
	{
		pFVCur->SetGENext(pNew);
		pNew->SetToGuNext(pTVCur);	//pNew와 To 구에 대해서 연결
	}
	else
	{
		Gu_Edge* pECur=pFVCur->GetGENext();

		while(pECur->GetENext()!=NULL)	//From 구에서 연결될 위치를 찾는다.
		{
			pECur=pECur->GetENext();
		}
		pECur->SetENext(pNew);
		pNew->SetToGuNext(pTVCur);	//pNew와 To 구에 대해서 연결
	}

	return true;
}

bool AdjacencyList::InsertDongEdge(LinkedList &list, Dong_Edge* pnode)	//Dong에 대한 인접리스트를 Insert하는 함수
{
	Gu_Vertex* pGCur=list.FindGu(pnode->GetGuName());

	if(pGCur==NULL)	//pGCur는 pnode의 구에 해당하는 Vertex_Node이다.
		return false;
	
	Dong_Edge* pNew=new Dong_Edge();		//새로운 Dong Edge에 대해서 동적할당
	pNew->SetGuName(pnode->GetGuName());		//멤버 변수들을 Set하도록 한다.
	pNew->SetFromDong(pnode->GetFromDong());	//from Dong의 이름에 대해서 set
	pNew->SetToDong(pnode->GetToDong());	//to Dong의 이름에 대해서 set
	pNew->SetLossRate2(pnode->GetLossRate());	//열 손실율을 Set하는 함수
	pNew->SetPipeStatus(pnode->GetPipeStatus());	//pipe 상태를 Set하는 함수
	//////overlap과 useflag는 0으로 초기화 되기 때문에 따로 초기화 하지 않는다

	Dong_Vertex* pDCur=pGCur->GetDNext();	//Gu Vertex의 처음 Dong Vertex를 가리킬 포인터
	Dong_Vertex* D_Head=pDCur;		//D_Head는 Gu Vertex의 처음 Dong Vertex를 가리키는 포인터
	Dong_Vertex* pDFCur=NULL;		//From에 해당하는 Dong Vertex를 가리킬 포인터
	Dong_Vertex* pDTCur=NULL;		//To에 해당하는 Dong Vertex를 가리킬 포인터

	do
	{
		if(strcmp(pDCur->GetDongName(),pNew->GetFromDong())==0)	//From에 해당하는 Dong을 찾는다.
			pDFCur=pDCur;

		if(strcmp(pDCur->GetDongName(),pNew->GetToDong())==0)	//To에 해당하는 Dong을 찾는다.
			pDTCur=pDCur;

		pDCur=pDCur->GetDVNext();

	}while(pDCur!=D_Head);
	
	/////////////////pDFCur에서 edge Node(pNew)를 연결한다
	Dong_Edge* pECur=pDFCur->GetDENext();	//pECur는 pDFCur에서 Dong Edge를 가리킨다.

	if(pECur==NULL)	//Dong Edge가 하나도 없는 경우
	{
		pDFCur->SetDENext(pNew);
		pNew->SetToDongNext(pDTCur);	//pNew에서 toDong에 해당하는 pDTCur로 연결하기
		pNew->SetFromDongNext(pDFCur);//pNew에서 fromDong에 해당하는 pDFCur로 연결하기
		return true;
	}

	//Dong Edge가 있는 경우
	while(pECur->GetENext()!=NULL)	//Edge가 없을 때 까지 이동
	{
		pECur=pECur->GetENext();
	}
	pECur->SetENext(pNew);	//마지막 Edge Node와 Insert된 Edge Node 연결
	pNew->SetToDongNext(pDTCur);		//pNew에서 toDong에 해당하는 pDTCur로 연결하기
	pNew->SetFromDongNext(pDFCur);	//pNew에서 fromDong에 해당하는 pDFCur로 연결하기

	return true;
}