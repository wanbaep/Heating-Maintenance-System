#include "stack.h"


stack::stack(void)
{
	m_pHead=NULL;
}


stack::~stack(void)
{
}

bool stack::IsEmpty() //memory�� ����ִ��� Ȯ���ϴ� �Լ�
{
	if(m_pHead==NULL) //Node�� ���ٸ� m_pHead�� ���� NULL�̴�.
		return 1;
	else
		return 0;
}


bool stack::Push(Gu_Vertex* pNode) //�� �����޴� ->return true, ������ ����X ->return false
{                             //Push(����) �Լ� ���ڷ� Node�� �����͸� �޴´�.

	Gu_Vertex* pCur=m_pHead;
	Gu_Vertex* pNew=NULL;

	pNew=pNode;

	if(m_pHead==NULL) //Node�� �ϳ��� ���ٸ�
	{
		m_pHead=pNew; //m_pHead�� pNew�� ����Ų��.
	}
	else //Node�� �ִٸ�
	{
		pNew->SetSNext(m_pHead); //pNew �� m_pHead ���� �տ� ���Եȴ�.
		m_pHead=pNew;   //m_pHead�� pNew�� �ٲ��ش�.
	}
	return 1;  //���Լ����̹Ƿ� true ��ȯ

}

Gu_Vertex* stack::Pop()  //Pop(����)�Լ�
{
	Gu_Vertex* pPop=m_pHead; //pop�� �������� �� ������ �̷�� ���µ� �� ���� m_pHead �̴�.
	bool empty=0;  //������� Ȯ��
	empty=IsEmpty(); //IsEmpty��ȯ�� ����

	if(empty) //����ִٸ�
	{
		return NULL;
	}
	else //Node�� �ִٸ�
	{
		m_pHead=m_pHead->GetSNext(); //m_pHead�� ���� Node�� ����Ű�� �Ѵ�.
		pPop->SetSNext(NULL);
		return pPop;     // �� ������ m_pHead�� ����Ű�� pPop ��ȯ
	}
}