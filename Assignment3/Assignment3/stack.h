#pragma once
#include"Gu_Vertex.h"

class stack
{
private:
	Gu_Vertex* m_pHead;	//head를 가리킬 변수

public:
	stack(void);	//생성자&소멸자
	~stack(void);

	bool IsEmpty(); //비어있다 -> return true, //뭔가 있다 -> return false
	bool Push(Gu_Vertex* pNode); //push (삽입) //꽉 차서 push가 되지 않으면 false return
	Gu_Vertex* Pop();          //Pop stack의 경우 가장 나중에삽입된 Node를 return

};