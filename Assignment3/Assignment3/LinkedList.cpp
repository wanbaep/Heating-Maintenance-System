#include "LinkedList.h"


LinkedList::LinkedList(void)	//생성자
{
	GVNum=0;	//변수 초기화
	m_GVHead=NULL;
	m_MHead=NULL;
}

LinkedList::~LinkedList(void)	//소멸자
{
	Gu_Vertex* pCur=m_GVHead;	//pCur는 Gu_Vertex의 Head를 가리킨다.
	Dong_Vertex* pDCur=NULL;	//pDCur는 Gu에 속한 Dong들을 가리킬 포인터이다.
	Dong_Vertex* pDelD=NULL;	//pDelD는 동적할당 해제할 Dong들을 가리키는 포인터
	Dong_Edge* pDECur=NULL;		//pDECur는 Dong에 속한 Dong Edge를 가리킬 포인터
	Dong_Edge* pDelDE=NULL;		//pDelDE는 동적할당 해제할 Dong Edge를 가리킬 포인터
	
	Gu_Edge* pGECur=NULL;	//Gu의 Edge를 가리킬 포인터
	Gu_Edge* pDelGE=NULL;	//동적할당 해제할 Gu Edge를 가리킬 포인터

	Mechanic* pMCur=m_MHead;	//정비사 list의 head를 가리킨다

	/////////////////////////////////////////////////////////////////////////////////1. Dong_Edge에 대한 동적할당 후에 Dong_Vertex에 대한 동적할당
	while(pCur!=NULL)	//모든 Gu에 대해서 탐색
	{
		pDCur=pCur->GetDNext();	//Gu_Vertex의 Dong_Vertex를 가리킨다.
		if(pDCur!=NULL)	//Dong_Vertex가 존재한다면
		{
			do	//Dong의 연결이 종료 될 때 까지
			{
				pDCur=pDCur->GetDVNext();
			}while(pDCur->GetDVNext()!=pCur->GetDNext());
			//pDCur는 head가 되는 Dong Node의 마지막을 가리킨다
			pDCur->SetDVNext(NULL);	//Dong Vertex list를 선형 List로 만든다

			pDCur=pCur->GetDNext();
			while(pDCur!=NULL)	//Dong Vertex가 없을 때 까지
			{
				pDelD=pDCur;
				pDECur=pDCur->GetDENext();	//Dong Vertex의 Edge Node를 가리킨다
				if(pDECur!=NULL)	//pDECur이 존재한다면
				{
					while(pDECur!=NULL)	//pDECur이 Null일 때 까지
					{
						pDelDE=pDECur;	//pDelDE는 현재 pDECur를 가리킨다(삭제할 Node)
						pDECur=pDECur->GetENext();	//pDECur는 다음 Edge 를 가리킨다
						delete pDelDE;	//Dong Edge에 대해서 동적할당 해제
					}
				}

				pDCur=pDCur->GetDVNext();	//pDCur는 다음 Node로 이동
				delete pDelD;	//pDelD 동적할당 해제
			}
		}
		pCur=pCur->GetGVNext();
	}

	///////////////////////////////////////////////////////////////////////////////2. Gu_Edge에 대한 동적할당 해제 후에 Gu_Vertex에 대한 동적할당 해제
	while(m_GVHead!=NULL)	//모든 Gu에 대해서 탐색
	{
		pCur=m_GVHead;	//Gu_Vertex Node의 head를 가리킨다

		pGECur=pCur->GetGENext();	//Gu Edge는 현재 Gu_Vertex의 Edge를 가리킨다
		if(pGECur!=NULL)	//Gu Edge가 존재한다면
		{
			while(pGECur!=NULL)	//Gu Edge를 모두 탐색
			{
				pDelGE=pGECur;	//pDelGE는 동적할당 해제할 node를 가리킨다
				pGECur=pGECur->GetENext();	//pGECur는 다음 Edge로 이동
				delete pDelGE;	//동적할당 해제
			}
		}
		
		m_GVHead=m_GVHead->GetGVNext();	//Gu Vertex의 head는 다음 Gu Vertex로 이동
		delete pCur;	//head의 이전을 가리키던 pCur 동적할당 해제
	}

	////////////////////////////////////////////////////////////////////////////////3. 정비사에 대한 동적할당 해제
	while(m_MHead!=NULL)	//Head가 NULL일 때까지
	{
		pMCur=m_MHead;	//pCur는 head를 가리킨다.
		m_MHead=m_MHead->GetNext();	//head는 다음 정비사를 가리킨다
		delete pMCur;	//pCur동적할당해제
	}

}

