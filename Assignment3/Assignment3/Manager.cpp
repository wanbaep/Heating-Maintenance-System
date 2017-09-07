#include "Manager.h"


Manager::Manager(void)	//������
	:linklist(), adjacency(), sptree()	//��ü ������ ȣ��
{
	ofstream fout("repair_log.txt");	//repair_log text file open
	ofstream fout1("map.txt");			//map text file open
	ofstream fout2("pipe.txt");			//pipe text file open
	ofstream fout3("mechanic_list.txt");	//mechanic text file open

	fout.close();	//������ file �ݱ�
	fout1.close();
	fout2.close();
	fout3.close();
}


Manager::~Manager(void)	//�Ҹ���
{
}

bool Manager::Command(char* filename)	//Command file�� �о �����ϴ� �Լ�
{
	ifstream fin(filename);	//������ ����

	if(!fin.is_open())	//������ ������ �ʾ��� ��,
		return false;	//���й�ȯ

	char str[100]={'\0'};	//���Ͽ��� ���پ� �о ������ �迭
	char* token=NULL;		//str���� �ʿ��� �κ��� ����ų ������
	int len=0;			//token�� ���̸� ������ ����
	int count=0;		//factor�� ������ ��Ƹ� ����
	int loadable=0;		//ó�� Load����, �� ���� Load������ Ȯ���� ����
	char* command=NULL;	//command���� ����ų ������

	/////////////////////factor���� command file���� �� command�� ���� �ΰ����� ���׿� ���� �������� �ִ� 5�� ���� �����Ѵ�
	char* factor1=NULL;	//factor1�� ����ų ������
	char* factor2=NULL;	//factor2�� ����ų ������
	char* factor3=NULL;	//factor3�� ����ų ������
	char* factor4=NULL;	//factor4�� ����ų ������
	char* factor5=NULL;	//factor5�� ����ų ������

	fin.getline(str,100);	//������ ���� �д´�
	fin.getline(str,100);	//������ ���� �д´�
	fin.getline(str,100);	//������ ���� �д´�
	memset(str,0,100);		//�迭 �ʱ�ȭ

	while(!fin.eof())	//file�� ����� �� ����
	{
		fin.getline(str,100);	//������ �о�´�
		len=0;			//���̸� 0���� �ʱ�ȭ
		count=0;		//count�� �ʱ�ȭ

		if(str[0]==0)	//Enter key �Է½�����
			break;

		token=strtok(str," /");	//tap�� /�� ���� token�� ����
		len=strlen(token);		//token�� ��������
		command=new char[len+1];	//�����Ҵ�
		memset(command,0,len+1);	//�ʱ�ȭ
		strcpy(command,token);		//���� copy

		token=strtok(NULL," /");	//token�� ���� ����
		if(token!=NULL)	//token�� �����ϸ�
		{
			len=strlen(token);	//token�� ��������
			factor1=new char[len+1];	//�����Ҵ�
			memset(factor1,0,len+1);	//�ʱ�ȭ
			strcpy(factor1,token);		//���� copy
			count++;	//count==1

			token=strtok(NULL," /");	//token�� ���� ����
			if(token!=NULL)
			{
				len=strlen(token);	//token�� ���� ����
				factor2=new char[len+1];	//�����Ҵ�
				memset(factor2,0,len+1);	//�ʱ�ȭ
				strcpy(factor2,token);		//���� copy
				count++;	//count==2

				token=strtok(NULL," /");	//token�� ���� ����
				if(token!=NULL)
				{
					len=strlen(token);	//token�� ���� ����
					factor3=new char[len+1];	//�����Ҵ�
					memset(factor3,0,len+1);	//�ʱ�ȭ
					strcpy(factor3,token);		//���� copy
					count++;	//count==3

					token=strtok(NULL," /");	//token�� ���� ����
					if(token!=NULL)
					{
						len=strlen(token);	//token�� ���� ����
						factor4=new char[len+1];	//�����Ҵ�
						memset(factor4,0,len+1);	//�ʱ�ȭ
						strcpy(factor4,token);	//���� copy
						count++;	//count==4

						token=strtok(NULL," /");	//token�� ���� ����
						if(token!=NULL)
						{
							len=strlen(token);
							factor5=new char[len+1];
							memset(factor5,0,len+1);
							strcpy(factor5,token);
							count++;	//count==5
						}
					}
				}
			}
		}

		if(strcmp(command,"LOAD")==0) //5�� file load, Format : LOAD gu_vertex.txt,gu_edge.txt, dong_vertex.txt, dong_edge.txt, mechanic.txt
		{
			if(loadable==0)
			{
				this->Load(factor1, factor2, factor3, factor4, factor5);
				loadable=1;
			}
			else
			{
				////�����Ҵ� ����
				linklist.DeleteDongList();
				linklist.DeleteGuList();
				linklist.DeleteMechanic();
				this->Load(factor1, factor2, factor3, factor4, factor5);
			}
		}
		else if(strcmp(command,"UPDATE")==0) //1�� file load, Format : UPDATE update_dong_edge_cost.txt
		{
			this->Update(factor1);
		}
		else if(strcmp(command,"PIPE_BROKEN")==0) //3�� factor, Format : PIPE_BROKEN ����� / ���1�� / ���2��
		{
			this->PipeBroken(factor1, factor2, factor3);
		}
		else if(strcmp(command,"PIPE_REPAIR")==0) //1�� factor, Format : PIPE_REPAIR ������
		{
			this->PipeRepair(factor1);
		}
		else if(strcmp(command,"SAVE")==0)	//No factor, Format : SAVE
		{
			this->Save();
		}
		else if(strcmp(command,"PRINT")==0) //1�� factor, Format : (1). PRINT �����, (2). PRINT ����, (3). PRINT �����
		{
			if(strcmp(factor1,"����")==0)	//������ ���� ���
			{
				this->PrintMap();
			}
			else if(strcmp(factor1,"�����")==0)	//����翡 ���� ���
			{
				this->PrintMechanic();
			}
			else	//���̸�
			{
				Gu_Vertex* GuNode=linklist.FindGu(factor1);	//�ش� Gu �̸��� �ش��ϴ� Gu Vertex�� ã�´�
				this->PrintPipe(GuNode);	//������ ���
			}
		}
		else if(strcmp(command,"EXIT")==0)	//Format : EXIT
		{
			return true;
		}
		else
		{
			cout<<command<<" is Not Exist COMMAND!"<<endl;	//�̿��� command�� ���°��
		}

		//�����Ҵ� ����
		delete[] command;	//command�����Ҵ� ����
		if(count>=1)	//count�� 1���� ū���
		{
			delete[] factor1;	//factor1�����Ҵ� ����
			if(count>=2)	//count�� 2���� ū���
			{
				delete[] factor2;	//factor2�����Ҵ� ����
				if(count>=3)	//count�� 3���� ū ���
				{
					delete[] factor3;	//factor3�����Ҵ� ����
					if(count>=4)	//count�� 4���� ū ���
					{
						delete[] factor4;	//factor4�����Ҵ� ����
						if(count==5)	//count�� 5���� ū���
							delete[] factor5;	//factor5�����Ҵ� ����
					}
				}
			}
		}

		memset(str,0,100);	//�迭 �ʱ�ȭ
	}

	fin.close();	//������ �ݴ´�.

	return true;
}

