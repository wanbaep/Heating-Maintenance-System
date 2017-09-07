#include "Gu_Edge.h"
#include"Gu_Vertex.h"

Gu_Edge::Gu_Edge(void)	//������
{
	FromGu=NULL;	//�ʱ�ȭ
	ToGu=NULL;
	distance=0;
	E_Next=NULL;
	toGu_Next=NULL;
}


Gu_Edge::~Gu_Edge(void)	//�Ҹ���
{
	delete[] FromGu;	//�����Ҵ� ����
	delete[] ToGu;
}

void Gu_Edge::SetFromGu(char* fromgu)	//From�� �ش��ϴ� Gu�� �̸��� �����ϴ� �Լ�
{
	int len=strlen(fromgu);	//������ ���̸� ����
	FromGu=new char[len+1];	//�����Ҵ�
	memset(FromGu,0,len+1);	//�ʱ�ȭ
	strcpy(FromGu,fromgu);	//���� copy�Ѵ�
}

void Gu_Edge::SetToGu(char* togu)	//to�� �ش��ϴ� Gu�� �̸��� �����ϴ� �Լ�
{
	int len=strlen(togu);	//���ڱ��� ����
	ToGu=new char[len+1];	//���� �Ҵ�
	memset(ToGu,0,len+1);	//�迭 �ʱ�ȭ �Ѵ�
	strcpy(ToGu,togu);		//���� copy�Ѵ�
}

void Gu_Edge::SetDist1(char* dist)	//char�� dist�� ���� distance�� set�ϴ� �Լ�
{
	distance=atoi(dist);
}

void Gu_Edge::SetDist2(int dist)	//int�� dist�� ���� distance�� set�ϴ� �Լ�
{
	distance=dist;
}

void Gu_Edge::SetENext(Gu_Edge* next)	//Gu edge�� ������ set�ϴ� �Լ�
{
	E_Next=next;
}

void Gu_Edge::SetToGuNext(Gu_Vertex* next)	//To�� �ش��ϴ� Gu�� ���ؼ� �����ϴ� �Լ�
{
	toGu_Next=next;
}

char* Gu_Edge::GetFromGu()	//from�� �ش��ϴ� Gu�� �̸��� Get�ϴ��Լ�
{
	return FromGu;
}

char* Gu_Edge::GetToGu()	//to�� �ش��ϴ� Gu�� �̸��� Get�ϴ� �Լ�
{
	return ToGu;
}

int Gu_Edge::GetDist()	//distance�� ���� Get�ϴ� �Լ�
{
	return distance;
}

Gu_Edge* Gu_Edge::GetENext()	//���� Edge�� Get�ϴ� �Լ�
{
	return E_Next;
}

Gu_Vertex* Gu_Edge::GetToGuNext()	//To�� �ش��ϴ� Gu Vertex�� Get�ϴ� �Լ�
{
	return toGu_Next;
}