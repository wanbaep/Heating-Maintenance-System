#pragma once

#include"Gu_Edge.h"
#include"Dong_Vertex.h"


class Gu_Vertex
{
private:
	char* GuName;	//�ش� ���� �̸��� ����ų ������
	int dongnum;	//�ش� ���� ���ϴ� ���� ������ count�ϴ� ����
	int* arr;		//�ش� ���� ���ϴ� ���� ������ ���� �迭�� �����Ҵ� �ϴ� ����
	int cost;		//��ǥ Node���� �ش� Node���� �ɸ��� �Ÿ��� ��
	bool visit;		//Shortest Path tree ���� ���� �ش� Node�� �湮�ߴ��� Ȯ���ϴ� ����
	Gu_Vertex* GV_Next;	//���� Gu Vertex�� ����ų ������
	Gu_Edge* GE_Next;	//�ش� Gu Vertex�� Edge�� ����ų ������
	Dong_Vertex* D_Next;	//�ش� Gu Vertex�� head�� Dong�� ����ų ������
	Gu_Vertex* S_Next;	//���ÿ��� ��� Next ������
public:
	Gu_Vertex(void);	//������
	~Gu_Vertex(void);	//�Ҹ���

	//Set�Լ�
	void SetGuName(char* name);	//�ش� Gu�� �̸��� Set�ϴ� �Լ�
	void IncreaseDongNum();		//���ԵǴ� Dong�� ������ ������Ű�� �Լ�
	void SetArray(int num);		//MST���� ���� Array�� Set�ϴ� �Լ�
	void SetCost(int co);		//Dijkstra���� ���� Cost�� Set�ϴ� �Լ�
	void SetVisit(bool vis);	//Dijkstra���� ���� Visit�� ���ؼ� Set�ϴ� �Լ�
	void SetGVNext(Gu_Vertex* next);	//Gu Vertex�� ������ Set�ϴ� �Լ�
	void SetGENext(Gu_Edge* next);		//Gu Edge�� Set�ϴ� �Լ�
	void SetDNext(Dong_Vertex* next);	//head�� �ش��ϴ� Dong Vertex�� Set�ϴ� �Լ�
	void SetSNext(Gu_Vertex* next);		//stack���� ����� Gu Vertex�� ����Ű�� �����͸� Set�ϴ� �Լ�

	//Get�Լ�
	char* GetGuName();	//GuName�� Get�ϴ��Լ�
	int GetDongNum();	//DongNum�� Get�ϴ��Լ�
	int* GetArray();	//Vertex�� array�� Get�ϴ��Լ�
	int GetCost();		//Cost ���� Get�ϴ� �Լ�
	bool GetVisit();	//vidst���� Get�ϴ� �Լ�
	Gu_Vertex* GetGVNext();	//���� Gu Vertex�� Get�ϴ� �Լ�
	Gu_Edge* GetGENext();	//���� Gu Edge�� Get�ϴ� �Լ�
	Dong_Vertex* GetDNext();	//head Dong�� Get�ϴ� �Լ�
	Gu_Vertex* GetSNext();		//Stack�� Next�� Get�ϴ� �Լ�
};

