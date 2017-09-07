#include "stack.h"


stack::stack(void)
{
	m_pHead=NULL;
}


stack::~stack(void)
{
}

bool stack::IsEmpty() //memory가 비어있는지 확인하는 함수
{
	if(m_pHead==NULL) //Node가 없다면 m_pHead의 값은 NULL이다.
		return 1;
	else
		return 0;
}


bool stack::Push(Gu_Vertex* pNode) //비어서 삽입햇다 ->return true, 꽉차서 삽입X ->return false
{                             //Push(삽입) 함수 인자로 Node형 포인터를 받는다.

	Gu_Vertex* pCur=m_pHead;
	Gu_Vertex* pNew=NULL;

	pNew=pNode;

	if(m_pHead==NULL) //Node가 하나도 없다면
	{
		m_pHead=pNew; //m_pHead는 pNew를 가리킨다.
	}
	else //Node가 있다면
	{
		pNew->SetSNext(m_pHead); //pNew 는 m_pHead 보다 앞에 삽입된다.
		m_pHead=pNew;   //m_pHead를 pNew로 바꿔준다.
	}
	return 1;  //삽입성공이므로 true 반환

}

Gu_Vertex* stack::Pop()  //Pop(삭제)함수
{
	Gu_Vertex* pPop=m_pHead; //pop은 마지막에 들어간 값에서 이루어 지는데 그 값이 m_pHead 이다.
	bool empty=0;  //비었는지 확인
	empty=IsEmpty(); //IsEmpty반환값 저장

	if(empty) //비어있다면
	{
		return NULL;
	}
	else //Node가 있다면
	{
		m_pHead=m_pHead->GetSNext(); //m_pHead를 다음 Node를 가리키게 한다.
		pPop->SetSNext(NULL);
		return pPop;     // 그 이전의 m_pHead를 가리키던 pPop 반환
	}
}