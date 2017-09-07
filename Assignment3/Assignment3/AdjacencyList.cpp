#include "AdjacencyList.h"


AdjacencyList::AdjacencyList(void)	//������
{
}


AdjacencyList::~AdjacencyList(void)	//�Ҹ���
{
}


bool AdjacencyList::InsertGuEdge(LinkedList &list, Gu_Edge* pnode)		//Gu�� ���� ��������Ʈ�� Insert�ϴ� �Լ�
{
	Gu_Vertex* pVCur=list.GetGVHead();

	Gu_Edge* pNew=new Gu_Edge();	//�����Ҵ� �� ������ Node�� ���� Set�Ѵ�.
	pNew->SetFromGu(pnode->GetFromGu());
	pNew->SetToGu(pnode->GetToGu());
	pNew->SetDist2(pnode->GetDist());
	
	Gu_Vertex* pFVCur=NULL;	//From�� ���� ����Ű�� ������
	Gu_Vertex* pTVCur=NULL;	//To�� ���� ����Ű�� ������
	int count=0;

	while(pVCur!=NULL)
	{
		if(strcmp(pVCur->GetGuName(),pNew->GetFromGu())==0)	//From ���� ã�´�.
		{
			pFVCur=pVCur;
			count++;
		}
		if(strcmp(pVCur->GetGuName(),pNew->GetToGu())==0)	//To ���� ã�´�.
		{
			pTVCur=pVCur;
			count++;
		}
		if(count==2)	//From ���� To ���� ��� ã������
			break;

		pVCur=pVCur->GetGVNext();
	}
	if(pVCur==NULL)	//From ���� To ���� ã�� ���� ��� count�� 2�� ���� �ʾƼ�, pVCur�� NULL�� �Ǹ� ���� ��ȯ
		return false;

	if(pFVCur->GetGENext()==NULL)	//From���� ���ؼ� ���� ����
	{
		pFVCur->SetGENext(pNew);
		pNew->SetToGuNext(pTVCur);	//pNew�� To ���� ���ؼ� ����
	}
	else
	{
		Gu_Edge* pECur=pFVCur->GetGENext();

		while(pECur->GetENext()!=NULL)	//From ������ ����� ��ġ�� ã�´�.
		{
			pECur=pECur->GetENext();
		}
		pECur->SetENext(pNew);
		pNew->SetToGuNext(pTVCur);	//pNew�� To ���� ���ؼ� ����
	}

	return true;
}

bool AdjacencyList::InsertDongEdge(LinkedList &list, Dong_Edge* pnode)	//Dong�� ���� ��������Ʈ�� Insert�ϴ� �Լ�
{
	Gu_Vertex* pGCur=list.FindGu(pnode->GetGuName());

	if(pGCur==NULL)	//pGCur�� pnode�� ���� �ش��ϴ� Vertex_Node�̴�.
		return false;
	
	Dong_Edge* pNew=new Dong_Edge();		//���ο� Dong Edge�� ���ؼ� �����Ҵ�
	pNew->SetGuName(pnode->GetGuName());		//��� �������� Set�ϵ��� �Ѵ�.
	pNew->SetFromDong(pnode->GetFromDong());	//from Dong�� �̸��� ���ؼ� set
	pNew->SetToDong(pnode->GetToDong());	//to Dong�� �̸��� ���ؼ� set
	pNew->SetLossRate2(pnode->GetLossRate());	//�� �ս����� Set�ϴ� �Լ�
	pNew->SetPipeStatus(pnode->GetPipeStatus());	//pipe ���¸� Set�ϴ� �Լ�
	//////overlap�� useflag�� 0���� �ʱ�ȭ �Ǳ� ������ ���� �ʱ�ȭ ���� �ʴ´�

	Dong_Vertex* pDCur=pGCur->GetDNext();	//Gu Vertex�� ó�� Dong Vertex�� ����ų ������
	Dong_Vertex* D_Head=pDCur;		//D_Head�� Gu Vertex�� ó�� Dong Vertex�� ����Ű�� ������
	Dong_Vertex* pDFCur=NULL;		//From�� �ش��ϴ� Dong Vertex�� ����ų ������
	Dong_Vertex* pDTCur=NULL;		//To�� �ش��ϴ� Dong Vertex�� ����ų ������

	do
	{
		if(strcmp(pDCur->GetDongName(),pNew->GetFromDong())==0)	//From�� �ش��ϴ� Dong�� ã�´�.
			pDFCur=pDCur;

		if(strcmp(pDCur->GetDongName(),pNew->GetToDong())==0)	//To�� �ش��ϴ� Dong�� ã�´�.
			pDTCur=pDCur;

		pDCur=pDCur->GetDVNext();

	}while(pDCur!=D_Head);
	
	/////////////////pDFCur���� edge Node(pNew)�� �����Ѵ�
	Dong_Edge* pECur=pDFCur->GetDENext();	//pECur�� pDFCur���� Dong Edge�� ����Ų��.

	if(pECur==NULL)	//Dong Edge�� �ϳ��� ���� ���
	{
		pDFCur->SetDENext(pNew);
		pNew->SetToDongNext(pDTCur);	//pNew���� toDong�� �ش��ϴ� pDTCur�� �����ϱ�
		pNew->SetFromDongNext(pDFCur);//pNew���� fromDong�� �ش��ϴ� pDFCur�� �����ϱ�
		return true;
	}

	//Dong Edge�� �ִ� ���
	while(pECur->GetENext()!=NULL)	//Edge�� ���� �� ���� �̵�
	{
		pECur=pECur->GetENext();
	}
	pECur->SetENext(pNew);	//������ Edge Node�� Insert�� Edge Node ����
	pNew->SetToDongNext(pDTCur);		//pNew���� toDong�� �ش��ϴ� pDTCur�� �����ϱ�
	pNew->SetFromDongNext(pDFCur);	//pNew���� fromDong�� �ش��ϴ� pDFCur�� �����ϱ�

	return true;
}