bool Manager::Load(char* guvertex, char* guedge, char* dongvertex, char* dongedge, char* mechanic)	//Load file�� �޾Ƽ� gu, don vertex & edge�� �������ִ� �Լ�
{
	this->LoadGuVertex(guvertex);	//Gu Vertex�� ���� Load

	this->LoadGuEdge(guedge);	//Gu Edge�� ���� Load

	this->LoadDongVertex(dongvertex);	//Dong Vertex�� ���� Load

	this->LoadDongEdge(dongedge);	//Dong Edge�� ���� Load

	this->LoadMechanic(mechanic);	//����翡 ���� Load

	this->MST();		//Load�ÿ� ��� Gu�� ���� MST����

	return true;	//�Լ�����
}

bool Manager::LoadGuVertex(char* filename)	//GuVertex�� �о���� �Լ�
{
	ifstream fin(filename);	//���� ����

	if(!fin.is_open())	//������ �ʴ´ٸ�
		return false;	//���й�ȯ

	char str[50]={'\0'};	//���� �о�� �迭
	char* token=NULL;	//������ �ּҸ� ����ų ������
	int len=0;			//token�� ����
	char* guname=NULL;	//���� �̸��� ������ �迭

	fin.getline(str,50);	//������ ���� 3�� �б�
	fin.getline(str,50);
	fin.getline(str,50);
	memset(str,0,50);		//�迭 �ʱ�ȭ

	while(!fin.eof())	//������ ����� �� ����
	{
		fin.getline(str,50);	//���������� �д´�

		if(str[0]==0)	//Enter key �Է½�����
			break;

		token=strtok(str,"\t");	//token�� ���ϴ� ���ڿ��� ����Ų��
		len=strlen(token);		//���� ����
		guname=new char[len+1];	//�����Ҵ�
		memset(guname,0,len+1);	//�ʱ�ȭ
		strcpy(guname,token);	//���� copy

		///Insert
		Gu_Vertex* pNode=new Gu_Vertex();	//Gu Vertex �����Ҵ�
		pNode->SetGuName(guname);		//���� Set ���� �̸�
		linklist.InsertGuVertex(pNode);	//linklist ������ Insert Gu �Լ� ȣ��

		delete pNode;	//�����Ҵ� ����
		delete[] guname;
		len=0;	//���� �ʱ�ȭ
		memset(str,0,50);	//�迭 �ʱ�ȭ
	}

	fin.close();	//������ �ݴ´�.

	return true;	//�Լ�����
}

bool Manager::LoadGuEdge(char* filename)	//GuEdge�� �о���� �Լ�
{
	ifstream fin(filename);	//������ ����

	if(!fin.is_open())	//������ ���� ���
		return false;

	char str[150]={'\0'};	//�迭����
	char* token=NULL;	//���ϴ� �κ��� ����ų ������
	int len=0;		//token�� �������� �����Һ���
	char* fromgu=NULL;	//fromgu�� ������ ����ų ������
	char* togu=NULL;	//togu�� ������ ����ų ������
	char* dist=NULL;	//dist�� ������ ����ų ������

	fin.getline(str,150);	//������ 3���� �о�´�
	fin.getline(str,150);
	fin.getline(str,150);
	memset(str,0,150);		//�ʱ�ȭ

	while(!fin.eof())	//������ ����� �� ����
	{
		fin.getline(str,150);	//���� �����д´�

		if(str[0]==0)	//enterŰ �Է½� ����
			break;

		token=strtok(str,"\t");	//token�� tap���� ������
		len=strlen(token);		//���� ����
		fromgu=new char[len+1];	//�����Ҵ�
		memset(fromgu,0,len+1);	//�ʱ�ȭ
		strcpy(fromgu,token);	//���� copy

		token=strtok(NULL,"\t");	//token�� tap���� ������
		len=strlen(token);		//��������
		togu=new char[len+1];	//�����Ҵ�
		memset(togu,0,len+1);	//�ʱ�ȭ
		strcpy(togu,token);		//���� copy

		token=strtok(NULL,"\t");	//token�� tap���� ������
		len=strlen(token);		//��������
		dist=new char[len+1];	//�����Ҵ�
		memset(dist,0,len+1);	//�ʱ�ȭ
		strcpy(dist,token);	//���� copy

		Gu_Edge* pNode=new Gu_Edge();	//Gu Edge type�� ���� �����Ҵ�
		pNode->SetFromGu(fromgu);	//Fromgu, Togu, dist�� ���� Set�Ѵ�
		pNode->SetToGu(togu);
		pNode->SetDist1(dist);

		adjacency.InsertGuEdge(linklist,pNode);	//��������Ʈ���� Gu�� Edge�� �����Ѵ�

		delete pNode;	//�����Ҵ� ����
		delete[] fromgu;
		delete[] togu;
		delete[] dist;
		len=0;	//���� �ʱ�ȭ
		memset(str,0,150);	//�迭 �ʱ�ȭ
	}

	fin.close();	//������ �ݴ´�.

	return true;	//�Լ�����
}

