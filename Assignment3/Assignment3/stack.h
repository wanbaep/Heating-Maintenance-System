#pragma once
#include"Gu_Vertex.h"

class stack
{
private:
	Gu_Vertex* m_pHead;	//head�� ����ų ����

public:
	stack(void);	//������&�Ҹ���
	~stack(void);

	bool IsEmpty(); //����ִ� -> return true, //���� �ִ� -> return false
	bool Push(Gu_Vertex* pNode); //push (����) //�� ���� push�� ���� ������ false return
	Gu_Vertex* Pop();          //Pop stack�� ��� ���� ���߿����Ե� Node�� return

};