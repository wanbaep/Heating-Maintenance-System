#pragma once
#include"Dong_Edge.h"

class Dong_Vertex
{
private:
	char* GuName;		//�ش� ���� Gu�� �̸��� ����ų ������
	char* DongName;		//���� �̸��� ����ų ������
	char* HeatCheck;	//���ս����� ����ų ������
	int index;			//MST kruskal���� ����� �迭������ index�� ��Ÿ���� ����
	Dong_Vertex* DV_Next;	//���� Dong�� ����ų ������
	Dong_Edge* DE_Next;		//�ش� Dong Vertex�� ����� edge�� ����ų ������

public:
	Dong_Vertex(void);			//������
	~Dong_Vertex(void);			//�Ҹ���

	void SetGuName(char* name);		//Gu�� �̸��� Set�ϴ� �Լ�
	void SetDongName(char* name);	//Dong�� �̸��� Set�ϴ� �Լ�
	void SetHeatCheck(char* check);	//���� ������ ���θ� Set�ϴ� �Լ�
	void SetIndex(int num);				//index�� Set�ϴ� �Լ�
	void SetDVNext(Dong_Vertex* next);	//Dong Vertex�� Next�� DV_Next�� Set�ϴ� �Լ�
	void SetDENext(Dong_Edge* next);	//Dong Edge�� Next�� DE_Next�� Set�ϴ� �Լ�

	char* GetGuName();			//Gu�� �̸��� Get�ϴ� �Լ�
	char* GetDongName();		//Dong�� �̸��� Get�ϴ� �Լ�
	char* GetHeatCheck();		//���� ������ ���θ� Get�ϴ� �Լ�
	int GetIndex();				//index���� Get�ϴ� �Լ�
	Dong_Vertex* GetDVNext();	//Dong Vertex�� Next�� DV_Next�� Get�ϴ� �Լ�
	Dong_Edge* GetDENext();		//Dong Edge�� Next�� DE_Next�� Get�ϴ� �Լ�
};

