#include "Manager.h"


Manager::Manager(void)	//생성자
	:linklist(), adjacency(), sptree()	//객체 생성자 호출
{
	ofstream fout("repair_log.txt");	//repair_log text file open
	ofstream fout1("map.txt");			//map text file open
	ofstream fout2("pipe.txt");			//pipe text file open
	ofstream fout3("mechanic_list.txt");	//mechanic text file open

	fout.close();	//열었던 file 닫기
	fout1.close();
	fout2.close();
	fout3.close();
}


Manager::~Manager(void)	//소멸자
{
}

bool Manager::Command(char* filename)	//Command file을 읽어서 실행하는 함수
{
	ifstream fin(filename);	//파일을 연다

	if(!fin.is_open())	//파일이 열리지 않았을 때,
		return false;	//실패반환

	char str[100]={'\0'};	//파일에서 한줄씩 읽어서 저장할 배열
	char* token=NULL;		//str값을 필요한 부분을 가리킬 포인터
	int len=0;			//token의 길이를 저장할 변수
	int count=0;		//factor의 개수를 헤아릴 변수
	int loadable=0;		//처음 Load인지, 그 외의 Load인지를 확인할 변수
	char* command=NULL;	//command값을 가리킬 포인터

	/////////////////////factor들은 command file에서 의 command에 따른 부가적인 사항에 대한 요인으로 최대 5개 까지 존재한다
	char* factor1=NULL;	//factor1을 가리킬 포인터
	char* factor2=NULL;	//factor2를 가리킬 포인터
	char* factor3=NULL;	//factor3를 가리킬 포인터
	char* factor4=NULL;	//factor4를 가리킬 포인터
	char* factor5=NULL;	//factor5를 가리킬 포인터

	fin.getline(str,100);	//파일을 한줄 읽는다
	fin.getline(str,100);	//파일을 한줄 읽는다
	fin.getline(str,100);	//파일을 한줄 읽는다
	memset(str,0,100);		//배열 초기화

	while(!fin.eof())	//file이 종료될 때 까지
	{
		fin.getline(str,100);	//한줄을 읽어온다
		len=0;			//길이를 0으로 초기화
		count=0;		//count값 초기화

		if(str[0]==0)	//Enter key 입력시종료
			break;

		token=strtok(str," /");	//tap과 /에 따라서 token을 구분
		len=strlen(token);		//token의 길이측정
		command=new char[len+1];	//동적할당
		memset(command,0,len+1);	//초기화
		strcpy(command,token);		//값을 copy

		token=strtok(NULL," /");	//token에 값을 저장
		if(token!=NULL)	//token이 존재하면
		{
			len=strlen(token);	//token의 길이측정
			factor1=new char[len+1];	//동적할당
			memset(factor1,0,len+1);	//초기화
			strcpy(factor1,token);		//값을 copy
			count++;	//count==1

			token=strtok(NULL," /");	//token에 값을 저장
			if(token!=NULL)
			{
				len=strlen(token);	//token의 길이 측정
				factor2=new char[len+1];	//동적할당
				memset(factor2,0,len+1);	//초기화
				strcpy(factor2,token);		//값을 copy
				count++;	//count==2

				token=strtok(NULL," /");	//token에 값을 저장
				if(token!=NULL)
				{
					len=strlen(token);	//token의 길이 측정
					factor3=new char[len+1];	//동적할당
					memset(factor3,0,len+1);	//초기화
					strcpy(factor3,token);		//값을 copy
					count++;	//count==3

					token=strtok(NULL," /");	//token에 값을 저장
					if(token!=NULL)
					{
						len=strlen(token);	//token의 길이 측정
						factor4=new char[len+1];	//동적할당
						memset(factor4,0,len+1);	//초기화
						strcpy(factor4,token);	//값을 copy
						count++;	//count==4

						token=strtok(NULL," /");	//token에 값을 저장
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

		if(strcmp(command,"LOAD")==0) //5개 file load, Format : LOAD gu_vertex.txt,gu_edge.txt, dong_vertex.txt, dong_edge.txt, mechanic.txt
		{
			if(loadable==0)
			{
				this->Load(factor1, factor2, factor3, factor4, factor5);
				loadable=1;
			}
			else
			{
				////동적할당 해제
				linklist.DeleteDongList();
				linklist.DeleteGuList();
				linklist.DeleteMechanic();
				this->Load(factor1, factor2, factor3, factor4, factor5);
			}
		}
		else if(strcmp(command,"UPDATE")==0) //1개 file load, Format : UPDATE update_dong_edge_cost.txt
		{
			this->Update(factor1);
		}
		else if(strcmp(command,"PIPE_BROKEN")==0) //3개 factor, Format : PIPE_BROKEN 노원구 / 상계1동 / 상계2동
		{
			this->PipeBroken(factor1, factor2, factor3);
		}
		else if(strcmp(command,"PIPE_REPAIR")==0) //1개 factor, Format : PIPE_REPAIR 강남구
		{
			this->PipeRepair(factor1);
		}
		else if(strcmp(command,"SAVE")==0)	//No factor, Format : SAVE
		{
			this->Save();
		}
		else if(strcmp(command,"PRINT")==0) //1개 factor, Format : (1). PRINT 정비사, (2). PRINT 지도, (3). PRINT 노원구
		{
			if(strcmp(factor1,"지도")==0)	//지도에 대한 출력
			{
				this->PrintMap();
			}
			else if(strcmp(factor1,"정비사")==0)	//정비사에 대한 출력
			{
				this->PrintMechanic();
			}
			else	//구이름
			{
				Gu_Vertex* GuNode=linklist.FindGu(factor1);	//해당 Gu 이름에 해당하는 Gu Vertex를 찾는다
				this->PrintPipe(GuNode);	//파이프 출력
			}
		}
		else if(strcmp(command,"EXIT")==0)	//Format : EXIT
		{
			return true;
		}
		else
		{
			cout<<command<<" is Not Exist COMMAND!"<<endl;	//이외의 command가 오는경우
		}

		//동적할당 해제
		delete[] command;	//command동적할당 해제
		if(count>=1)	//count가 1보다 큰경우
		{
			delete[] factor1;	//factor1동적할당 해제
			if(count>=2)	//count가 2보다 큰경우
			{
				delete[] factor2;	//factor2동적할당 해제
				if(count>=3)	//count가 3보다 큰 경우
				{
					delete[] factor3;	//factor3동적할당 해제
					if(count>=4)	//count가 4보다 큰 경우
					{
						delete[] factor4;	//factor4동적할당 해제
						if(count==5)	//count가 5보다 큰경우
							delete[] factor5;	//factor5동적할당 해제
					}
				}
			}
		}

		memset(str,0,100);	//배열 초기화
	}

	fin.close();	//파일을 닫는다.

	return true;
}

bool Manager::Load(char* guvertex, char* guedge, char* dongvertex, char* dongedge, char* mechanic)	//Load file을 받아서 gu, don vertex & edge를 실행해주는 함수
{
	this->LoadGuVertex(guvertex);	//Gu Vertex에 대한 Load

	this->LoadGuEdge(guedge);	//Gu Edge에 대한 Load

	this->LoadDongVertex(dongvertex);	//Dong Vertex에 대한 Load

	this->LoadDongEdge(dongedge);	//Dong Edge에 대한 Load

	this->LoadMechanic(mechanic);	//정비사에 대한 Load

	this->MST();		//Load시에 모든 Gu에 대한 MST구성

	return true;	//함수종료
}

bool Manager::LoadGuVertex(char* filename)	//GuVertex를 읽어오는 함수
{
	ifstream fin(filename);	//파일 열기

	if(!fin.is_open())	//열리지 않는다면
		return false;	//실패반환

	char str[50]={'\0'};	//파일 읽어올 배열
	char* token=NULL;	//파일의 주소를 가리킬 포인터
	int len=0;			//token의 길이
	char* guname=NULL;	//구의 이름을 저장할 배열

	fin.getline(str,50);	//파일의 상위 3줄 읽기
	fin.getline(str,50);
	fin.getline(str,50);
	memset(str,0,50);		//배열 초기화

	while(!fin.eof())	//파일이 종료될 때 까지
	{
		fin.getline(str,50);	//파일한줄을 읽는다

		if(str[0]==0)	//Enter key 입력시종료
			break;

		token=strtok(str,"\t");	//token은 원하는 문자열을 가리킨다
		len=strlen(token);		//길이 측정
		guname=new char[len+1];	//동적할당
		memset(guname,0,len+1);	//초기화
		strcpy(guname,token);	//값을 copy

		///Insert
		Gu_Vertex* pNode=new Gu_Vertex();	//Gu Vertex 동적할당
		pNode->SetGuName(guname);		//값을 Set 구의 이름
		linklist.InsertGuVertex(pNode);	//linklist 변수의 Insert Gu 함수 호출

		delete pNode;	//동적할당 해제
		delete[] guname;
		len=0;	//길이 초기화
		memset(str,0,50);	//배열 초기화
	}

	fin.close();	//파일을 닫는다.

	return true;	//함수종료
}

bool Manager::LoadGuEdge(char* filename)	//GuEdge를 읽어오는 함수
{
	ifstream fin(filename);	//파일을 연다

	if(!fin.is_open())	//열리지 않은 경우
		return false;

	char str[150]={'\0'};	//배열선언
	char* token=NULL;	//원하는 부분을 가리킬 포인터
	int len=0;		//token의 길이정보 저장할변수
	char* fromgu=NULL;	//fromgu의 정보를 가리킬 포인터
	char* togu=NULL;	//togu의 정보를 가리킬 포인터
	char* dist=NULL;	//dist의 정보를 가리킬 포인터

	fin.getline(str,150);	//파일의 3줄을 읽어온다
	fin.getline(str,150);
	fin.getline(str,150);
	memset(str,0,150);		//초기화

	while(!fin.eof())	//파일이 종료될 때 까지
	{
		fin.getline(str,150);	//파일 한줄읽는다

		if(str[0]==0)	//enter키 입력시 종료
			break;

		token=strtok(str,"\t");	//token은 tap으로 나눈다
		len=strlen(token);		//길이 측정
		fromgu=new char[len+1];	//동적할당
		memset(fromgu,0,len+1);	//초기화
		strcpy(fromgu,token);	//값을 copy

		token=strtok(NULL,"\t");	//token은 tap으로 나눈다
		len=strlen(token);		//길이측정
		togu=new char[len+1];	//동적할당
		memset(togu,0,len+1);	//초기화
		strcpy(togu,token);		//값을 copy

		token=strtok(NULL,"\t");	//token은 tap으로 나눈다
		len=strlen(token);		//길이측정
		dist=new char[len+1];	//동적할당
		memset(dist,0,len+1);	//초기화
		strcpy(dist,token);	//값을 copy

		Gu_Edge* pNode=new Gu_Edge();	//Gu Edge type의 변수 동적할당
		pNode->SetFromGu(fromgu);	//Fromgu, Togu, dist의 값을 Set한다
		pNode->SetToGu(togu);
		pNode->SetDist1(dist);

		adjacency.InsertGuEdge(linklist,pNode);	//인접리스트에서 Gu의 Edge를 삽입한다

		delete pNode;	//동적할당 해제
		delete[] fromgu;
		delete[] togu;
		delete[] dist;
		len=0;	//길이 초기화
		memset(str,0,150);	//배열 초기화
	}

	fin.close();	//파일을 닫는다.

	return true;	//함수종료
}

bool Manager::LoadDongVertex(char* filename)	//DongVertex를 읽어오는 함수
{
	ifstream fin(filename);	//파일 open

	if(!fin.is_open())	//열리지 않았다면
		return false;	//실패 반환

	char str[100]={'\0'};	//파일 한줄을 저장할 배열선언
	char* token=NULL;	//token은 NULL을 가리킨다
	int len=0;		//길이는 0이 된다
	char* guname=NULL;	//guname의 정보를 저장할 포인터
	char* dongname=NULL;	//dongname의 정보를 저장할 포인터
	char* heatcheck=NULL;	//열 손실율을 저장할 포인터

	fin.getline(str,100);	//파일의 3줄을 읽는다
	fin.getline(str,100);
	fin.getline(str,100);
	memset(str,0,100);	//배열 초기화

	while(!fin.eof())	//파일이 종료될 때 까지 반복문 실행
	{
		fin.getline(str,100);	//파일 한줄을 읽는다

		if(str[0]==0)	//enter key실행시
			break;		//반복문종료

		token=strtok(str,"\t");	//token은 guname부분을 가리킨다
		len=strlen(token);		//길이 측정
		guname=new char[len+1];	//동적할당
		memset(guname,0,len+1);	//배열 초기화
		strcpy(guname,token);	//값을 copy한다

		token=strtok(NULL,"\t");	//token은 dongname부분을 가리킨다
		len=strlen(token);			//길이 측정
		dongname=new char[len+1];	//동적할당
		memset(dongname,0,len+1);	//배열 초기화
		strcpy(dongname,token);		//값을 copy한다

		token=strtok(NULL,"\t");	//token은 heatcheck를 가리킨다
		len=strlen(token);			//길이측정
		heatcheck=new char[len+1];	//동적할당
		memset(heatcheck,0,len+1);	//배열 초기화
		strcpy(heatcheck,token);	//값을 copy한다

		Dong_Vertex* pNode=new Dong_Vertex();	//Dong Vertex type 동적 할당
		pNode->SetGuName(guname);		//guname을 set한다
		pNode->SetDongName(dongname);	//dongname을 set한다
		pNode->SetHeatCheck(heatcheck);	//열손실율 set

		linklist.InsertDongVertex(pNode);	// Dong Vertex를 linklist멤버함수 insertDongVertex를 호출해서 삽입

		delete pNode;	//동적할당해제
		delete[] guname;
		delete[] dongname;
		delete[] heatcheck;
		len=0;	//길이 초기화
		memset(str,0,100);	//배열 초기화
	}

	fin.close();	//파일을 닫는다.

	return true;	//함수종료
}

bool Manager::LoadDongEdge(char* filename)	//DongEdge를 읽어오는 함수
{
	ifstream fin(filename);	//파일 open

	if(!fin.is_open())	//파일이 열리지 않는다면
		return false;	//실패반환

	char str[150]={'\0'};	//파일 한줄을 저장할 배열
	char* token=NULL;	//원하는 부분을 가리킬 포인터
	int len=0;		//길이를 저장할 변수
	char* guname=NULL;	//guname을 저장할 포인터
	char* fromdong=NULL;	//fromdong을 저장할 포인터
	char* todong=NULL;		//todong을 저장할 포인터
	char* Lossrate=NULL;	//Lossrate를 저장할 포인터

	fin.getline(str,150);	//파일의 3줄을 읽는다
	fin.getline(str,150);
	fin.getline(str,150);
	memset(str,0,150);	//배열 초기화

	while(!fin.eof())	//파일이 종료될 때 까지
	{
		fin.getline(str,150);	//파일 한줄을 읽는다

		if(str[0]==0)	//Enter 입력시
			break;	//반복문 종료

		token=strtok(str,"\t");	//token은 guname을 가리킨다
		len=strlen(token);	//길이측정
		guname=new char[len+1];	//guname동적할당
		memset(guname,0,len+1);	//배열초기화
		strcpy(guname,token);	//값을 copy

		token=strtok(NULL,"\t");	//token은 fromdong정보를 가리킨다
		len=strlen(token);	//길이측정
		fromdong=new char[len+1];	//fromdong동적할당
		memset(fromdong,0,len+1);	//배열 초기화
		strcpy(fromdong,token);	//값을 copy

		token=strtok(NULL,"\t");	//token은 todong정보를 가리킨다
		len=strlen(token);		//길이측정
		todong=new char[len+1];	//todong동적할당
		memset(todong,0,len+1);	//배열 초기화
		strcpy(todong,token);	//값을 copy

		token=strtok(NULL,"\t");	//token은 Lossrate정보를 가리킨다
		len=strlen(token);		//길이측정
		Lossrate=new char[len+1];	//Lossrate동적할당
		memset(Lossrate,0,len+1);	//배열 초기화
		strcpy(Lossrate,token);	//값을 copy

		Dong_Edge* pNode=new Dong_Edge();	//Dong Edge동적할당
		pNode->SetGuName(guname);		//guname Set
		pNode->SetFromDong(fromdong);	//fromdong Set
		pNode->SetToDong(todong);		//todong Set
		pNode->SetLossRate1(Lossrate);	//Lossrate Set
		pNode->SetPipeStatus("USE");		//사용 가능

		adjacency.InsertDongEdge(linklist,pNode);	//인접 리스트의 insertDongEdge 함수를 이용해서 Dong Edge를 삽입

		delete pNode;	//동적할당 해제
		delete[] guname;
		delete[] fromdong;
		delete[] todong;
		delete[] Lossrate;
		len=0;	//길이 초기화
		memset(str,0,150);	//배열 초기화
	}

	fin.close();	//파일을 닫는다.

	return true;	//함수종료
}

bool Manager::LoadMechanic(char* filename)	//Mechanic을 읽어오는 함수
{
	ifstream fin(filename);	//파일 open

	if(!fin.is_open())	//파일이 열리지 않을때
		return false;	//실패반환

	char str[100]={'\0'};	//파일 한줄 정보를 저장할 배열
	char* token=NULL;	//원하는 data를 가리킬 포인터
	int len=0;	//길이 변수
	char* workplace=NULL;	//근무지를 가리킬 포인터
	char* name=NULL;		//이름을 가리킬 포인터

	fin.getline(str,100);	//파일의 3줄을 읽어온다
	fin.getline(str,100);
	fin.getline(str,100);
	memset(str,0,100);	//배열 초기화

	while(!fin.eof())	//파일이종료될 때 까지 실행
	{
		fin.getline(str,100);	//파일 한줄을 읽어온다

		if(str[0]==0)	//Enter를 읽어오면
			break;	//파일 종료

		token=strtok(str,"\t");	//token은 근무지를 가리킨다
		len=strlen(token);		//길이측정
		workplace=new char[len+1];	//동적할당
		memset(workplace,0,len+1);	//초기화
		strcpy(workplace,token);	//값을 copy

		token=strtok(NULL,"\t");	//token은 이름을 가리킨다
		len=strlen(token);	//길이측정
		name=new char[len+1];	//동적할당
		memset(name,0,len+1);	//초기화
		strcpy(name,token);		//값을 copy

		Mechanic* pNode=new Mechanic();	//Mechanic type의 변수를 동적할당
		pNode->SetWorkPlace(workplace);	//근무지와 이름 Set
		pNode->SetName(name);

		linklist.InsertMechanic(pNode);	//linklist 객체의 멤버함수 insertMechanic함수를 호출해서 Node삽입

		delete pNode;	//동적할당 해제
		delete[] name;
		delete[] workplace;
		len=0;	//길이 초기화
		memset(str,0,100);	//배열 초기화
	}

	fin.close();	//파일을 닫는다.

	return true;	//함수 종료
}

bool Manager::Update(char* filename)	//Update함수
{
	ifstream fin(filename);	//파일 open

	if(!fin.is_open())	//파일이 열리지 않앗다면
		return false;	//실패

	char str[150]={'\0'};	//파일의 한줄을 저장할 배열
	char* token=NULL;	//원하는 Data를 가리킬 포인터
	int len=0;	//길이를 저장할 변수
	char* guname=NULL;	//guname정보를 저장할 변수
	char* fromdong=NULL;	//fromdong정보를 가리킬 포인터
	char* todong=NULL;		//todong정보를 가리킬 포인터
	char* Lossrate=NULL;	//Lossrate정보를 가리킬 포인터
	bool Mstcheck=false;	//Mst가 구성되었는지 확인할 변수
	Dong_Vertex* pDfrom=NULL;	//From에 해당하는 Dong Vertex를 가리킬 포인터
	Dong_Vertex* pDto=NULL;		//To에 해당하는 Dong Vertex를 가리킬 포인터
	Dong_Edge* pFE=NULL;		//From에 해당하는 Dong Vertex의 Edge를 가리킬 포인터
	Dong_Edge* pTE=NULL;		//To에 해당하는 Dong Vertex의 Edge를 가리킬 포인터

	fin.getline(str,150);	//파일의 3줄을 읽는다
	fin.getline(str,150);
	fin.getline(str,150);
	memset(str,0,150);	//배열 초기화

	while(!fin.eof())	//파일이 종료될 때 까지
	{
		fin.getline(str,150);	//파일 한줄을 읽는다

		if(str[0]==0)	//Enter 입력시
			break;	//반복문 종료

		token=strtok(str,"\t");	//token은 guname정보를 가리킨다
		len=strlen(token);	//길이측정
		guname=new char[len+1];	//동적할당
		memset(guname,0,len+1);	//배열 초기화
		strcpy(guname,token);	//값을 copy

		token=strtok(NULL,"\t");	//token은 fromdong정보를 가리킨다
		len=strlen(token);	//길이 측정
		fromdong=new char[len+1];	//동적할당
		memset(fromdong,0,len+1);	//배열 초기화
		strcpy(fromdong,token);		//값을 copy

		token=strtok(NULL,"\t");	//token은 todong정보를 가리킨다
		len=strlen(token);	//길이측정
		todong=new char[len+1];	//동적할당
		memset(todong,0,len+1);	//배열 초기화
		strcpy(todong,token);	//값을 copy

		token=strtok(NULL,"\t");	//token은 Lossrate정보를 가리킨다
		len=strlen(token);		//길이측정
		Lossrate=new char[len+1];	//동적할당
		memset(Lossrate,0,len+1);	//배열 초기화
		strcpy(Lossrate,token);	//값을 copy

		pDfrom=linklist.FindDong(guname,fromdong);	//불러온 edge의 from에 해당하는 Dong_Vertex
		pFE=pDfrom->GetDENext();		//pDfrom 동의 edge를 탐색할 포인터

		while(pFE!=NULL)	//Dong의 Edge가 있다면
		{
			if(strcmp(pFE->GetToDong(),todong)==0)	//Edge의 ToDong의 이름과 todong이 일치한다면
				break;	//반복문 종료
			pFE=pFE->GetENext();	//다음 Edge로 이동
		}
		if(pFE!=NULL)	//from에 해당하는 edge가 있는경우
		{
			pDto=linklist.FindDong(guname,todong);	//불러온 edge의 to에 해당하는 Dong_Vertex
			pTE=pDto->GetDENext();		//pDto 동의 edge를 탐색할 포인터

			while(pTE!=NULL)	//ToDong의 Edge가 있다면
			{
				if(strcmp(pTE->GetToDong(),fromdong)==0)	//Edge의 ToDong과 fromdong이 일치한다면
					break;	//반복문 종료
				pTE=pTE->GetENext();	//다음 Edge로 이동
			}
		}

		Gu_Vertex* pGNode=linklist.FindGu(guname);	//update 파일에서 읽어온 Dong_Edge의 Gu_Vertex 정보

		if(pFE==NULL)	//해당 edge가 없는 경우 Edge 삽입
		{
			Dong_Edge* pNode1=new Dong_Edge();	//from 에서 to에 해당하는 Dong_Edge 삽입
			pNode1->SetGuName(guname);		//새로 동적할당 한, Node의 값들을 Set한다
			pNode1->SetFromDong(fromdong);
			pNode1->SetToDong(todong);
			pNode1->SetLossRate1(Lossrate);
			pNode1->SetPipeStatus("USE");		//사용 가능여부 를 USE로 설정

			adjacency.InsertDongEdge(linklist,pNode1);	//인접리스트 멤버함수를 통해서 DongEdge를 삽입

			delete pNode1;	//동적할당 해제

			//위에서 삽입한 Dong Edge와 대조를 이루는 Edge삽입
			Dong_Edge* pNode2=new Dong_Edge();	//to에서 from에 해당하는 Dong_Edge 삽입
			pNode2->SetGuName(guname);		//fromdong과 todong의 이름을반대로 Set해서 삽입
			pNode2->SetFromDong(todong);
			pNode2->SetToDong(fromdong);
			pNode2->SetLossRate1(Lossrate);
			pNode2->SetPipeStatus("USE");		//사용 가능여부를 USE로 설정

			adjacency.InsertDongEdge(linklist,pNode2);	//인접리스트 멤버함수를 통해서 Dong Edge를 삽입

			delete pNode2;	//동적할당 해제

			//Mst재구성
			sptree.InitialUseflag(pGNode);	//MST초기화
			Mstcheck=sptree.Kruskal(pGNode);	//MST재구성
			if(Mstcheck==false)	//MST 구성이 되지 않으면
				this->PipeRepair(guname);	//Pipe repair 함수를 호출해서 MST를 구성하도록 한다.
		}
		else	//해당 Edge가 있는 경우 열손실율 update
		{
			//Edge에 대해서 열 손실율 update
			pFE->SetLossRate1(Lossrate);
			pTE->SetLossRate1(Lossrate);
			
			//Mst 재구성
			sptree.InitialUseflag(pGNode);	//MST초기화
			Mstcheck=sptree.Kruskal(pGNode);	//MST재구성
			if(Mstcheck==false)		//MST 구성이 되지 않으면
				this->PipeRepair(guname);	//Pipe repair 함수를 호출해서 MST를 구성하도록 한다.
		}
		
		delete[] guname;	//동적할당 해제
		delete[] fromdong;
		delete[] todong;
		delete[] Lossrate;
		len=0;	//길이 초기화
		memset(str,0,150);	//배열 초기화
	}

	fin.close();	//파일을 닫는다.

	return true;
}

bool Manager::PipeBroken(char* guname, char* fromdong, char* todong)	//PipeBroken 명령어 수행 함수
{
	Dong_Vertex* pFrom=linklist.FindDong(guname, fromdong);	//from에 해당하는 dong vertex
	Dong_Vertex* pTo=linklist.FindDong(guname,todong);		//to에 해당하는 dong vertex

	Dong_Edge* pFE=pFrom->GetDENext();	//From의 edge를 탐색할 pointer
	Dong_Edge* pTE=pTo->GetDENext();		//to의 edge를 탐색할 pointer

	while(pFE!=NULL)	//fromdong -> todong에 해당하는 edge 열수도를 broken상태로 만든다
	{
		if(strcmp(pFE->GetToDong(), todong)==0)	//From Edge의 todong과 todong이 일치하는 경우
		{
			pFE->SetPipeStatus("BROKEN");	//Pipe의 상태를 USE에서 BROKEN으로 설정
			break;	//반복문 종료
		}
		pFE=pFE->GetENext();	//다음 Edge로 이동
	}

	while(pTE!=NULL)	//todong -> fromdong에 해당하는 edge 열수도를 broken 상태로 만든다
	{
		if(strcmp(pTE->GetToDong(), fromdong)==0)	//To Edge의 toDong과 fromdong이 일치하는 경우
		{
			pTE->SetPipeStatus("BROKEN");	//Pipe의 상태를 USE에서 BROKEN으로 설정
			break;	//반복문 종료
		}
		pTE=pTE->GetENext();	//다음 Edge로 이동
	}

	////MST 재구성
	Gu_Vertex* pCur=linklist.FindGu(guname);	//해당 guname의 Gu Vertex를 찾는다
	//pCur는 guname의 Gu Vertex

	////////1. MST useflag 초기화
	sptree.InitialUseflag(pCur);	//해당 구에 대해서 MST 초기화

	////////2. MST 재구성
	bool mst=false;
	mst=sptree.Kruskal(pCur);	//해당 구에 대해서 MST 재구성

	if(mst==true)	//Mst가 구성되었다면
		return true;	//함수 종료
	else if(mst==false)	//Mst가 아니라면
		this->PipeRepair(guname);	//해당 구에 대해서 Pipe_Repair 실행

	

	return true;
}

bool Manager::PipeRepair(char* guname)	//PipeRepair 명령어 수행 함수
{
	//1. 각 정비사의 현재 위치와 목표 위치에 대한 Dijkstra 알고리즘을 이용한 거리 계산
	/////////
	Mechanic* pMCur=linklist.GetMHead();	//mechanic head를 가리킨다
	Gu_Vertex* pSRC=NULL;//source
	Gu_Vertex* pDES=NULL;//destination

	pDES=linklist.FindGu(guname);		//도착점(수리를 요구하는 구)

	while(pMCur!=NULL)	//모든 정비사에 대해서 탐색
	{
		pSRC=linklist.FindGu(pMCur->GetWorkPlace());		//출발점(정비사의 현재근무위치)
		if(pSRC!=NULL)	//출발 근무지가 존재하는 Gu Vertex인 경우
			pMCur->SetDist(sptree.Dijkstra(linklist,pSRC,pDES));	//출발점 -> 도착점까지의 최소 거리 반환 해서 정비사의 이동거리변수에 Set한다

		pMCur=pMCur->GetNext();	//다음 정비사로 이동
	}
	Mechanic* pMin=NULL;	//Dist값이 최소인 정비사를 가리킬 포인터

	pMCur=linklist.GetMHead();	//정비사의 head를 가리킨다
	pMin=pMCur;	//최소인 포인터는 head를 가리킨다
	pMCur=pMCur->GetNext();	//pMCur는 다음 정비사로 이동

	while(pMCur!=NULL)//모든 정비사에 대해서 확인
	{
		if(pMCur->GetDist()<pMin->GetDist())	//pMCur 정비사의 이동 거리가 더 짧다면, pMin의 값은 해당 정비사로 교체
		{
			pMin=pMCur;	//정비사 교체
		}

		pMCur=pMCur->GetNext();	//다음 정비사로 이동
	}
	/////////////pMin은 이동 거리가 최단거리인 정비사


	ofstream fout("repair_log.txt",ios_base::app);	//file이어서 열기

	//2. 최단거리가 가장 적은 정비사의 이름 / 수리를 요구하는 구이름 출력
	fout<<pMin->GetName()<<" / "<<guname<<endl;


	//3. Pipestatus가 USE인 Edge들에 repair log
	fout<<"수리 전 수도 맵 구성"<<endl;

	//pDES는 수리를 요하는 구
	Dong_Vertex* pDCur=pDES->GetDNext();	//동으로 이동
	Dong_Edge* pDECur=NULL;

	do
	{
		pDECur=pDCur->GetDENext();	//해당 동의 Edge를 가리킨다
		while(pDECur!=NULL)
		{
			if(strcmp(pDECur->GetPipeStatus(),"USE")==0&&pDECur->GetUseflag()==1)	//USE상태이며, Mst를 구성하는 Edge를 출력
			{
				fout<<"\t\t"<<pDECur->GetFromDong()<<" -> "<<pDECur->GetToDong()<<" ("<<pDECur->GetLossRate()<<")"<<endl;
			}
			pDECur=pDECur->GetENext();	//다음 dong_edge로 이동
		}

		pDCur=pDCur->GetDVNext();//동 이동
	}while(pDCur!=pDES->GetDNext());

	//4. BROKEN인 Dong_Edge들에 대해서 repair log
	pDCur=pDES->GetDNext();	//다시 도착지의 동으로 이동

	fout<<"수리 수도"<<endl;

	do
	{
		pDECur=pDCur->GetDENext();	//동의 Edge를 가리킨다
		while(pDECur!=NULL)	//Edge가 Null이 아닐 때 까지
		{
			if(strcmp(pDECur->GetPipeStatus(),"BROKEN")==0)	//BROKEN인 경우 해당 Dong Edge를 USE로 바꿔주며 열 수도는 이전의 2배
			{
				//수리하는 부분에 대해서 출력
				fout<<"\t\t["<<pDECur->GetPipeStatus()<<"]"<<pDECur->GetFromDong()<<" -> "<<pDECur->GetToDong();
				fout<<" ("<<pDECur->GetLossRate()<<") -> ("<<pDECur->GetLossRate()*2<<")"<<endl;
				
				pDECur->SetPipeStatus("USE");	//Pipe의 상태를 USE로 바꾸어 준다
				pDECur->SetLossRate2(pDECur->GetLossRate()*2);	//열 수도는 이전의 2배
				
			}
			pDECur=pDECur->GetENext();	//다음 dong_edge로 이동
		}

		pDCur=pDCur->GetDVNext();//동 이동
	}while(pDCur!=pDES->GetDNext());	//원형리스트를 한번 탐색

	//5. ->MST 재구성 (1), useflag초기화, (2), MST구성
	sptree.InitialUseflag(pDES);	//useflag, overlap 초기화
	bool mstcheck=false;
	mstcheck=sptree.Kruskal(pDES);	//MST구성

	//수리를 하였는데 MST가 되지 않는 경우는 없다고 문제에서 가정 만약 있게 된다면 무한 Repiar
	
	//6. 수리 후, Pipestatus가 USE인 Edge들에 대해서 repair log
	fout<<"수리 후 수도 맵 구성"<<endl;
	pDCur=pDES->GetDNext();	//도착지의 Gu Vertex의 동을 가리킨다

	do
	{
		pDECur=pDCur->GetDENext();	//동의 Edge를 가리킨다
		while(pDECur!=NULL)	//Edge를 모두 탐색
		{
			if(strcmp(pDECur->GetPipeStatus(),"USE")==0&&pDECur->GetUseflag()==1)	//use인 경우와 Mst를 이루는 Edge들에대해서만 출력
			{
				//Edge에 대한 출력
				fout<<"\t\t"<<pDECur->GetFromDong()<<" -> "<<pDECur->GetToDong()<<" ("<<pDECur->GetLossRate()<<")"<<endl;
			}
			pDECur=pDECur->GetENext();	//다음 dong_edge로 이동
		}

		pDCur=pDCur->GetDVNext();//동 이동
	}while(pDCur!=pDES->GetDNext());	//원형리스트 탐색


	//7. Dijstra 이동경로와 역추적 이동경로 함수 호출후
	pSRC=linklist.FindGu(pMin->GetWorkPlace());	//출발지가 되는 구에 대해서 찾는다
	int distance=0;	//거리값을 저장할 변수

	distance=sptree.Dijkstra(linklist,pSRC,pDES);	//출발지에서 도착지 까지의 거리를 저장

	//8. stack에서 pop하면서 이동경로 출력
	stack sp;	//stack type의 변수를 설정
	sp=sptree.BackTrace(linklist,pSRC,pDES);	//역추적 함수를 호출해서 반환되는 stack을 받는다

	Gu_Vertex* pCur=sp.Pop();	// stack의 data를 pop한다 -> 출발지

	fout<<pMin->GetName()<<" 정비사의 이동 경로"<<endl;//정비사의 정보 출력

	while(pCur!=NULL)	//stack의 pop한 값이 NULL이 될 때 까지
	{
		//구의 이름과, cost의 정보를 출력
		fout<<pCur->GetGuName()<<"("<<pCur->GetCost()<<")";
		if(pCur!=pDES)	//다음 이동방향 출력
			fout<<" -> ";
		pCur=sp.Pop();	//pCur는 stack에서 Pop한 Node를 가리킨다
	}
	fout<<endl<<endl;

	fout.close();	//파일 닫는다
	///정비사의 현재 근무 위치를 guname으로 변환
	pMin->SetWorkPlace(guname);

	return true;	//함수 종료
}

bool Manager::MST()//열수도에 대해서 MST를 구성하는 함수
{
	Gu_Vertex* pGCur=linklist.GetGVHead();	//Gu_Vertex의 head를 가리킨다
	bool check=false;
	while(pGCur!=NULL)
	{
		check=sptree.Kruskal(pGCur);	//MST 구성 함수 호출
		pGCur=pGCur->GetGVNext();	//다음 Gu_Vertex로 이동
	}

	return true;	//함수종료
}

bool Manager::PrintMap()	//지도 출력 함수
{
	Gu_Vertex* pCur=linklist.GetGVHead();	//Gu Vertex의 head를 가리킨다

	if(pCur==NULL)	//Gu Vertex가 없다면
		return false;	//실패

	Gu_Edge* pECur=NULL;	//Gu Edge를 가리킬 포인터

	ofstream fout("map.txt",ios_base::app);	//파일을 이어서 open

	//파일의 형식 출력
	fout<<"===================================="<<endl;
	fout<<"\t      PRINT MAP"<<endl;
	fout<<"===================================="<<endl;

	while(pCur!=NULL)	//Gu Vertex가 NULL일 때 까지
	{
		pECur=pCur->GetGENext();	//Gu Vertex의 Edge를 가리킨다

		while(pECur!=NULL)	//Edge가 NULL이 아닐 때 까지
		{
			//구의 Edge에 대해서 출력
			fout<<pECur->GetFromGu()<<" -> "<<pECur->GetToGu()<<" ("<<pECur->GetDist()<<")"<<endl;
			pECur=pECur->GetENext();	//다음 Edge로 이동
		}

		pCur=pCur->GetGVNext();	//Gu Vertex이동
	}

	fout.close();	//파일 닫는다

	return true;	//함수종료
}

bool Manager::PrintPipe(Gu_Vertex* GuNode)	//구의 파이프 출력 함수
{
	if(GuNode==NULL)	//해당 구가 존재하지 않는다.
		return false;

	Dong_Vertex* pDCur=GuNode->GetDNext();	//Dong을 가리킬 포인터
	Dong_Edge* pDECur=NULL;	//Dong Edge를 가리킬 포인터

	ofstream fout("pipe.txt",ios_base::app);	//파일을 이어서 open

	//파일의 형식 출력
	fout<<"===================================="<<endl;
	fout<<"\t\tPIPE"<<endl;
	fout<<"===================================="<<endl;

	do
	{
		pDECur=pDCur->GetDENext();	//Dong Edge는 Dong Vertex의 Edge를 가리킨다
		while(pDECur!=NULL)	//모든 Edge탐색
		{
			if(strcmp(pDECur->GetPipeStatus(),"USE")==0&&pDECur->GetUseflag()==1)	//MST를 구성하는 Edge에 대해서 출력
			{
				fout<<GuNode->GetGuName()<<" : ";
				fout<<pDECur->GetFromDong()<<" -> "<<pDECur->GetToDong()<<" ("<<pDECur->GetLossRate()<<")"<<endl;
			}
			pDECur=pDECur->GetENext();	//다음 Edge로 이동
		}
		pDCur=pDCur->GetDVNext();	//다음 Dong Vertex로 이동
	}while(pDCur!=GuNode->GetDNext());	//모든 Dong에 대해서 탐색

	fout.close();	//파일 닫는다

	return true;	//함수종료
}

bool Manager::PrintMechanic()	//정비사 출력 함수
{
	Mechanic* pCur=linklist.GetMHead();	//정비사 head를 가리킨다
	if(pCur==NULL)	//없다면
		return false;	//함수종료

	ofstream fout("mechanic_list.txt",ios_base::app);	//파일을 이어서 open

	//file 형식 출력
	fout<<"===================================="<<endl;
	fout<<"\t      MECHANIC INFO"<<endl;
	fout<<"===================================="<<endl;


	while(pCur!=NULL)	//모든 정비사 탐색
	{
		//정비사 정보 출력
		fout<<pCur->GetName()<<" - "<<pCur->GetWorkPlace()<<endl;
		pCur=pCur->GetNext();	//다음 정비사로 이동
	}

	fout.close();	//파일 닫는다

	return true;	//함수종료
}

bool Manager::Save()	//Save명령어 수행함수
{
	this->SaveGuVertex();	//Gu Vertex저장 함수

	this->SaveGuEdge();	//Gu Edge저장 함수

	this->SaveDongVertex();	//Dong Vertex저장 함수

	this->SaveDongEdge();	//Dong Edge 저장함수

	this->SaveMechanic();	//정비사 저장 함수

	return true;	//함수종료
}

bool Manager::SaveGuVertex()	//Gu Vertex에 대한 Save함수
{
	ofstream fout("gu_vertex.bak");	//파일 open

	if(!fout.is_open())	//파일이 제대로 열리지 않았다면
		return false;	//실패 반환

	//파일 형식 출력
	fout<<"========================="<<endl;
    fout<<"    서울시 구 명칭	"<<endl;
	fout<<"========================="<<endl;

	Gu_Vertex* pCur=linklist.GetGVHead();	//Gu Vertex는 Gu의 head를 가리킨다

	while(pCur!=NULL)	//모든 Gu에 대해서 탐색
	{
		fout<<"\t"<<pCur->GetGuName()<<endl;	//정보 출력
		pCur=pCur->GetGVNext();	//다음 Gu로 이동
	}

	fout.close();	//end file

	return true;	//함수 종료
}

bool Manager::SaveGuEdge()	//Gu Edge에 대한 Save함수
{
	ofstream fout("gu_edge.bak");	//파일 open

	if(!fout.is_open())	//파일이 제대로 열리지 않았다면
		return false;	//실패 반환

	//파일 형식 출력
	fout<<"===================================================================================="<<endl;
	fout<<"	from(구)			to(구)			   distance (Km)"<<endl;
	fout<<"===================================================================================="<<endl;

	Gu_Vertex* pCur=linklist.GetGVHead();	//Gu Vertex의 head를 가리킨다
	Gu_Edge* pECur=NULL;	//Gu Edge를 가리킬 포인터
	
	while(pCur!=NULL)	//모든 Gu Vertex 탐색
	{
		pECur=pCur->GetGENext();	//해당 GU의 Edge를 가리킨다
		while(pECur!=NULL)	//모든 Edge탐색
		{
			//Edge정보 출력
			fout<<"\t"<<pECur->GetFromGu();
			fout<<"\t\t\t"<<pECur->GetToGu();
			fout<<"\t\t\t\t"<<pECur->GetDist()<<endl;

			pECur=pECur->GetENext();	//다음 Edge로 이동
		}

		pCur=pCur->GetGVNext();	//다음 Gu Vertex로 이동
	}

	fout.close();	//end file

	return true;	//함수종료
}

bool Manager::SaveDongVertex()	//Dong Vertex에 대한 Save함수
{
	ofstream fout("dong_vertex.bak");	//파일 open

	if(!fout.is_open())	//파일이 제대로 열리지 않았다면
		return false;	//실패 반환

	//파일 형식 출력
	fout<<"================================================================================="<<endl;
	fout<<"	구 명칭			동 명칭			난방 관제소 여부(O/X)	"<<endl;
	fout<<"================================================================================="<<endl;

	Gu_Vertex* pGCur=linklist.GetGVHead();	//Gu의 Head를 가리킨다
	Dong_Vertex* pDCur=NULL;	//동을 가리킬 포인터

	while(pGCur!=NULL)	//모든 gu탐색
	{
		pDCur=pGCur->GetDNext();	//head가 되는 Dong을 가리킨다
		if(pDCur!=NULL)	//Dong이 존재한다면
		{
			do
			{
				//동에대한 정보 출력
				fout<<"\t"<<pDCur->GetGuName();
				fout<<"\t\t\t"<<pDCur->GetDongName();
				fout<<"\t\t\t\t"<<pDCur->GetHeatCheck()<<endl;
				pDCur=pDCur->GetDVNext();	//다음 Dong으로 이동

			}while(pDCur!=pGCur->GetDNext());	//원형 List에서 모든 동에 접근한다
		}
		pGCur=pGCur->GetGVNext();	//다음 Gu로 이동
	}

	fout.close();	//end file

	return true;	//함수 종료
}

bool Manager::SaveDongEdge()	//Dong Edge에 대한 Save함수
{
	ofstream fout("dong_edge.bak");	//파일을 연다

	if(!fout.is_open())	//파일이 제대로 열리지 않았다면
		return false;	//실패 반환

	//파일 형식 출력
	fout<<"=============================================================================================="<<endl;
	fout<<"	구 명칭			from(동)			to(동)		    열 손실률(%)"<<endl;
	fout<<"=============================================================================================="<<endl;

	Gu_Vertex* pGCur=linklist.GetGVHead();	//Head가 되는 Gu를 가리킨다
	Dong_Vertex* pDCur=NULL;	//Dong을 가리킬 포인터
	Dong_Edge* pDECur=NULL;		//Dong Edge를 가리킬 포인터

	while(pGCur!=NULL)	//모든 Gu에대해서 탐색
	{
		pDCur=pGCur->GetDNext();	//Gu의 head가 되는 Dong을 가리킨다
		if(pDCur!=NULL)	//Dong이 NULL이 아니라면
		{
			do
			{
				pDECur=pDCur->GetDENext();	//Dong의 Edge로 이동
				while(pDECur!=NULL)	//Edge모두 탐색
				{
					//Edge정보 출력
					fout<<"\t"<<pDECur->GetGuName();
					fout<<"\t\t\t"<<pDECur->GetFromDong();
					fout<<"\t\t\t"<<pDECur->GetToDong();
					fout<<"\t\t\t"<<pDECur->GetLossRate()<<endl;

					pDECur=pDECur->GetENext();	//다음 Dong Edge로 이동
				}

				pDCur=pDCur->GetDVNext();	//Dong Vertex이동
			}while(pDCur!=pGCur->GetDNext());	//원형 list를 한바퀴 참조
		}
		pGCur=pGCur->GetGVNext();	//다음 Gu vertex로 이동
	}

	fout.close();	//end file

	return true;	//함수 종료
}

bool Manager::SaveMechanic()	//정비사에 대한 Save함수
{
	ofstream fout("mechanic.bak");	//file open

	if(!fout.is_open())	//파일이 제대로 열리지 않았다면
		return false;	//실패 반환

	//파일 형식 출력
	fout<<"============================================"<<endl;
	fout<<"	근무지		정비사 이름		"<<endl;
	fout<<"============================================"<<endl;

	Mechanic* pMec=linklist.GetMHead();	//정비사의 head를 가리킨다

	while(pMec!=NULL)	//모든 정비사 탐색
	{
		//정비사정보 출력
		fout<<"\t"<<pMec->GetWorkPlace();
		fout<<"\t\t"<<pMec->GetName()<<endl;
		pMec=pMec->GetNext();	//다음 정비사로 이동
	}

	fout.close();	//end file

	return true;	//함수 종료
}