void LinkedList::IncreaseGVNum()	//Gu Vertex의 개수를 증가시키는 함수
{
	GVNum++;
}

int LinkedList::GetGVNum()		//Gu Vertex의 개수를 Get하는 함수
{
	return GVNum;
}

Gu_Vertex* LinkedList::GetGVHead()		//Gu_Vertex Node의 head를 Get하는 함수
{
	return m_GVHead;
}

Mechanic* LinkedList::GetMHead()		//Mechanic Node의 head를 Get하는 함수
{
	return m_MHead;
}

bool LinkedList::InsertGuVertex(Gu_Vertex* pnode)		//1차원 Linked List Insert
{
	Gu_Vertex* pCur=m_GVHead;	//pCur는 Gu Vertex의 head를 가리킨다

	Gu_Vertex* pNew=new Gu_Vertex();	//Gu Vertex type 동적할당
	pNew->SetGuName(pnode->GetGuName());	//Gu의 이름에 대한 정보를 Set

	if(m_GVHead==NULL)	//head가 비었다면
	{
		m_GVHead=pNew;	//새로 Insert된 Vertex가 head가 된다
		this->IncreaseGVNum();	//Gu Vertex의 개수 증가
		return true;	//함수 종료
	}

	while(pCur->GetGVNext()!=NULL)	//List내의 제일 마지막 Node를 가리킬 때 까지
	{
		pCur=pCur->GetGVNext();	//다음 Gu Vertex로 이동
	}

	pCur->SetGVNext(pNew);	//마지막 Node와 새로 삽입된 Vertex를 연결한다
	this->IncreaseGVNum();	//Gu Vertex의 개수 증가
	return true;		//함수 종료
}

bool LinkedList::InsertDongVertex(Dong_Vertex* pnode)	//1차원 Circular List Insert
{
	//해당하는 Gu Node를 먼저 찾고
	Gu_Vertex* pGCur=this->FindGu(pnode->GetGuName());

	if(pGCur==NULL)	//해당하는 구가 없는 경우
		return false;

	//pGCur는 pnode에 해당하는 구 Node가 된다.

	Dong_Vertex* pCur=pGCur->GetDNext();
	Dong_Vertex* m_DVHead=pCur;	//해당 구Node의 Next바로 첫번째 Dong Node가 head가 된다.

	Dong_Vertex* pNew=new Dong_Vertex();	//Dong Vertex에 대한 Node를 동적할당
	pNew->SetGuName(pnode->GetGuName());		//인자로 받아온 값들로 정보를 Set한다
	pNew->SetDongName(pnode->GetDongName());
	pNew->SetHeatCheck(pnode->GetHeatCheck());
	pNew->SetIndex(pGCur->GetDongNum());

	if(pCur==NULL)	//Dong node가 하나도 없다면
	{
		pGCur->SetDNext(pNew);	//처음 들어오는 Node를 Head로 구성한다.
		pNew->SetDVNext(pNew);	//자기 자신을 가리켜서 원형 list구성
		pGCur->IncreaseDongNum();	//Gu_Vertex의 dong의 개수를 증가시킨다.
		return true;	//함수 종료
	}

	while(pCur->GetDVNext()!=m_DVHead)	//다음 가리키는 Node가 Dong의 head일 때 까지
	{
		pCur=pCur->GetDVNext();
	}

	pCur->SetDVNext(pNew);	//head이전을 가리키는 pCur와 새로 Insert된 Vertex를 연결
	pNew->SetDVNext(m_DVHead);	//새로 Insert된 Vertex와 head를 연결
	pGCur->IncreaseDongNum();	//Gu_Vertex의 dong의 개수를 증가시킨다.

	if(strcmp(pNew->GetHeatCheck(),"O")==0)	//난방관제소를 head로 해준다.
	{
		pGCur->SetDNext(pNew);
	}

	return true;	//함수 종료

}

