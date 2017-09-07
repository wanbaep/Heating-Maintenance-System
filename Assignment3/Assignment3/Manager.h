#pragma once

#include<fstream>
#include"Gu_Vertex.h"
#include"LinkedList.h"
#include"AdjacencyList.h"
#include"SpanningTree.h"

class Manager
{
private:
	LinkedList linklist;	//LinkedList type의 변수 선언
	AdjacencyList adjacency;	//AdjacencyList type의 변수 선언
	SpanningTree sptree;		//SpanningTree type의 변수 선언
public:
	Manager(void);		//생성자
	~Manager(void);		//소멸자

	bool Command(char* filename);	//Command file을 읽어서 실행하는 함수
	bool Load(char* guvertex, char* guedge, char* dongvertex, char* dongedge, char* mechanic);	//Load file을 받아서 gu, don vertex & edge를 실행해주는 함수
	bool LoadGuVertex(char* filename);	//Gu Vertex를 Load하는 함수
	bool LoadGuEdge(char* filename);	//Gu Edge를 Load하는 함수
	bool LoadDongVertex(char* filename);	//Dong Vertex를 Load하는 함수
	bool LoadDongEdge(char* filename);		//Dong Edge를 Load하는 함수
	bool LoadMechanic(char* filename);		//Mechanic정보를 Load하는 함수
	bool MST();	//열수도에 대해서 MST를 구성하는 함수
	bool Update(char* filename);			//Update 함수
	bool PipeBroken(char* guname, char* fromdong, char* todong);	//PipeBroken 명령어 수행 함수
	bool PipeRepair(char* guname);			//PipeRepair 명령어 수행 함수
	bool Save();		//Save명령어 수행함수
	bool SaveGuVertex();	//Gu Vertex에 대한 Save함수
	bool SaveGuEdge();		//Gu Edge에 대한 Save함수
	bool SaveDongVertex();	//Dong Vertex에 대한 Save함수
	bool SaveDongEdge();	//Dong Edge에 대한 Save함수
	bool SaveMechanic();	//정비사에 대한 Save함수
	bool PrintMap();		//지도 출력 함수
	bool PrintPipe(Gu_Vertex* GuNode);	//구의 파이프 출력 함수
	bool PrintMechanic();		//정비사 출력 함수
	
};