bool Manager::LoadDongVertex(char* filename)	//DongVertex�� �о���� �Լ�
{
	ifstream fin(filename);	//���� open

	if(!fin.is_open())	//������ �ʾҴٸ�
		return false;	//���� ��ȯ

	char str[100]={'\0'};	//���� ������ ������ �迭����
	char* token=NULL;	//token�� NULL�� ����Ų��
	int len=0;		//���̴� 0�� �ȴ�
	char* guname=NULL;	//guname�� ������ ������ ������
	char* dongname=NULL;	//dongname�� ������ ������ ������
	char* heatcheck=NULL;	//�� �ս����� ������ ������

	fin.getline(str,100);	//������ 3���� �д´�
	fin.getline(str,100);
	fin.getline(str,100);
	memset(str,0,100);	//�迭 �ʱ�ȭ

	while(!fin.eof())	//������ ����� �� ���� �ݺ��� ����
	{
		fin.getline(str,100);	//���� ������ �д´�

		if(str[0]==0)	//enter key�����
			break;		//�ݺ�������

		token=strtok(str,"\t");	//token�� guname�κ��� ����Ų��
		len=strlen(token);		//���� ����
		guname=new char[len+1];	//�����Ҵ�
		memset(guname,0,len+1);	//�迭 �ʱ�ȭ
		strcpy(guname,token);	//���� copy�Ѵ�

		token=strtok(NULL,"\t");	//token�� dongname�κ��� ����Ų��
		len=strlen(token);			//���� ����
		dongname=new char[len+1];	//�����Ҵ�
		memset(dongname,0,len+1);	//�迭 �ʱ�ȭ
		strcpy(dongname,token);		//���� copy�Ѵ�

		token=strtok(NULL,"\t");	//token�� heatcheck�� ����Ų��
		len=strlen(token);			//��������
		heatcheck=new char[len+1];	//�����Ҵ�
		memset(heatcheck,0,len+1);	//�迭 �ʱ�ȭ
		strcpy(heatcheck,token);	//���� copy�Ѵ�

		Dong_Vertex* pNode=new Dong_Vertex();	//Dong Vertex type ���� �Ҵ�
		pNode->SetGuName(guname);		//guname�� set�Ѵ�
		pNode->SetDongName(dongname);	//dongname�� set�Ѵ�
		pNode->SetHeatCheck(heatcheck);	//���ս��� set

		linklist.InsertDongVertex(pNode);	// Dong Vertex�� linklist����Լ� insertDongVertex�� ȣ���ؼ� ����

		delete pNode;	//�����Ҵ�����
		delete[] guname;
		delete[] dongname;
		delete[] heatcheck;
		len=0;	//���� �ʱ�ȭ
		memset(str,0,100);	//�迭 �ʱ�ȭ
	}

	fin.close();	//������ �ݴ´�.

	return true;	//�Լ�����
}

bool Manager::LoadDongEdge(char* filename)	//DongEdge�� �о���� �Լ�
{
	ifstream fin(filename);	//���� open

	if(!fin.is_open())	//������ ������ �ʴ´ٸ�
		return false;	//���й�ȯ

	char str[150]={'\0'};	//���� ������ ������ �迭
	char* token=NULL;	//���ϴ� �κ��� ����ų ������
	int len=0;		//���̸� ������ ����
	char* guname=NULL;	//guname�� ������ ������
	char* fromdong=NULL;	//fromdong�� ������ ������
	char* todong=NULL;		//todong�� ������ ������
	char* Lossrate=NULL;	//Lossrate�� ������ ������

	fin.getline(str,150);	//������ 3���� �д´�
	fin.getline(str,150);
	fin.getline(str,150);
	memset(str,0,150);	//�迭 �ʱ�ȭ

	while(!fin.eof())	//������ ����� �� ����
	{
		fin.getline(str,150);	//���� ������ �д´�

		if(str[0]==0)	//Enter �Է½�
			break;	//�ݺ��� ����

		token=strtok(str,"\t");	//token�� guname�� ����Ų��
		len=strlen(token);	//��������
		guname=new char[len+1];	//guname�����Ҵ�
		memset(guname,0,len+1);	//�迭�ʱ�ȭ
		strcpy(guname,token);	//���� copy

		token=strtok(NULL,"\t");	//token�� fromdong������ ����Ų��
		len=strlen(token);	//��������
		fromdong=new char[len+1];	//fromdong�����Ҵ�
		memset(fromdong,0,len+1);	//�迭 �ʱ�ȭ
		strcpy(fromdong,token);	//���� copy

		token=strtok(NULL,"\t");	//token�� todong������ ����Ų��
		len=strlen(token);		//��������
		todong=new char[len+1];	//todong�����Ҵ�
		memset(todong,0,len+1);	//�迭 �ʱ�ȭ
		strcpy(todong,token);	//���� copy

		token=strtok(NULL,"\t");	//token�� Lossrate������ ����Ų��
		len=strlen(token);		//��������
		Lossrate=new char[len+1];	//Lossrate�����Ҵ�
		memset(Lossrate,0,len+1);	//�迭 �ʱ�ȭ
		strcpy(Lossrate,token);	//���� copy

		Dong_Edge* pNode=new Dong_Edge();	//Dong Edge�����Ҵ�
		pNode->SetGuName(guname);		//guname Set
		pNode->SetFromDong(fromdong);	//fromdong Set
		pNode->SetToDong(todong);		//todong Set
		pNode->SetLossRate1(Lossrate);	//Lossrate Set
		pNode->SetPipeStatus("USE");		//��� ����

		adjacency.InsertDongEdge(linklist,pNode);	//���� ����Ʈ�� insertDongEdge �Լ��� �̿��ؼ� Dong Edge�� ����

		delete pNode;	//�����Ҵ� ����
		delete[] guname;
		delete[] fromdong;
		delete[] todong;
		delete[] Lossrate;
		len=0;	//���� �ʱ�ȭ
		memset(str,0,150);	//�迭 �ʱ�ȭ
	}

	fin.close();	//������ �ݴ´�.

	return true;	//�Լ�����
}

