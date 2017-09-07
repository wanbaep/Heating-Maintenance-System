#include "LinkedList.h"


LinkedList::LinkedList(void)	//������
{
	GVNum=0;	//���� �ʱ�ȭ
	m_GVHead=NULL;
	m_MHead=NULL;
}

LinkedList::~LinkedList(void)	//�Ҹ���
{
	Gu_Vertex* pCur=m_GVHead;	//pCur�� Gu_Vertex�� Head�� ����Ų��.
	Dong_Vertex* pDCur=NULL;	//pDCur�� Gu�� ���� Dong���� ����ų �������̴�.
	Dong_Vertex* pDelD=NULL;	//pDelD�� �����Ҵ� ������ Dong���� ����Ű�� ������
	Dong_Edge* pDECur=NULL;		//pDECur�� Dong�� ���� Dong Edge�� ����ų ������
	Dong_Edge* pDelDE=NULL;		//pDelDE�� �����Ҵ� ������ Dong Edge�� ����ų ������
	
	Gu_Edge* pGECur=NULL;	//Gu�� Edge�� ����ų ������
	Gu_Edge* pDelGE=NULL;	//�����Ҵ� ������ Gu Edge�� ����ų ������

	Mechanic* pMCur=m_MHead;	//����� list�� head�� ����Ų��

	/////////////////////////////////////////////////////////////////////////////////1. Dong_Edge�� ���� �����Ҵ� �Ŀ� Dong_Vertex�� ���� �����Ҵ�
	while(pCur!=NULL)	//��� Gu�� ���ؼ� Ž��
	{
		pDCur=pCur->GetDNext();	//Gu_Vertex�� Dong_Vertex�� ����Ų��.
		if(pDCur!=NULL)	//Dong_Vertex�� �����Ѵٸ�
		{
			do	//Dong�� ������ ���� �� �� ����
			{
				pDCur=pDCur->GetDVNext();
			}while(pDCur->GetDVNext()!=pCur->GetDNext());
			//pDCur�� head�� �Ǵ� Dong Node�� �������� ����Ų��
			pDCur->SetDVNext(NULL);	//Dong Vertex list�� ���� List�� �����

			pDCur=pCur->GetDNext();
			while(pDCur!=NULL)	//Dong Vertex�� ���� �� ����
			{
				pDelD=pDCur;
				pDECur=pDCur->GetDENext();	//Dong Vertex�� Edge Node�� ����Ų��
				if(pDECur!=NULL)	//pDECur�� �����Ѵٸ�
				{
					while(pDECur!=NULL)	//pDECur�� Null�� �� ����
					{
						pDelDE=pDECur;	//pDelDE�� ���� pDECur�� ����Ų��(������ Node)
						pDECur=pDECur->GetENext();	//pDECur�� ���� Edge �� ����Ų��
						delete pDelDE;	//Dong Edge�� ���ؼ� �����Ҵ� ����
					}
				}

				pDCur=pDCur->GetDVNext();	//pDCur�� ���� Node�� �̵�
				delete pDelD;	//pDelD �����Ҵ� ����
			}
		}
		pCur=pCur->GetGVNext();
	}

	///////////////////////////////////////////////////////////////////////////////2. Gu_Edge�� ���� �����Ҵ� ���� �Ŀ� Gu_Vertex�� ���� �����Ҵ� ����
	while(m_GVHead!=NULL)	//��� Gu�� ���ؼ� Ž��
	{
		pCur=m_GVHead;	//Gu_Vertex Node�� head�� ����Ų��

		pGECur=pCur->GetGENext();	//Gu Edge�� ���� Gu_Vertex�� Edge�� ����Ų��
		if(pGECur!=NULL)	//Gu Edge�� �����Ѵٸ�
		{
			while(pGECur!=NULL)	//Gu Edge�� ��� Ž��
			{
				pDelGE=pGECur;	//pDelGE�� �����Ҵ� ������ node�� ����Ų��
				pGECur=pGECur->GetENext();	//pGECur�� ���� Edge�� �̵�
				delete pDelGE;	//�����Ҵ� ����
			}
		}
		
		m_GVHead=m_GVHead->GetGVNext();	//Gu Vertex�� head�� ���� Gu Vertex�� �̵�
		delete pCur;	//head�� ������ ����Ű�� pCur �����Ҵ� ����
	}

	////////////////////////////////////////////////////////////////////////////////3. ����翡 ���� �����Ҵ� ����
	while(m_MHead!=NULL)	//Head�� NULL�� ������
	{
		pMCur=m_MHead;	//pCur�� head�� ����Ų��.
		m_MHead=m_MHead->GetNext();	//head�� ���� ����縦 ����Ų��
		delete pMCur;	//pCur�����Ҵ�����
	}

}

