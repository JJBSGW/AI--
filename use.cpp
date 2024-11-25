#include <cstdlib> // 对于 Windows 使用 <cstdlib>
#include<iostream> 

using namespace std;

int main() {
	while (true){
		system("cls");
		cout<<"which one you want to use?\n"<<endl;
		cout<<"1) minimax"<<"  |  "<<"2)Alpha_Beta"<<"  |  "<<"3)MTCS"<<"  |  "<<"4)exit\n"<<endl;
		char c = getchar();
		switch (c){
			// 调用第一个程序
			case '1':system("C:\\Users\\Lucky\\Desktop\\ZHINENG\\minimax.exe");break;
			// 调用第二个程序
			case '2':system("C:\\Users\\Lucky\\Desktop\\ZHINENG\\AB.exe");break;
			// 调用第三个程序
			case '3':system("cls");system("C:\\Users\\Lucky\\Desktop\\ZHINENG\\MT.exe");break;
			// 退出 
			case '4':exit(0);break;
			//
			default:cout<<"invalid!"<<endl;break; 
		}
	}
    return 0;
}
