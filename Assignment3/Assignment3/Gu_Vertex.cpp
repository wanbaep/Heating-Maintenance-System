#include "Gu_Vertex.h"


Gu_Vertex::Gu_Vertex(void)	//������
{
	GuName=NULL;	//������� �ʱ�ȭ
	dongnum=0;
	arr=0;
	cost=0;
	visit=false;
	GV_Next=NULL;
	GE_Next=NULL;
	D_Next=NULL;
	S_Next=NULL;
}


Gu_Vertex::~Gu_Vertex(void)	//�Ҹ���
{
	delete[] GuName;	//�����Ҵ� ����
	delete[] arr;
}

void Gu_Vertex::SetGuName(char* name)	//�ش� Gu�� �̸��� Set�ϴ� �Լ�
{
	int len=strlen(name);	//������ ���̸� �޴´�
	GuName=new char[len+1];	//�����Ҵ�
	memset(GuName,0,len+1);	//�迭 �ʱ�ȭ
	strcpy(GuName,name);	//���� copy
}

void Gu_Vertex::IncreaseDongNum()	//���ԵǴ� Dong�� ������ ������Ű�� �Լ�
{
	dongnum++;	//dongnum���� 0���� ����
}

void Gu_Vertex::SetArray(int num)	//MST���� ���� Array�� Set�ϴ� �Լ�
{
	arr=new int[num];		//������ ���̸� �޴´�
	memset(arr,0,num);		//�迭 1���� �ʱ�ȭ
	for(int i=0; i<num;i++)	//�ݺ����� ���� 2���� �迭 �ʱ�ȭ
		arr[i]=i;
}

void Gu_Vertex::SetCost(int co)//Dijkstra���� ���� Cost�� Set�ϴ� �Լ�
{
	cost=co;
}

void Gu_Vertex::SetVisit(bool vis)//Dijkstra���� ���� Visit�� ���ؼ� Set�ϴ� �Լ�
{
	visit=vis;
}

void Gu_Vertex::SetGVNext(Gu_Vertex* next)//Gu Vertex�� ������ Set�ϴ� �Լ�
{
	GV_Next=next;
}

void Gu_Vertex::SetGENext(Gu_Edge* next)//Gu Edge�� Set�ϴ� �Լ�
{
	GE_Next=next;
}

void Gu_Vertex::SetDNext(Dong_Vertex* next)//head�� �ش��ϴ� Dong Vertex�� Set�ϴ� �Լ�
{
	D_Next=next;
}

void Gu_Vertex::SetSNext(Gu_Vertex* next)//stack���� ����� Gu Vertex�� ����Ű�� �����͸� Set�ϴ� �Լ�
{
	S_Next=next;
}

char* Gu_Vertex::GetGuName()	//GuName�� Get�ϴ��Լ�
{
	return GuName;
}

int Gu_Vertex::GetDongNum()	//DongNum�� Get�ϴ��Լ�
{
	return dongnum;
}

int* Gu_Vertex::GetArray()	//Vertex�� array�� Get�ϴ��Լ�
{
	return arr;
}

int Gu_Vertex::GetCost()	//Cost ���� Get�ϴ� �Լ�
{
	return cost;
}
bool Gu_Vertex::GetVisit()	//vidst���� Get�ϴ� �Լ�
{
	return visit;
}

Gu_Vertex* Gu_Vertex::GetGVNext()	//���� Gu Vertex�� Get�ϴ� �Լ�
{
	return GV_Next;
}

Gu_Edge* Gu_Vertex::GetGENext()	//���� Gu Edge�� Get�ϴ� �Լ�
{
	return GE_Next;
}

Dong_Vertex* Gu_Vertex::GetDNext()	//head Dong�� Get�ϴ� �Լ�
{
	return D_Next;
}

Gu_Vertex* Gu_Vertex::GetSNext()	//Stack�� Next�� Get�ϴ� �Լ�
{
	return S_Next;
}