void LinkedList::IncreaseGVNum()	//Gu Vertex�� ������ ������Ű�� �Լ�
{
	GVNum++;
}

int LinkedList::GetGVNum()		//Gu Vertex�� ������ Get�ϴ� �Լ�
{
	return GVNum;
}

Gu_Vertex* LinkedList::GetGVHead()		//Gu_Vertex Node�� head�� Get�ϴ� �Լ�
{
	return m_GVHead;
}

Mechanic* LinkedList::GetMHead()		//Mechanic Node�� head�� Get�ϴ� �Լ�
{
	return m_MHead;
}

bool LinkedList::InsertGuVertex(Gu_Vertex* pnode)		//1���� Linked List Insert
{
	Gu_Vertex* pCur=m_GVHead;	//pCur�� Gu Vertex�� head�� ����Ų��

	Gu_Vertex* pNew=new Gu_Vertex();	//Gu Vertex type �����Ҵ�
	pNew->SetGuName(pnode->GetGuName());	//Gu�� �̸��� ���� ������ Set

	if(m_GVHead==NULL)	//head�� ����ٸ�
	{
		m_GVHead=pNew;	//���� Insert�� Vertex�� head�� �ȴ�
		this->IncreaseGVNum();	//Gu Vertex�� ���� ����
		return true;	//�Լ� ����
	}

	while(pCur->GetGVNext()!=NULL)	//List���� ���� ������ Node�� ����ų �� ����
	{
		pCur=pCur->GetGVNext();	//���� Gu Vertex�� �̵�
	}

	pCur->SetGVNext(pNew);	//������ Node�� ���� ���Ե� Vertex�� �����Ѵ�
	this->IncreaseGVNum();	//Gu Vertex�� ���� ����
	return true;		//�Լ� ����
}

bool LinkedList::InsertDongVertex(Dong_Vertex* pnode)	//1���� Circular List Insert
{
	//�ش��ϴ� Gu Node�� ���� ã��
	Gu_Vertex* pGCur=this->FindGu(pnode->GetGuName());

	if(pGCur==NULL)	//�ش��ϴ� ���� ���� ���
		return false;

	//pGCur�� pnode�� �ش��ϴ� �� Node�� �ȴ�.

	Dong_Vertex* pCur=pGCur->GetDNext();
	Dong_Vertex* m_DVHead=pCur;	//�ش� ��Node�� Next�ٷ� ù��° Dong Node�� head�� �ȴ�.

	Dong_Vertex* pNew=new Dong_Vertex();	//Dong Vertex�� ���� Node�� �����Ҵ�
	pNew->SetGuName(pnode->GetGuName());		//���ڷ� �޾ƿ� ����� ������ Set�Ѵ�
	pNew->SetDongName(pnode->GetDongName());
	pNew->SetHeatCheck(pnode->GetHeatCheck());
	pNew->SetIndex(pGCur->GetDongNum());

	if(pCur==NULL)	//Dong node�� �ϳ��� ���ٸ�
	{
		pGCur->SetDNext(pNew);	//ó�� ������ Node�� Head�� �����Ѵ�.
		pNew->SetDVNext(pNew);	//�ڱ� �ڽ��� �����Ѽ� ���� list����
		pGCur->IncreaseDongNum();	//Gu_Vertex�� dong�� ������ ������Ų��.
		return true;	//�Լ� ����
	}

	while(pCur->GetDVNext()!=m_DVHead)	//���� ����Ű�� Node�� Dong�� head�� �� ����
	{
		pCur=pCur->GetDVNext();
	}

	pCur->SetDVNext(pNew);	//head������ ����Ű�� pCur�� ���� Insert�� Vertex�� ����
	pNew->SetDVNext(m_DVHead);	//���� Insert�� Vertex�� head�� ����
	pGCur->IncreaseDongNum();	//Gu_Vertex�� dong�� ������ ������Ų��.

	if(strcmp(pNew->GetHeatCheck(),"O")==0)	//��������Ҹ� head�� ���ش�.
	{
		pGCur->SetDNext(pNew);
	}

	return true;	//�Լ� ����

}

