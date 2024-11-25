#include<iostream> 
#include<stdlib.h> 
#include<conio.h>  
#include<algorithm> 

using namespace std;

#define MAN 1 //�� 
#define COM -1 //�� 

int isEnd(); //����Ƿ����
void show();//չʾ���� 
void init();//��ʼ�� 
void win_lose();//�ж���Ӯ 
void listen();//����������� 
void manPlay(int x ,int y);//�˲���
void comPlay();//�������� 
int minimaxSearch(int depth);

int curDepth = 0;//��ǰ��� 
int player = 0; 
int times = 0;//���� 

int board[3][3]={{0,0,0},{0,0,0},{0,0,0}}; //���� 
bool over = false;
 
struct chose{
	int x;
	int y;
};

chose bestChose;//���ѡ�� 

void manPlay(int x ,int y){
	board[x][y] = MAN;
	curDepth++;
	player = COM;//������Ȩ 
}

void comPlay(){
	minimaxSearch(curDepth);
	board[bestChose.x][bestChose.y] = COM;
	curDepth++;
	player = MAN;
}

int Evaluate(){//�������� 
	int value = isEnd();
	if (value == MAN)return INT_MAX;
	if (value == COM)return INT_MIN;

	return value;
}

int minimaxSearch(int depth){
	
	int value = 0;
	if (player == MAN) value = INT_MIN;
	if (player == COM) value = INT_MAX;
	if (isEnd() != 0)
	{
		return Evaluate();
	}
	if (depth == 9)
	{
		value = Evaluate();
		return value;
	}
	for (int i = 0;i<3;i++){
		for (int j = 0;j<3;j++){
			//��δ���� 
			if (board[i][j] == 0){ 
				times++;
				if (player == MAN){
					board[i][j] = MAN;
					player = COM;
					int nextvalue = minimaxSearch(depth + 1);
					player = MAN;
					if (value < nextvalue)
					{
						value = nextvalue;
						if (depth == curDepth)
						{
							bestChose.x = i;
							bestChose.y = j;
						}
					}		
				}
				
				else if (player == COM){
					board[i][j] = COM;
					player = MAN;
					int nextvalue = minimaxSearch(depth + 1);
					player = COM;
					if (value>nextvalue)
					{
						value = nextvalue;
						if (depth == curDepth)
						{
							bestChose.x = i;
							bestChose.y = j;
						}
					}
				}
			board[i][j] = 0;	
			}
		}
	}
}

void listen(){
	if (_kbhit){
		char c = _getch();
		int num = c - '1';
		int temp_x = num /3;
		int temp_y = num %3;
		if (!over){//������
			if (board[temp_x][temp_y] != 0){
		 		show();
				}
			else if (c >= '1' && c <= '9'){
		 		
		 		manPlay(temp_x , temp_y);
				if (isEnd() == 0 && curDepth < 8){
		 			comPlay();
					 if (isEnd() != 0){
					 	over = true;
					 	}	
					}else{
						over = true;
						}

			}else if (c == 'X' || c == 'x'){
					exit(0);
					}
		 	else if (c == 'r' || c == 'R'){
					init();
				}
		
		}
		if (over){
			if (c == 'r' || c == 'R'){
				init();
			}
			if (c == 'X' || c == 'x'){
			exit(0);
		}
		} 
	}
	
	
}

void win_lose(){
	//system("cls");
	if (over){
		if (isEnd() == MAN){
			cout<<"���ʤ��"<<endl; 
			cout<<"�� x �˳�"<<endl;
		}
		else if (isEnd() == COM){
			cout<<"����ʤ��"<<endl;
			cout<<"�� x �˳�"<<endl; 
		}
		else if(isEnd() == 0){
			cout<<"��Ϸƽ��"<<endl;
			cout<<"�� x �˳�"<<endl;
		}
	}
}

void init(){//��ʼ�� 
	system("cls");
	for (int i = 0;i<3;i++){
		for (int j = 0;j<3;j++){
			board[i][j] = 0;
		}
	}
	cout<<"Who go first?(M/C)";
	char c = getchar();
	if (c == 'M'||c == 'm'){
		player = MAN;
	}
	else if (c == 'c' || c == 'C'){
		player = -1;
		comPlay();
	}
	
	over = false;
	curDepth = 0;
	show(); 
}

int isEnd(){//���� 1 ��ʤ 
	int count = 0;
	for (int i = 0;i<3;i++){//������ 
		count = 0;
		count = board[i][0] +board[i][1] +board[i][2];
		if (count == 3||count == -3){
			return count/3;
		}
	}
	for (int i = 0;i<3;i++){//������ 
		count = 0;
		count = board[0][i] +board[1][i] +board[2][i];
		if (count == 3||count == -3){
			return count/3;
		}
	}
	//����б 
	count = 0;
	count = board[0][0] +board[1][1] +board[2][2];
	if (count == 3||count == -3){
			return count/3;
		}
	count = board[0][2] +board[1][1] +board[2][0];
	if (count == 3||count == -3){
			return count/3;
		}
	count = 0;
	
	return 0;
}

void show(){//�滭 
	system("cls");
	cout<<"�� r �ؿ�"<<endl;
	cout<<"����ʹ����"<<times<<"��"<<endl;
	cout<<"\n"<<"---------------"<<endl;
	for (int i = 0;i<3;i++){
		for (int j = 0;j<3;j++){
			cout<<"| "<<board[i][j]<<" |";
		}
		cout<<"\n"<<"---------------"<<endl;
	}
	times = 0;
}

void start(){
	init();
	while(1){
		listen(); 
		show();
		win_lose();
	} 
}

int main(void){
	start();
}
