#include "Dong_Vertex.h"


Dong_Vertex::Dong_Vertex(void)	//������
{
	GuName=NULL;	//�������� �ʱ�ȭ
	DongName=NULL;
	HeatCheck=NULL;
	index=0;
	DV_Next=NULL;
	DE_Next=NULL;
}


Dong_Vertex::~Dong_Vertex(void)	//�Ҹ���
{
	delete[] GuName;		//�����Ҵ� ����
	delete[] DongName;
	delete[] HeatCheck;
}

void Dong_Vertex::SetGuName(char* name)		//Gu�� �̸��� Set�ϴ� �Լ�
{
	int len=strlen(name);	//name������ ��������
	GuName=new char[len+1];	//���̸�ŭ �����Ҵ�
	memset(GuName,0,len+1);	//�迭 �ʱ�ȭ
	strcpy(GuName,name);	//���� copy
}

void Dong_Vertex::SetDongName(char* name)	//Dong�� �̸��� Set�ϴ� �Լ�
{
	int len=strlen(name);		//name������ ��������
	DongName=new char[len+1];	//���̸�ŭ �����Ҵ�
	memset(DongName,0,len+1);	//�迭 �ʱ�ȭ
	strcpy(DongName,name);		//���� copy
}

void Dong_Vertex::SetHeatCheck(char* check)	//���� ������ ���θ� Set�ϴ� �Լ�
{
	int len=strlen(check);		//check������ ���� ����
	HeatCheck=new char[len+1];	//���̸�ŭ �����Ҵ�
	memset(HeatCheck,0,len+1);	//�迭 �ʱ�ȭ
	strcpy(HeatCheck,check);	//���� copy
}

void Dong_Vertex::SetIndex(int num)	//index�� ���� Set�ϴ� �Լ�
{
	index=num;
}

void Dong_Vertex::SetDVNext(Dong_Vertex* next)	//Dong Vertex�� Next�� DV_Next�� Set�ϴ� �Լ�
{
	DV_Next=next;
}

void Dong_Vertex::SetDENext(Dong_Edge* next)	//Dong Edge�� Next�� DE_Next�� Set�ϴ� �Լ�
{
	DE_Next=next;
}

char* Dong_Vertex::GetGuName()			//Gu�� �̸��� Get�ϴ� �Լ�
{
	return GuName;
}

char* Dong_Vertex::GetDongName()		//Dong�� �̸��� Get�ϴ� �Լ�
{
	return DongName;
}

char* Dong_Vertex::GetHeatCheck()		//���� ������ ���θ� Get�ϴ� �Լ�
{
	return HeatCheck;
}

int Dong_Vertex::GetIndex()		//index�� ���� Get�ϴ� �Լ�
{
	return index;
}

Dong_Vertex* Dong_Vertex::GetDVNext()	//Dong Vertex�� Next�� DV_Next�� Get�ϴ� �Լ�
{
	return DV_Next;
}

Dong_Edge* Dong_Vertex::GetDENext()		//Dong Edge�� Next�� DE_Next�� Get�ϴ� �Լ�
{
	return DE_Next;
}