bool LinkedList::InsertMechanic(Mechanic* pnode)		//����� 1���� Linked List Insert
{
	Mechanic* pNew=new Mechanic();	//Mechanic Ÿ���� data �����Ҵ� �� ������ Set�Ѵ�.
	pNew->SetName(pnode->GetName());
	pNew->SetWorkPlace(pnode->GetWorkPlace());
	pNew->SetDist(pnode->GetDist());

	if(m_MHead==NULL)	//mechanic head�� NULL�̸�
	{
		m_MHead=pNew;	//pNew�� head�� �ȴ�.
		return true;
	}

	Mechanic* pCur=m_MHead;	//pCur�� List���� �̵��ϴ� ������

	while(pCur->GetNext()!=NULL)	//pCur�� ���� Node�� NULL�� �� ����
	{
		pCur=pCur->GetNext();	//���� Node�� �̵�
	}

	pCur->SetNext(pNew);	//�������� pCur������ pNew�� �ǵ��� ����
	
	return true;
}

Gu_Vertex* LinkedList::FindGu(char* Guname)	//List ���� �����ϴ� ���ڿ� �ش��ϴ� Gu Vertex Node�� ã�Ƽ� ��ȯ�ϴ� �Լ�
{
	Gu_Vertex* pGCur=m_GVHead;	//pGCur �����ʹ� list�� Gu Vertex head�� ����Ų��

	while(pGCur!=NULL)	//list���� ��� Gu Vertex�� ��ȸ�Ѵ�
	{
		if(strcmp(pGCur->GetGuName(),Guname)==0)	//pGCur�� GuName�� ���ڷ� �޾ƿ� GuName�� ��ġ�ϸ�
			break;	//�ݺ��� ����
		pGCur=pGCur->GetGVNext();	//pGCur�� ���� Node�� ����Ų��
	}
	if(pGCur==NULL)	//�ش��ϴ� ���� ���� ���
		return false;

	return pGCur;	//ã�� Gu Vertex ��ȯ
}

Dong_Vertex* LinkedList::FindDong(char* Guname, char* dongname)	//List���� �����ϴ� ���ڿ� ��ġ�ϴ� (��,��) Dong_Vertex�� ã�Ƽ� ��ȯ�ϴ� �Լ�
{
	Gu_Vertex* pGCur=this->FindGu(Guname);	//Gu�� ���� ������ �ش� Gu Vertex�� ã�´�

	Dong_Vertex* pDCur=pGCur->GetDNext();	//ó�� ���� ����Ų��.

	do
	{
		if(strcmp(pDCur->GetDongName(),dongname)==0)	//Dongname������ ��ġ�ϴ� Dong Vertex�� ã����
			break;	//�ݺ��� ����
		pDCur=pDCur->GetDVNext();	//���� Dong Vertex�� �̵��Ѵ�

	}while(pDCur!=pGCur->GetDNext());	//���� �ѹ��� ����
	if(pDCur==NULL)	//�ش� Node�� ã�� ���� ���
		return false;	//����

	return pDCur;	//ã�� Dong Vertex�� ��ȯ

}

bool LinkedList::DeleteMechanic()//Mechanic list�� �����Ҵ� ���� �ϴ� �Լ�
{
	Mechanic* pCur=m_MHead;	//����� list�� head�� ����Ų��

	while(m_MHead!=NULL)	//Head�� NULL�� ������
	{
		pCur=m_MHead;	//pCur�� head�� ����Ų��.
		m_MHead=m_MHead->GetNext();	//head�� ���� ����縦 ����Ų��
		delete pCur;	//pCur�����Ҵ�����
	}

	return true;
}

