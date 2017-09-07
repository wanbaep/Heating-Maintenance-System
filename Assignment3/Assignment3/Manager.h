#pragma once

#include<fstream>
#include"Gu_Vertex.h"
#include"LinkedList.h"
#include"AdjacencyList.h"
#include"SpanningTree.h"

class Manager
{
private:
	LinkedList linklist;	//LinkedList type�� ���� ����
	AdjacencyList adjacency;	//AdjacencyList type�� ���� ����
	SpanningTree sptree;		//SpanningTree type�� ���� ����
public:
	Manager(void);		//������
	~Manager(void);		//�Ҹ���

	bool Command(char* filename);	//Command file�� �о �����ϴ� �Լ�
	bool Load(char* guvertex, char* guedge, char* dongvertex, char* dongedge, char* mechanic);	//Load file�� �޾Ƽ� gu, don vertex & edge�� �������ִ� �Լ�
	bool LoadGuVertex(char* filename);	//Gu Vertex�� Load�ϴ� �Լ�
	bool LoadGuEdge(char* filename);	//Gu Edge�� Load�ϴ� �Լ�
	bool LoadDongVertex(char* filename);	//Dong Vertex�� Load�ϴ� �Լ�
	bool LoadDongEdge(char* filename);		//Dong Edge�� Load�ϴ� �Լ�
	bool LoadMechanic(char* filename);		//Mechanic������ Load�ϴ� �Լ�
	bool MST();	//�������� ���ؼ� MST�� �����ϴ� �Լ�
	bool Update(char* filename);			//Update �Լ�
	bool PipeBroken(char* guname, char* fromdong, char* todong);	//PipeBroken ��ɾ� ���� �Լ�
	bool PipeRepair(char* guname);			//PipeRepair ��ɾ� ���� �Լ�
	bool Save();		//Save��ɾ� �����Լ�
	bool SaveGuVertex();	//Gu Vertex�� ���� Save�Լ�
	bool SaveGuEdge();		//Gu Edge�� ���� Save�Լ�
	bool SaveDongVertex();	//Dong Vertex�� ���� Save�Լ�
	bool SaveDongEdge();	//Dong Edge�� ���� Save�Լ�
	bool SaveMechanic();	//����翡 ���� Save�Լ�
	bool PrintMap();		//���� ��� �Լ�
	bool PrintPipe(Gu_Vertex* GuNode);	//���� ������ ��� �Լ�
	bool PrintMechanic();		//����� ��� �Լ�
	
};