bool LinkedList::InsertMechanic(Mechanic* pnode)		//정비사 1차원 Linked List Insert
{
	Mechanic* pNew=new Mechanic();	//Mechanic 타입의 data 동적할당 후 값들을 Set한다.
	pNew->SetName(pnode->GetName());
	pNew->SetWorkPlace(pnode->GetWorkPlace());
	pNew->SetDist(pnode->GetDist());

	if(m_MHead==NULL)	//mechanic head가 NULL이면
	{
		m_MHead=pNew;	//pNew는 head가 된다.
		return true;
	}

	Mechanic* pCur=m_MHead;	//pCur는 List에서 이동하는 포인터

	while(pCur->GetNext()!=NULL)	//pCur의 다음 Node가 NULL일 때 까지
	{
		pCur=pCur->GetNext();	//다음 Node로 이동
	}

	pCur->SetNext(pNew);	//마지막에 pCur다음이 pNew가 되도록 연결
	
	return true;
}

Gu_Vertex* LinkedList::FindGu(char* Guname)	//List 내에 존재하는 인자에 해당하는 Gu Vertex Node를 찾아서 반환하는 함수
{
	Gu_Vertex* pGCur=m_GVHead;	//pGCur 포인터는 list의 Gu Vertex head를 가리킨다

	while(pGCur!=NULL)	//list내의 모든 Gu Vertex를 순회한다
	{
		if(strcmp(pGCur->GetGuName(),Guname)==0)	//pGCur의 GuName와 인자로 받아온 GuName이 일치하면
			break;	//반복문 종료
		pGCur=pGCur->GetGVNext();	//pGCur는 다음 Node를 가리킨다
	}
	if(pGCur==NULL)	//해당하는 구가 없는 경우
		return false;

	return pGCur;	//찾은 Gu Vertex 반환
}

Dong_Vertex* LinkedList::FindDong(char* Guname, char* dongname)	//List내에 존재하는 인자와 일치하는 (구,동) Dong_Vertex를 찾아서 반환하는 함수
{
	Gu_Vertex* pGCur=this->FindGu(Guname);	//Gu에 대한 정보로 해당 Gu Vertex를 찾는다

	Dong_Vertex* pDCur=pGCur->GetDNext();	//처음 동을 가리킨다.

	do
	{
		if(strcmp(pDCur->GetDongName(),dongname)==0)	//Dongname정보와 일치하는 Dong Vertex를 찾으면
			break;	//반복문 종료
		pDCur=pDCur->GetDVNext();	//다음 Dong Vertex로 이동한다

	}while(pDCur!=pGCur->GetDNext());	//원형 한바퀴 돌기
	if(pDCur==NULL)	//해당 Node를 찾지 못한 경우
		return false;	//실패

	return pDCur;	//찾은 Dong Vertex를 반환

}

bool LinkedList::DeleteMechanic()//Mechanic list를 동적할당 해제 하는 함수
{
	Mechanic* pCur=m_MHead;	//정비사 list의 head를 가리킨다

	while(m_MHead!=NULL)	//Head가 NULL일 때까지
	{
		pCur=m_MHead;	//pCur는 head를 가리킨다.
		m_MHead=m_MHead->GetNext();	//head는 다음 정비사를 가리킨다
		delete pCur;	//pCur동적할당해제
	}

	return true;
}

