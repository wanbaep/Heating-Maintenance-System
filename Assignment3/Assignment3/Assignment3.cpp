#include"Manager.h"

int main()
{
	char filename[50]={"cmd.txt"};
	Manager manager;	//Manager class type���� ����
	cout<<"== EXECUTE COMMAND filename : "<<filename<<" =="<<endl;
	manager.Command(filename);	//"input file�� cmd.txt�� ���ؼ� Command ����
	cout<<"== END THE PROGRAM =="<<endl;
	return 0;
}