bool Manager::LoadMechanic(char* filename)	//Mechanic�� �о���� �Լ�
{
	ifstream fin(filename);	//���� open

	if(!fin.is_open())	//������ ������ ������
		return false;	//���й�ȯ

	char str[100]={'\0'};	//���� ���� ������ ������ �迭
	char* token=NULL;	//���ϴ� data�� ����ų ������
	int len=0;	//���� ����
	char* workplace=NULL;	//�ٹ����� ����ų ������
	char* name=NULL;		//�̸��� ����ų ������

	fin.getline(str,100);	//������ 3���� �о�´�
	fin.getline(str,100);
	fin.getline(str,100);
	memset(str,0,100);	//�迭 �ʱ�ȭ

	while(!fin.eof())	//����������� �� ���� ����
	{
		fin.getline(str,100);	//���� ������ �о�´�

		if(str[0]==0)	//Enter�� �о����
			break;	//���� ����

		token=strtok(str,"\t");	//token�� �ٹ����� ����Ų��
		len=strlen(token);		//��������
		workplace=new char[len+1];	//�����Ҵ�
		memset(workplace,0,len+1);	//�ʱ�ȭ
		strcpy(workplace,token);	//���� copy

		token=strtok(NULL,"\t");	//token�� �̸��� ����Ų��
		len=strlen(token);	//��������
		name=new char[len+1];	//�����Ҵ�
		memset(name,0,len+1);	//�ʱ�ȭ
		strcpy(name,token);		//���� copy

		Mechanic* pNode=new Mechanic();	//Mechanic type�� ������ �����Ҵ�
		pNode->SetWorkPlace(workplace);	//�ٹ����� �̸� Set
		pNode->SetName(name);

		linklist.InsertMechanic(pNode);	//linklist ��ü�� ����Լ� insertMechanic�Լ��� ȣ���ؼ� Node����

		delete pNode;	//�����Ҵ� ����
		delete[] name;
		delete[] workplace;
		len=0;	//���� �ʱ�ȭ
		memset(str,0,100);	//�迭 �ʱ�ȭ
	}

	fin.close();	//������ �ݴ´�.

	return true;	//�Լ� ����
}

bool Manager::Update(char* filename)	//Update�Լ�
{
	ifstream fin(filename);	//���� open

	if(!fin.is_open())	//������ ������ �ʾѴٸ�
		return false;	//����

	char str[150]={'\0'};	//������ ������ ������ �迭
	char* token=NULL;	//���ϴ� Data�� ����ų ������
	int len=0;	//���̸� ������ ����
	char* guname=NULL;	//guname������ ������ ����
	char* fromdong=NULL;	//fromdong������ ����ų ������
	char* todong=NULL;		//todong������ ����ų ������
	char* Lossrate=NULL;	//Lossrate������ ����ų ������
	bool Mstcheck=false;	//Mst�� �����Ǿ����� Ȯ���� ����
	Dong_Vertex* pDfrom=NULL;	//From�� �ش��ϴ� Dong Vertex�� ����ų ������
	Dong_Vertex* pDto=NULL;		//To�� �ش��ϴ� Dong Vertex�� ����ų ������
	Dong_Edge* pFE=NULL;		//From�� �ش��ϴ� Dong Vertex�� Edge�� ����ų ������
	Dong_Edge* pTE=NULL;		//To�� �ش��ϴ� Dong Vertex�� Edge�� ����ų ������

	fin.getline(str,150);	//������ 3���� �д´�
	fin.getline(str,150);
	fin.getline(str,150);
	memset(str,0,150);	//�迭 �ʱ�ȭ

	while(!fin.eof())	//������ ����� �� ����
	{
		fin.getline(str,150);	//���� ������ �д´�

		if(str[0]==0)	//Enter �Է½�
			break;	//�ݺ��� ����

		token=strtok(str,"\t");	//token�� guname������ ����Ų��
		len=strlen(token);	//��������
		guname=new char[len+1];	//�����Ҵ�
		memset(guname,0,len+1);	//�迭 �ʱ�ȭ
		strcpy(guname,token);	//���� copy

		token=strtok(NULL,"\t");	//token�� fromdong������ ����Ų��
		len=strlen(token);	//���� ����
		fromdong=new char[len+1];	//�����Ҵ�
		memset(fromdong,0,len+1);	//�迭 �ʱ�ȭ
		strcpy(fromdong,token);		//���� copy

		token=strtok(NULL,"\t");	//token�� todong������ ����Ų��
		len=strlen(token);	//��������
		todong=new char[len+1];	//�����Ҵ�
		memset(todong,0,len+1);	//�迭 �ʱ�ȭ
		strcpy(todong,token);	//���� copy

		token=strtok(NULL,"\t");	//token�� Lossrate������ ����Ų��
		len=strlen(token);		//��������
		Lossrate=new char[len+1];	//�����Ҵ�
		memset(Lossrate,0,len+1);	//�迭 �ʱ�ȭ
		strcpy(Lossrate,token);	//���� copy

		pDfrom=linklist.FindDong(guname,fromdong);	//�ҷ��� edge�� from�� �ش��ϴ� Dong_Vertex
		pFE=pDfrom->GetDENext();		//pDfrom ���� edge�� Ž���� ������

		while(pFE!=NULL)	//Dong�� Edge�� �ִٸ�
		{
			if(strcmp(pFE->GetToDong(),todong)==0)	//Edge�� ToDong�� �̸��� todong�� ��ġ�Ѵٸ�
				break;	//�ݺ��� ����
			pFE=pFE->GetENext();	//���� Edge�� �̵�
		}
		if(pFE!=NULL)	//from�� �ش��ϴ� edge�� �ִ°��
		{
			pDto=linklist.FindDong(guname,todong);	//�ҷ��� edge�� to�� �ش��ϴ� Dong_Vertex
			pTE=pDto->GetDENext();		//pDto ���� edge�� Ž���� ������

			while(pTE!=NULL)	//ToDong�� Edge�� �ִٸ�
			{
				if(strcmp(pTE->GetToDong(),fromdong)==0)	//Edge�� ToDong�� fromdong�� ��ġ�Ѵٸ�
					break;	//�ݺ��� ����
				pTE=pTE->GetENext();	//���� Edge�� �̵�
			}
		}

		Gu_Vertex* pGNode=linklist.FindGu(guname);	//update ���Ͽ��� �о�� Dong_Edge�� Gu_Vertex ����

		if(pFE==NULL)	//�ش� edge�� ���� ��� Edge ����
		{
			Dong_Edge* pNode1=new Dong_Edge();	//from ���� to�� �ش��ϴ� Dong_Edge ����
			pNode1->SetGuName(guname);		//���� �����Ҵ� ��, Node�� ������ Set�Ѵ�
			pNode1->SetFromDong(fromdong);
			pNode1->SetToDong(todong);
			pNode1->SetLossRate1(Lossrate);
			pNode1->SetPipeStatus("USE");		//��� ���ɿ��� �� USE�� ����

			adjacency.InsertDongEdge(linklist,pNode1);	//��������Ʈ ����Լ��� ���ؼ� DongEdge�� ����

			delete pNode1;	//�����Ҵ� ����

			//������ ������ Dong Edge�� ������ �̷�� Edge����
			Dong_Edge* pNode2=new Dong_Edge();	//to���� from�� �ش��ϴ� Dong_Edge ����
			pNode2->SetGuName(guname);		//fromdong�� todong�� �̸����ݴ�� Set�ؼ� ����
			pNode2->SetFromDong(todong);
			pNode2->SetToDong(fromdong);
			pNode2->SetLossRate1(Lossrate);
			pNode2->SetPipeStatus("USE");		//��� ���ɿ��θ� USE�� ����

			adjacency.InsertDongEdge(linklist,pNode2);	//��������Ʈ ����Լ��� ���ؼ� Dong Edge�� ����

			delete pNode2;	//�����Ҵ� ����

			//Mst�籸��
			sptree.InitialUseflag(pGNode);	//MST�ʱ�ȭ
			Mstcheck=sptree.Kruskal(pGNode);	//MST�籸��
			if(Mstcheck==false)	//MST ������ ���� ������
				this->PipeRepair(guname);	//Pipe repair �Լ��� ȣ���ؼ� MST�� �����ϵ��� �Ѵ�.
		}
		else	//�ش� Edge�� �ִ� ��� ���ս��� update
		{
			//Edge�� ���ؼ� �� �ս��� update
			pFE->SetLossRate1(Lossrate);
			pTE->SetLossRate1(Lossrate);
			
			//Mst �籸��
			sptree.InitialUseflag(pGNode);	//MST�ʱ�ȭ
			Mstcheck=sptree.Kruskal(pGNode);	//MST�籸��
			if(Mstcheck==false)		//MST ������ ���� ������
				this->PipeRepair(guname);	//Pipe repair �Լ��� ȣ���ؼ� MST�� �����ϵ��� �Ѵ�.
		}
		
		delete[] guname;	//�����Ҵ� ����
		delete[] fromdong;
		delete[] todong;
		delete[] Lossrate;
		len=0;	//���� �ʱ�ȭ
		memset(str,0,150);	//�迭 �ʱ�ȭ
	}

	fin.close();	//������ �ݴ´�.

	return true;
}

