#include"Manager.h"

int main()
{
	char filename[50]={"cmd.txt"};
	Manager manager;	//Manager class type변수 선언
	cout<<"== EXECUTE COMMAND filename : "<<filename<<" =="<<endl;
	manager.Command(filename);	//"input file인 cmd.txt에 대해서 Command 실행
	cout<<"== END THE PROGRAM =="<<endl;
	return 0;
}