bool LinkedList::DeleteGuList()//Gu_Vertex & Gu_Edge를 동적할당 해제 하는 함수
{
	Gu_Vertex* pCur=m_GVHead;
	Gu_Edge* pGECur=NULL;	//Gu의 Edge를 가리킬 포인터
	Gu_Edge* pDelGE=NULL;	//동적할당 해제할 Gu Edge를 가리킬 포인터

	while(m_GVHead!=NULL)	//모든 Gu에 대해서 탐색
	{
		pCur=m_GVHead;	//Gu_Vertex Node의 head를 가리킨다

		pGECur=pCur->GetGENext();	//Gu Edge는 현재 Gu_Vertex의 Edge를 가리킨다
		if(pGECur!=NULL)	//Gu Edge가 존재한다면
		{
			while(pGECur!=NULL)	//Gu Edge를 모두 탐색
			{
				pDelGE=pGECur;	//pDelGE는 동적할당 해제할 node를 가리킨다
				pGECur=pGECur->GetENext();	//pGECur는 다음 Edge로 이동
				delete pDelGE;	//동적할당 해제
			}
		}
		
		m_GVHead=m_GVHead->GetGVNext();	//Gu Vertex의 head는 다음 Gu Vertex로 이동
		delete pCur;	//head의 이전을 가리키던 pCur 동적할당 해제
	}

	return true;
}

bool LinkedList::DeleteDongList()//Dong_Vertex & Dong_Edge를 동적할당 해제 하는 함수
{
	Gu_Vertex* pCur=m_GVHead;	//pCur는 Gu_Vertex의 Head를 가리킨다.
	Dong_Vertex* pDCur=NULL;	//pDCur는 Gu에 속한 Dong들을 가리킬 포인터이다.
	Dong_Vertex* pDelD=NULL;	//pDelD는 동적할당 해제할 Dong들을 가리키는 포인터
	Dong_Edge* pDECur=NULL;		//pDECur는 Dong에 속한 Dong Edge를 가리킬 포인터
	Dong_Edge* pDelDE=NULL;		//pDelDE는 동적할당 해제할 Dong Edge를 가리킬 포인터

	while(pCur!=NULL)	//모든 Gu에 대해서 탐색
	{
		pDCur=pCur->GetDNext();	//Gu_Vertex의 Dong_Vertex를 가리킨다.
		if(pDCur!=NULL)	//Dong_Vertex가 존재한다면
		{
			do	//Dong의 연결이 종료 될 때 까지
			{
				pDCur=pDCur->GetDVNext();
			}while(pDCur->GetDVNext()!=pCur->GetDNext());
			//pDCur는 head가 되는 Dong Node의 마지막을 가리킨다
			pDCur->SetDVNext(NULL);	//Dong Vertex list를 선형 List로 만든다

			pDCur=pCur->GetDNext();
			while(pDCur!=NULL)	//Dong Vertex가 없을 때 까지
			{
				pDelD=pDCur;
				pDECur=pDCur->GetDENext();	//Dong Vertex의 Edge Node를 가리킨다
				if(pDECur!=NULL)	//pDECur이 존재한다면
				{
					while(pDECur!=NULL)	//pDECur이 Null일 때 까지
					{
						pDelDE=pDECur;	//pDelDE는 현재 pDECur를 가리킨다(삭제할 Node)
						pDECur=pDECur->GetENext();	//pDECur는 다음 Edge 를 가리킨다
						delete pDelDE;	//Dong Edge에 대해서 동적할당 해제
					}
				}

				pDCur=pDCur->GetDVNext();	//pDCur는 다음 Node로 이동
				delete pDelD;	//pDelD 동적할당 해제
			}
		}
		pCur=pCur->GetGVNext();
	}

	return true;
}