bool Manager::PipeBroken(char* guname, char* fromdong, char* todong)	//PipeBroken ��ɾ� ���� �Լ�
{
	Dong_Vertex* pFrom=linklist.FindDong(guname, fromdong);	//from�� �ش��ϴ� dong vertex
	Dong_Vertex* pTo=linklist.FindDong(guname,todong);		//to�� �ش��ϴ� dong vertex

	Dong_Edge* pFE=pFrom->GetDENext();	//From�� edge�� Ž���� pointer
	Dong_Edge* pTE=pTo->GetDENext();		//to�� edge�� Ž���� pointer

	while(pFE!=NULL)	//fromdong -> todong�� �ش��ϴ� edge �������� broken���·� �����
	{
		if(strcmp(pFE->GetToDong(), todong)==0)	//From Edge�� todong�� todong�� ��ġ�ϴ� ���
		{
			pFE->SetPipeStatus("BROKEN");	//Pipe�� ���¸� USE���� BROKEN���� ����
			break;	//�ݺ��� ����
		}
		pFE=pFE->GetENext();	//���� Edge�� �̵�
	}

	while(pTE!=NULL)	//todong -> fromdong�� �ش��ϴ� edge �������� broken ���·� �����
	{
		if(strcmp(pTE->GetToDong(), fromdong)==0)	//To Edge�� toDong�� fromdong�� ��ġ�ϴ� ���
		{
			pTE->SetPipeStatus("BROKEN");	//Pipe�� ���¸� USE���� BROKEN���� ����
			break;	//�ݺ��� ����
		}
		pTE=pTE->GetENext();	//���� Edge�� �̵�
	}

	////MST �籸��
	Gu_Vertex* pCur=linklist.FindGu(guname);	//�ش� guname�� Gu Vertex�� ã�´�
	//pCur�� guname�� Gu Vertex

	////////1. MST useflag �ʱ�ȭ
	sptree.InitialUseflag(pCur);	//�ش� ���� ���ؼ� MST �ʱ�ȭ

	////////2. MST �籸��
	bool mst=false;
	mst=sptree.Kruskal(pCur);	//�ش� ���� ���ؼ� MST �籸��

	if(mst==true)	//Mst�� �����Ǿ��ٸ�
		return true;	//�Լ� ����
	else if(mst==false)	//Mst�� �ƴ϶��
		this->PipeRepair(guname);	//�ش� ���� ���ؼ� Pipe_Repair ����

	

	return true;
}

