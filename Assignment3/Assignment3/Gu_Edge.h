#pragma once

class Gu_Vertex;
class Gu_Edge
{
private:
	char* FromGu;	//������� �Ǵ� Gu Vertex�� �̸�����
	char* ToGu;		//�������� �Ǵ� Gu Vertex�� �̸�����
	int distance;	//�Ÿ��� ������ ����
	Gu_Edge* E_Next;	//���� edge�� ����ų ����
	Gu_Vertex* toGu_Next;	//to�� �ش��ϴ� Vertex�� ����Ű�� ����
public:
	Gu_Edge(void);	//������
	~Gu_Edge(void);	//�Ҹ���

	void SetFromGu(char* fromgu);	//From�� �ش��ϴ� Gu�� �̸��� set�ϴ� �Լ�
	void SetToGu(char* togu);		//to�� �ش��ϴ� Gu�� �̸��� Set�ϴ� �Լ�
	void SetDist1(char* dist);		//char�� distance�� �ش��ϴ� ���� Set�ϴ� �Լ�
	void SetDist2(int dist);		//int�� distance�� �ش��ϴ� ���� set�ϴ� �Լ�
	void SetENext(Gu_Edge* next);	//���� Gu Vertex�� edge�� ����ų ������
	void SetToGuNext(Gu_Vertex* next);	//to�� �ش��ϴ� vertex�� �� ������ set�ϴ� �Լ�

	char* GetFromGu();	//from�� �ش��ϴ� gu�̸��� get�ϴ� �Լ�
	char* GetToGu();	//to�� �ش��ϴ� gu�� �̸��� Get�ϴ� �Լ�
	int GetDist();		//distance�� ���� Get�ϴ� �Լ�
	Gu_Edge* GetENext();	//���� Edge�� ����ų ������
	Gu_Vertex* GetToGuNext();	//To�� �ش��ϴ� vertex�� get�ϴ� �Լ�
};

