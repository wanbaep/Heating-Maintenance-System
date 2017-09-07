#include "Dong_Edge.h"
#include "Dong_Vertex.h"

Dong_Edge::Dong_Edge(void)	//������
{
	GuName=NULL;	//�������� �ʱ�ȭ
	FromDong=NULL;
	ToDong=NULL;
	Pipestatus=NULL;
	LossRate=0;
	overlap=0;
	useflag=0;
	E_Next=NULL;
	toDong_Next=NULL;
	fromDong_Next=NULL;
}


Dong_Edge::~Dong_Edge(void)	//�Ҹ���
{
	delete[] GuName;	//�����Ҵ��� ���鿡 ���ؼ� �����Ҵ� ����
	delete[] FromDong;
	delete[] ToDong;
	delete[] Pipestatus;
}

void Dong_Edge::SetGuName(char* name)			//�ش� ���� ���̸��� Set�ϴ� �Լ�
{
	int len=strlen(name);	//������ ���̸� ����
	GuName=new char[len+1];	//������ ���̸�ŭ �����Ҵ�
	memset(GuName,0,len+1);	//�����Ҵ��� �迭 �ʱ�ȭ
	strcpy(GuName,name);	//������ ������ �迭�� copy
}

void Dong_Edge::SetFromDong(char* fromdong)	//From�� �ش��ϴ� Dong�� �̸��� Set�ϴ� �Լ�
{
	int len=strlen(fromdong);	//������ ���̸� ����
	FromDong=new char[len+1];	//������ ���̸�ŭ �����Ҵ�
	memset(FromDong,0,len+1);	//�����Ҵ��� �迭 �ʱ�ȭ
	strcpy(FromDong,fromdong);	//������ ������ �迭�� copy
}

void Dong_Edge::SetToDong(char* todong)		//To�� �ش��ϴ� Dong�� �̸��� Set�ϴ� �Լ�
{
	int len=strlen(todong);	//������ ���̸� ����
	ToDong=new char[len+1];	//������ ���̸�ŭ �����Ҵ�
	memset(ToDong,0,len+1);	//�����Ҵ��� �迭 �ʱ�ȭ
	strcpy(ToDong,todong);	//������ ������ �迭�� copy
}

void Dong_Edge::SetPipeStatus(char* pipe)	//pipe�� ���¸� Set�ϴ� �Լ�
{
	int len=strlen(pipe);		//������ ���̸� ����
	Pipestatus=new char[len+1];	//������ ���̸�ŭ �����Ҵ�
	memset(Pipestatus,0,len+1);	//�����Ҵ��� �迭 �ʱ�ȭ
	strcpy(Pipestatus,pipe);	//������ ������ �迭�� copy
}

void Dong_Edge::SetLossRate1(char* rate)	//���ս����� ���� Set�ϴ� �Լ�
{
	LossRate=atoi(rate);
}

void Dong_Edge::SetLossRate2(int rate)	//int�� ���ս����� ���� Set�ϴ� �Լ�
{
	LossRate=rate;
}

void Dong_Edge::SetOverlap(int ov)	//Overlap�� ���� Set�ϴ� �Լ�
{
	overlap=ov;
}

void Dong_Edge::SetUseflag(int flag)	//useflag�� ���� Set�ϴ� �Լ�
{
	useflag=flag;
}

void Dong_Edge::SetENext(Dong_Edge* next)		//Dong_Edge�� Next�� Set�ϴ� �Լ�
{
	E_Next=next;
}

void Dong_Edge::SetToDongNext(Dong_Vertex* next)	//To�� �ش��ϴ�Dong_Vertex���� ������ Set�ϴ� �Լ�
{
	toDong_Next=next;
}

void Dong_Edge::SetFromDongNext(Dong_Vertex* next)	//From�� �ش��ϴ� Dong_Vertex�� Set�ϴ��Լ�
{
	fromDong_Next=next;
}

char* Dong_Edge::GetGuName()		//�ش� ���� �� �̸��� Get�ϴ� �Լ�
{
	return GuName;
}

char* Dong_Edge::GetFromDong()	//From�� �ش��ϴ� Dong�� �̸��� Get�ϴ� �Լ�
{
	return FromDong;
}

char* Dong_Edge::GetToDong()		//To�� �ش��ϴ� Dong�� �̸��� Get�ϴ� �Լ�
{
	return ToDong;
}

char* Dong_Edge::GetPipeStatus()	//Pipe�� ���¸� ��ȯ�ϴ� �Լ�
{
	return Pipestatus;
}

int Dong_Edge::GetLossRate()		//���ս����� ���� Get�ϴ� �Լ�
{
	return LossRate;
}

int Dong_Edge::GetOverlap()		//overlap������ ���� get�ϴ� �Լ�
{
	return overlap;
}

int Dong_Edge::GetUseflag()		//useflag�� ���� Get�ϴ� �Լ�
{
	return useflag;
}

Dong_Edge* Dong_Edge::GetENext()		//Dong_Edge�� Next�� Get�ϴ� �Լ�
{
	return E_Next;
}

Dong_Vertex* Dong_Edge::GetToDongNext()	//To�� �ش��ϴ�Dong_Vertex�� ��ȯ�ϴ� Get�Լ�
{
	return toDong_Next;
}

Dong_Vertex* Dong_Edge::GetFromDongNext()	//From�� �ش��ϴ� Dong_Vertex�� ��ȯ�ϴ� Get�Լ�
{
	return fromDong_Next;
}