bool Manager::PipeRepair(char* guname)	//PipeRepair ��ɾ� ���� �Լ�
{
	//1. �� ������� ���� ��ġ�� ��ǥ ��ġ�� ���� Dijkstra �˰����� �̿��� �Ÿ� ���
	/////////
	Mechanic* pMCur=linklist.GetMHead();	//mechanic head�� ����Ų��
	Gu_Vertex* pSRC=NULL;//source
	Gu_Vertex* pDES=NULL;//destination

	pDES=linklist.FindGu(guname);		//������(������ �䱸�ϴ� ��)

	while(pMCur!=NULL)	//��� ����翡 ���ؼ� Ž��
	{
		pSRC=linklist.FindGu(pMCur->GetWorkPlace());		//�����(������� ����ٹ���ġ)
		if(pSRC!=NULL)	//��� �ٹ����� �����ϴ� Gu Vertex�� ���
			pMCur->SetDist(sptree.Dijkstra(linklist,pSRC,pDES));	//����� -> ������������ �ּ� �Ÿ� ��ȯ �ؼ� ������� �̵��Ÿ������� Set�Ѵ�

		pMCur=pMCur->GetNext();	//���� ������ �̵�
	}
	Mechanic* pMin=NULL;	//Dist���� �ּ��� ����縦 ����ų ������

	pMCur=linklist.GetMHead();	//������� head�� ����Ų��
	pMin=pMCur;	//�ּ��� �����ʹ� head�� ����Ų��
	pMCur=pMCur->GetNext();	//pMCur�� ���� ������ �̵�

	while(pMCur!=NULL)//��� ����翡 ���ؼ� Ȯ��
	{
		if(pMCur->GetDist()<pMin->GetDist())	//pMCur ������� �̵� �Ÿ��� �� ª�ٸ�, pMin�� ���� �ش� ������ ��ü
		{
			pMin=pMCur;	//����� ��ü
		}

		pMCur=pMCur->GetNext();	//���� ������ �̵�
	}
	/////////////pMin�� �̵� �Ÿ��� �ִܰŸ��� �����


	ofstream fout("repair_log.txt",ios_base::app);	//file�̾ ����

	//2. �ִܰŸ��� ���� ���� ������� �̸� / ������ �䱸�ϴ� ���̸� ���
	fout<<pMin->GetName()<<" / "<<guname<<endl;


	//3. Pipestatus�� USE�� Edge�鿡 repair log
	fout<<"���� �� ���� �� ����"<<endl;

	//pDES�� ������ ���ϴ� ��
	Dong_Vertex* pDCur=pDES->GetDNext();	//������ �̵�
	Dong_Edge* pDECur=NULL;

	do
	{
		pDECur=pDCur->GetDENext();	//�ش� ���� Edge�� ����Ų��
		while(pDECur!=NULL)
		{
			if(strcmp(pDECur->GetPipeStatus(),"USE")==0&&pDECur->GetUseflag()==1)	//USE�����̸�, Mst�� �����ϴ� Edge�� ���
			{
				fout<<"\t\t"<<pDECur->GetFromDong()<<" -> "<<pDECur->GetToDong()<<" ("<<pDECur->GetLossRate()<<")"<<endl;
			}
			pDECur=pDECur->GetENext();	//���� dong_edge�� �̵�
		}

		pDCur=pDCur->GetDVNext();//�� �̵�
	}while(pDCur!=pDES->GetDNext());

	//4. BROKEN�� Dong_Edge�鿡 ���ؼ� repair log
	pDCur=pDES->GetDNext();	//�ٽ� �������� ������ �̵�

	fout<<"���� ����"<<endl;

	do
	{
		pDECur=pDCur->GetDENext();	//���� Edge�� ����Ų��
		while(pDECur!=NULL)	//Edge�� Null�� �ƴ� �� ����
		{
			if(strcmp(pDECur->GetPipeStatus(),"BROKEN")==0)	//BROKEN�� ��� �ش� Dong Edge�� USE�� �ٲ��ָ� �� ������ ������ 2��
			{
				//�����ϴ� �κп� ���ؼ� ���
				fout<<"\t\t["<<pDECur->GetPipeStatus()<<"]"<<pDECur->GetFromDong()<<" -> "<<pDECur->GetToDong();
				fout<<" ("<<pDECur->GetLossRate()<<") -> ("<<pDECur->GetLossRate()*2<<")"<<endl;
				
				pDECur->SetPipeStatus("USE");	//Pipe�� ���¸� USE�� �ٲپ� �ش�
				pDECur->SetLossRate2(pDECur->GetLossRate()*2);	//�� ������ ������ 2��
				
			}
			pDECur=pDECur->GetENext();	//���� dong_edge�� �̵�
		}

		pDCur=pDCur->GetDVNext();//�� �̵�
	}while(pDCur!=pDES->GetDNext());	//��������Ʈ�� �ѹ� Ž��

	//5. ->MST �籸�� (1), useflag�ʱ�ȭ, (2), MST����
	sptree.InitialUseflag(pDES);	//useflag, overlap �ʱ�ȭ
	bool mstcheck=false;
	mstcheck=sptree.Kruskal(pDES);	//MST����

	//������ �Ͽ��µ� MST�� ���� �ʴ� ���� ���ٰ� �������� ���� ���� �ְ� �ȴٸ� ���� Repiar
	
	//6. ���� ��, Pipestatus�� USE�� Edge�鿡 ���ؼ� repair log
	fout<<"���� �� ���� �� ����"<<endl;
	pDCur=pDES->GetDNext();	//�������� Gu Vertex�� ���� ����Ų��

	do
	{
		pDECur=pDCur->GetDENext();	//���� Edge�� ����Ų��
		while(pDECur!=NULL)	//Edge�� ��� Ž��
		{
			if(strcmp(pDECur->GetPipeStatus(),"USE")==0&&pDECur->GetUseflag()==1)	//use�� ���� Mst�� �̷�� Edge�鿡���ؼ��� ���
			{
				//Edge�� ���� ���
				fout<<"\t\t"<<pDECur->GetFromDong()<<" -> "<<pDECur->GetToDong()<<" ("<<pDECur->GetLossRate()<<")"<<endl;
			}
			pDECur=pDECur->GetENext();	//���� dong_edge�� �̵�
		}

		pDCur=pDCur->GetDVNext();//�� �̵�
	}while(pDCur!=pDES->GetDNext());	//��������Ʈ Ž��


	//7. Dijstra �̵���ο� ������ �̵���� �Լ� ȣ����
	pSRC=linklist.FindGu(pMin->GetWorkPlace());	//������� �Ǵ� ���� ���ؼ� ã�´�
	int distance=0;	//�Ÿ����� ������ ����

	distance=sptree.Dijkstra(linklist,pSRC,pDES);	//��������� ������ ������ �Ÿ��� ����

	//8. stack���� pop�ϸ鼭 �̵���� ���
	stack sp;	//stack type�� ������ ����
	sp=sptree.BackTrace(linklist,pSRC,pDES);	//������ �Լ��� ȣ���ؼ� ��ȯ�Ǵ� stack�� �޴´�

	Gu_Vertex* pCur=sp.Pop();	// stack�� data�� pop�Ѵ� -> �����

	fout<<pMin->GetName()<<" ������� �̵� ���"<<endl;//������� ���� ���

	while(pCur!=NULL)	//stack�� pop�� ���� NULL�� �� �� ����
	{
		//���� �̸���, cost�� ������ ���
		fout<<pCur->GetGuName()<<"("<<pCur->GetCost()<<")";
		if(pCur!=pDES)	//���� �̵����� ���
			fout<<" -> ";
		pCur=sp.Pop();	//pCur�� stack���� Pop�� Node�� ����Ų��
	}
	fout<<endl<<endl;

	fout.close();	//���� �ݴ´�
	///������� ���� �ٹ� ��ġ�� guname���� ��ȯ
	pMin->SetWorkPlace(guname);

	return true;	//�Լ� ����
}