bool LinkedList::DeleteGuList()//Gu_Vertex & Gu_Edge�� �����Ҵ� ���� �ϴ� �Լ�
{
	Gu_Vertex* pCur=m_GVHead;
	Gu_Edge* pGECur=NULL;	//Gu�� Edge�� ����ų ������
	Gu_Edge* pDelGE=NULL;	//�����Ҵ� ������ Gu Edge�� ����ų ������

	while(m_GVHead!=NULL)	//��� Gu�� ���ؼ� Ž��
	{
		pCur=m_GVHead;	//Gu_Vertex Node�� head�� ����Ų��

		pGECur=pCur->GetGENext();	//Gu Edge�� ���� Gu_Vertex�� Edge�� ����Ų��
		if(pGECur!=NULL)	//Gu Edge�� �����Ѵٸ�
		{
			while(pGECur!=NULL)	//Gu Edge�� ��� Ž��
			{
				pDelGE=pGECur;	//pDelGE�� �����Ҵ� ������ node�� ����Ų��
				pGECur=pGECur->GetENext();	//pGECur�� ���� Edge�� �̵�
				delete pDelGE;	//�����Ҵ� ����
			}
		}
		
		m_GVHead=m_GVHead->GetGVNext();	//Gu Vertex�� head�� ���� Gu Vertex�� �̵�
		delete pCur;	//head�� ������ ����Ű�� pCur �����Ҵ� ����
	}

	return true;
}

bool LinkedList::DeleteDongList()//Dong_Vertex & Dong_Edge�� �����Ҵ� ���� �ϴ� �Լ�
{
	Gu_Vertex* pCur=m_GVHead;	//pCur�� Gu_Vertex�� Head�� ����Ų��.
	Dong_Vertex* pDCur=NULL;	//pDCur�� Gu�� ���� Dong���� ����ų �������̴�.
	Dong_Vertex* pDelD=NULL;	//pDelD�� �����Ҵ� ������ Dong���� ����Ű�� ������
	Dong_Edge* pDECur=NULL;		//pDECur�� Dong�� ���� Dong Edge�� ����ų ������
	Dong_Edge* pDelDE=NULL;		//pDelDE�� �����Ҵ� ������ Dong Edge�� ����ų ������

	while(pCur!=NULL)	//��� Gu�� ���ؼ� Ž��
	{
		pDCur=pCur->GetDNext();	//Gu_Vertex�� Dong_Vertex�� ����Ų��.
		if(pDCur!=NULL)	//Dong_Vertex�� �����Ѵٸ�
		{
			do	//Dong�� ������ ���� �� �� ����
			{
				pDCur=pDCur->GetDVNext();
			}while(pDCur->GetDVNext()!=pCur->GetDNext());
			//pDCur�� head�� �Ǵ� Dong Node�� �������� ����Ų��
			pDCur->SetDVNext(NULL);	//Dong Vertex list�� ���� List�� �����

			pDCur=pCur->GetDNext();
			while(pDCur!=NULL)	//Dong Vertex�� ���� �� ����
			{
				pDelD=pDCur;
				pDECur=pDCur->GetDENext();	//Dong Vertex�� Edge Node�� ����Ų��
				if(pDECur!=NULL)	//pDECur�� �����Ѵٸ�
				{
					while(pDECur!=NULL)	//pDECur�� Null�� �� ����
					{
						pDelDE=pDECur;	//pDelDE�� ���� pDECur�� ����Ų��(������ Node)
						pDECur=pDECur->GetENext();	//pDECur�� ���� Edge �� ����Ų��
						delete pDelDE;	//Dong Edge�� ���ؼ� �����Ҵ� ����
					}
				}

				pDCur=pDCur->GetDVNext();	//pDCur�� ���� Node�� �̵�
				delete pDelD;	//pDelD �����Ҵ� ����
			}
		}
		pCur=pCur->GetGVNext();
	}

	return true;
}