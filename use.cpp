#include <cstdlib> // ���� Windows ʹ�� <cstdlib>
#include<iostream> 

using namespace std;

int main() {
	while (true){
		system("cls");
		cout<<"which one you want to use?\n"<<endl;
		cout<<"1) minimax"<<"  |  "<<"2)Alpha_Beta"<<"  |  "<<"3)MTCS"<<"  |  "<<"4)exit\n"<<endl;
		char c = getchar();
		switch (c){
			// ���õ�һ������
			case '1':system("C:\\Users\\Lucky\\Desktop\\ZHINENG\\minimax.exe");break;
			// ���õڶ�������
			case '2':system("C:\\Users\\Lucky\\Desktop\\ZHINENG\\AB.exe");break;
			// ���õ���������
			case '3':system("cls");system("C:\\Users\\Lucky\\Desktop\\ZHINENG\\MT.exe");break;
			// �˳� 
			case '4':exit(0);break;
			//
			default:cout<<"invalid!"<<endl;break; 
		}
	}
    return 0;
}
