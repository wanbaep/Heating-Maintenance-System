#pragma once

#include<iostream>

using namespace std;

class Mechanic
{
private:
	char* Name;	//����� �̸�
	char* Workplace;	//���� �ٹ���
	int dist;
	Mechanic* pNext;
public:
	Mechanic(void);	//������& �Ҹ���
	~Mechanic(void);

	//Set�Լ�
	void SetName(char* pname);		//������� �̸��� Set�ϴ� �Լ�
	void SetWorkPlace(char* place);	//������� �ٹ����� Set�ϴ� �Լ�
	void SetDist(int d);			//����簡 ��������� ������������ �Ÿ��� Set�ϴ� �Լ�
	void SetNext(Mechanic* next);	//���� ����縦 Set�ϴ� �Լ�

	//Get�Լ�
	char* GetName();		//������� �̸��� Get�ϴ� �Լ�
	char* GetWorkPlace();	//������� �ٹ����� Get�ϴ� �Լ�
	int GetDist();			//������� �̵� �Ÿ��� Get�ϴ� �Լ�
	Mechanic* GetNext();	//���� ����� Node�� Get�ϴ� �Լ�
};

