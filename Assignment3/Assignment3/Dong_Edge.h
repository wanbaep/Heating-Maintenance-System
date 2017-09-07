#pragma once
#include<iostream>

using namespace std;
class Dong_Vertex;
class Dong_Edge
{
private:
	char* GuName;		//�� �̸��� ������ �迭�� ����ų ������
	char* FromDong;		//from�� �ش��ϴ� dong�� �̸��� ������ �迭�� ����ų ������
	char* ToDong;		//to�� �ش��ϴ� dong�� �̸��� ������ �迭�� ����ų ������
	char* Pipestatus;	//�ش� edge�� pipe ��� ���� ���� USE���� BROKEN����
	int LossRate;		//�������� ���ս������� ������ ����
	int overlap;	//MST ������, Min heap�� �ݴ�Ǵ� ������ �̹� �߰� �Ǿ����� Ȯ���ϱ� ���� flag
	int useflag;	//MST ������, �ش� Edge�� ���Ǿ����� Ȯ���ϱ� ���� flag
	Dong_Edge* E_Next;		//���� edge�� ����ų ������
	Dong_Vertex* toDong_Next;	//to�� �ش��ϴ� dong Node�� ����ų ������
	Dong_Vertex* fromDong_Next;	//from�� �ش��ϴ� dong Node�� ����ų ������
public:
	Dong_Edge(void);	//������
	~Dong_Edge(void);	//�Ҹ���

	void SetGuName(char* name);			//�ش� ���� ���̸��� Set�ϴ� �Լ�
	void SetFromDong(char* fromdong);	//From�� �ش��ϴ� Dong�� �̸��� Set�ϴ� �Լ�
	void SetToDong(char* todong);		//To�� �ش��ϴ� Dong�� �̸��� Set�ϴ� �Լ�
	void SetPipeStatus(char* pipe);		//pipe�� ���¸� Set�ϴ� �Լ�
	void SetLossRate1(char* rate);		//char ������ ���ս����� ���� Set�ϴ� �Լ�
	void SetLossRate2(int rate);		//int �����ս����� ���� Set�ϴ� �Լ�
	void SetOverlap(int ov);			//Edge�� �ߺ��� check�ϴ� ���� overlap���� set�ϴ��Լ�
	void SetUseflag(int flag);			//Edge�� ��뿩�θ� set�ϴ� �Լ�
	void SetENext(Dong_Edge* next);		//Dong_Edge�� Next�� Set�ϴ� �Լ�
	void SetToDongNext(Dong_Vertex* next);	//To�� �ش��ϴ�Dong_Vertex���� ������ Set�ϴ� �Լ�
	void SetFromDongNext(Dong_Vertex* next);	//From�� �ش��ϴ� Dong_Vertex���� ������ Set�ϴ� �Լ�

	char* GetGuName();		//�ش� ���� �� �̸��� Get�ϴ� �Լ�
	char* GetFromDong();	//From�� �ش��ϴ� Dong�� �̸��� Get�ϴ� �Լ�
	char* GetToDong();		//To�� �ش��ϴ� Dong�� �̸��� Get�ϴ� �Լ�
	char* GetPipeStatus();	//Pipe�� ���¸� Get�ϴ� �Լ�
	int GetLossRate();		//���ս����� ���� Get�ϴ� �Լ�
	int GetOverlap();		//overlap ���� Get�ϴ� �Լ�
	int GetUseflag();		//useflag ���� Get�ϴ� �Լ�
	Dong_Edge* GetENext();		//Dong_Edge�� Next�� Get�ϴ� �Լ�
	Dong_Vertex* GetToDongNext();	//To�� �ش��ϴ�Dong_Vertex�� ��ȯ�ϴ� �Լ�
	Dong_Vertex* GetFromDongNext();	//From�� �ش��ϴ� Dong_Vertex�� ��ȯ�ϴ� �Լ�
};

