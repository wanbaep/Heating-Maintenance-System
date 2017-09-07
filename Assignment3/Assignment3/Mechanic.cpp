#include "Mechanic.h"


Mechanic::Mechanic(void)
{
	Name=NULL;
	Workplace=NULL;
	dist=0;
	pNext=NULL;
}


Mechanic::~Mechanic(void)
{
}

void Mechanic::SetName(char* pname)	//������� �̸��� Set�ϴ� �Լ�
{
	int len=strlen(pname);	//������ ���̸� �޾ƿ´�
	Name=new char[len+1];	//�����Ҵ�
	memset(Name,0,len+1);	//�迭 �ʱ�ȭ
	strcpy(Name,pname);		//���� copy
}

void Mechanic::SetWorkPlace(char* place)	//������� �ٹ����� Set�ϴ� �Լ�
{
	int len=strlen(place);		//������ ���̸� �޾ƿ´�
	Workplace=new char[len+1];	//�����Ҵ�
	memset(Workplace,0,len+1);	//�迭 �ʱ�ȭ
	strcpy(Workplace,place);	//���� copy
}

void Mechanic::SetDist(int d)		//����簡 ��������� ������������ �Ÿ��� Set�ϴ� �Լ�
{
	dist=d;
}

void Mechanic::SetNext(Mechanic* next)	//���� ����縦 Set�ϴ� �Լ�
{
	pNext=next;
}

char* Mechanic::GetName()	//������� �̸��� Get�ϴ� �Լ�
{
	return Name;
}

char* Mechanic::GetWorkPlace()	//������� �ٹ����� Get�ϴ� �Լ�
{
	return Workplace;
}

int Mechanic::GetDist()		//������� �̵� �Ÿ��� Get�ϴ� �Լ�
{
	return dist;
}

Mechanic* Mechanic::GetNext()	//���� ����� Node�� Get�ϴ� �Լ�
{
	return pNext;
}