bool Manager::MST()//�������� ���ؼ� MST�� �����ϴ� �Լ�
{
	Gu_Vertex* pGCur=linklist.GetGVHead();	//Gu_Vertex�� head�� ����Ų��
	bool check=false;
	while(pGCur!=NULL)
	{
		check=sptree.Kruskal(pGCur);	//MST ���� �Լ� ȣ��
		pGCur=pGCur->GetGVNext();	//���� Gu_Vertex�� �̵�
	}

	return true;	//�Լ�����
}

bool Manager::PrintMap()	//���� ��� �Լ�
{
	Gu_Vertex* pCur=linklist.GetGVHead();	//Gu Vertex�� head�� ����Ų��

	if(pCur==NULL)	//Gu Vertex�� ���ٸ�
		return false;	//����

	Gu_Edge* pECur=NULL;	//Gu Edge�� ����ų ������

	ofstream fout("map.txt",ios_base::app);	//������ �̾ open

	//������ ���� ���
	fout<<"===================================="<<endl;
	fout<<"\t      PRINT MAP"<<endl;
	fout<<"===================================="<<endl;

	while(pCur!=NULL)	//Gu Vertex�� NULL�� �� ����
	{
		pECur=pCur->GetGENext();	//Gu Vertex�� Edge�� ����Ų��

		while(pECur!=NULL)	//Edge�� NULL�� �ƴ� �� ����
		{
			//���� Edge�� ���ؼ� ���
			fout<<pECur->GetFromGu()<<" -> "<<pECur->GetToGu()<<" ("<<pECur->GetDist()<<")"<<endl;
			pECur=pECur->GetENext();	//���� Edge�� �̵�
		}

		pCur=pCur->GetGVNext();	//Gu Vertex�̵�
	}

	fout.close();	//���� �ݴ´�

	return true;	//�Լ�����
}

bool Manager::PrintPipe(Gu_Vertex* GuNode)	//���� ������ ��� �Լ�
{
	if(GuNode==NULL)	//�ش� ���� �������� �ʴ´�.
		return false;

	Dong_Vertex* pDCur=GuNode->GetDNext();	//Dong�� ����ų ������
	Dong_Edge* pDECur=NULL;	//Dong Edge�� ����ų ������

	ofstream fout("pipe.txt",ios_base::app);	//������ �̾ open

	//������ ���� ���
	fout<<"===================================="<<endl;
	fout<<"\t\tPIPE"<<endl;
	fout<<"===================================="<<endl;

	do
	{
		pDECur=pDCur->GetDENext();	//Dong Edge�� Dong Vertex�� Edge�� ����Ų��
		while(pDECur!=NULL)	//��� EdgeŽ��
		{
			if(strcmp(pDECur->GetPipeStatus(),"USE")==0&&pDECur->GetUseflag()==1)	//MST�� �����ϴ� Edge�� ���ؼ� ���
			{
				fout<<GuNode->GetGuName()<<" : ";
				fout<<pDECur->GetFromDong()<<" -> "<<pDECur->GetToDong()<<" ("<<pDECur->GetLossRate()<<")"<<endl;
			}
			pDECur=pDECur->GetENext();	//���� Edge�� �̵�
		}
		pDCur=pDCur->GetDVNext();	//���� Dong Vertex�� �̵�
	}while(pDCur!=GuNode->GetDNext());	//��� Dong�� ���ؼ� Ž��

	fout.close();	//���� �ݴ´�

	return true;	//�Լ�����
}

bool Manager::PrintMechanic()	//����� ��� �Լ�
{
	Mechanic* pCur=linklist.GetMHead();	//����� head�� ����Ų��
	if(pCur==NULL)	//���ٸ�
		return false;	//�Լ�����

	ofstream fout("mechanic_list.txt",ios_base::app);	//������ �̾ open

	//file ���� ���
	fout<<"===================================="<<endl;
	fout<<"\t      MECHANIC INFO"<<endl;
	fout<<"===================================="<<endl;


	while(pCur!=NULL)	//��� ����� Ž��
	{
		//����� ���� ���
		fout<<pCur->GetName()<<" - "<<pCur->GetWorkPlace()<<endl;
		pCur=pCur->GetNext();	//���� ������ �̵�
	}

	fout.close();	//���� �ݴ´�

	return true;	//�Լ�����
}

bool Manager::Save()	//Save��ɾ� �����Լ�
{
	this->SaveGuVertex();	//Gu Vertex���� �Լ�

	this->SaveGuEdge();	//Gu Edge���� �Լ�

	this->SaveDongVertex();	//Dong Vertex���� �Լ�

	this->SaveDongEdge();	//Dong Edge �����Լ�

	this->SaveMechanic();	//����� ���� �Լ�

	return true;	//�Լ�����
}

bool Manager::SaveGuVertex()	//Gu Vertex�� ���� Save�Լ�
{
	ofstream fout("gu_vertex.bak");	//���� open

	if(!fout.is_open())	//������ ����� ������ �ʾҴٸ�
		return false;	//���� ��ȯ

	//���� ���� ���
	fout<<"========================="<<endl;
    fout<<"    ����� �� ��Ī	"<<endl;
	fout<<"========================="<<endl;

	Gu_Vertex* pCur=linklist.GetGVHead();	//Gu Vertex�� Gu�� head�� ����Ų��

	while(pCur!=NULL)	//��� Gu�� ���ؼ� Ž��
	{
		fout<<"\t"<<pCur->GetGuName()<<endl;	//���� ���
		pCur=pCur->GetGVNext();	//���� Gu�� �̵�
	}

	fout.close();	//end file

	return true;	//�Լ� ����
}

bool Manager::SaveGuEdge()	//Gu Edge�� ���� Save�Լ�
{
	ofstream fout("gu_edge.bak");	//���� open

	if(!fout.is_open())	//������ ����� ������ �ʾҴٸ�
		return false;	//���� ��ȯ

	//���� ���� ���
	fout<<"===================================================================================="<<endl;
	fout<<"	from(��)			to(��)			   distance (Km)"<<endl;
	fout<<"===================================================================================="<<endl;

	Gu_Vertex* pCur=linklist.GetGVHead();	//Gu Vertex�� head�� ����Ų��
	Gu_Edge* pECur=NULL;	//Gu Edge�� ����ų ������
	
	while(pCur!=NULL)	//��� Gu Vertex Ž��
	{
		pECur=pCur->GetGENext();	//�ش� GU�� Edge�� ����Ų��
		while(pECur!=NULL)	//��� EdgeŽ��
		{
			//Edge���� ���
			fout<<"\t"<<pECur->GetFromGu();
			fout<<"\t\t\t"<<pECur->GetToGu();
			fout<<"\t\t\t\t"<<pECur->GetDist()<<endl;

			pECur=pECur->GetENext();	//���� Edge�� �̵�
		}

		pCur=pCur->GetGVNext();	//���� Gu Vertex�� �̵�
	}

	fout.close();	//end file

	return true;	//�Լ�����
}

bool Manager::SaveDongVertex()	//Dong Vertex�� ���� Save�Լ�
{
	ofstream fout("dong_vertex.bak");	//���� open

	if(!fout.is_open())	//������ ����� ������ �ʾҴٸ�
		return false;	//���� ��ȯ

	//���� ���� ���
	fout<<"================================================================================="<<endl;
	fout<<"	�� ��Ī			�� ��Ī			���� ������ ����(O/X)	"<<endl;
	fout<<"================================================================================="<<endl;

	Gu_Vertex* pGCur=linklist.GetGVHead();	//Gu�� Head�� ����Ų��
	Dong_Vertex* pDCur=NULL;	//���� ����ų ������

	while(pGCur!=NULL)	//��� guŽ��
	{
		pDCur=pGCur->GetDNext();	//head�� �Ǵ� Dong�� ����Ų��
		if(pDCur!=NULL)	//Dong�� �����Ѵٸ�
		{
			do
			{
				//�������� ���� ���
				fout<<"\t"<<pDCur->GetGuName();
				fout<<"\t\t\t"<<pDCur->GetDongName();
				fout<<"\t\t\t\t"<<pDCur->GetHeatCheck()<<endl;
				pDCur=pDCur->GetDVNext();	//���� Dong���� �̵�

			}while(pDCur!=pGCur->GetDNext());	//���� List���� ��� ���� �����Ѵ�
		}
		pGCur=pGCur->GetGVNext();	//���� Gu�� �̵�
	}

	fout.close();	//end file

	return true;	//�Լ� ����
}

bool Manager::SaveDongEdge()	//Dong Edge�� ���� Save�Լ�
{
	ofstream fout("dong_edge.bak");	//������ ����

	if(!fout.is_open())	//������ ����� ������ �ʾҴٸ�
		return false;	//���� ��ȯ

	//���� ���� ���
	fout<<"=============================================================================================="<<endl;
	fout<<"	�� ��Ī			from(��)			to(��)		    �� �սǷ�(%)"<<endl;
	fout<<"=============================================================================================="<<endl;

	Gu_Vertex* pGCur=linklist.GetGVHead();	//Head�� �Ǵ� Gu�� ����Ų��
	Dong_Vertex* pDCur=NULL;	//Dong�� ����ų ������
	Dong_Edge* pDECur=NULL;		//Dong Edge�� ����ų ������

	while(pGCur!=NULL)	//��� Gu�����ؼ� Ž��
	{
		pDCur=pGCur->GetDNext();	//Gu�� head�� �Ǵ� Dong�� ����Ų��
		if(pDCur!=NULL)	//Dong�� NULL�� �ƴ϶��
		{
			do
			{
				pDECur=pDCur->GetDENext();	//Dong�� Edge�� �̵�
				while(pDECur!=NULL)	//Edge��� Ž��
				{
					//Edge���� ���
					fout<<"\t"<<pDECur->GetGuName();
					fout<<"\t\t\t"<<pDECur->GetFromDong();
					fout<<"\t\t\t"<<pDECur->GetToDong();
					fout<<"\t\t\t"<<pDECur->GetLossRate()<<endl;

					pDECur=pDECur->GetENext();	//���� Dong Edge�� �̵�
				}

				pDCur=pDCur->GetDVNext();	//Dong Vertex�̵�
			}while(pDCur!=pGCur->GetDNext());	//���� list�� �ѹ��� ����
		}
		pGCur=pGCur->GetGVNext();	//���� Gu vertex�� �̵�
	}

	fout.close();	//end file

	return true;	//�Լ� ����
}

bool Manager::SaveMechanic()	//����翡 ���� Save�Լ�
{
	ofstream fout("mechanic.bak");	//file open

	if(!fout.is_open())	//������ ����� ������ �ʾҴٸ�
		return false;	//���� ��ȯ

	//���� ���� ���
	fout<<"============================================"<<endl;
	fout<<"	�ٹ���		����� �̸�		"<<endl;
	fout<<"============================================"<<endl;

	Mechanic* pMec=linklist.GetMHead();	//������� head�� ����Ų��

	while(pMec!=NULL)	//��� ����� Ž��
	{
		//��������� ���
		fout<<"\t"<<pMec->GetWorkPlace();
		fout<<"\t\t"<<pMec->GetName()<<endl;
		pMec=pMec->GetNext();	//���� ������ �̵�
	}

	fout.close();	//end file

	return true;	//�Լ� ����
}