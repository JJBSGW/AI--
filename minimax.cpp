#include<iostream> 
#include<stdlib.h> 
#include<conio.h>  
#include<algorithm> 

using namespace std;

#define MAN 1 //人 
#define COM -1 //机 

int isEnd(); //检查是否结束
void show();//展示棋盘 
void init();//初始化 
void win_lose();//判断输赢 
void listen();//监听插入操作 
void manPlay(int x ,int y);//人操作
void comPlay();//机器操作 
int minimaxSearch(int depth);

int curDepth = 0;//当前深度 
int player = 0; 
int times = 0;//次数 

int board[3][3]={{0,0,0},{0,0,0},{0,0,0}}; //棋盘 
bool over = false;
 
struct chose{
	int x;
	int y;
};

chose bestChose;//最佳选择 

void manPlay(int x ,int y){
	board[x][y] = MAN;
	curDepth++;
	player = COM;//交换棋权 
}

void comPlay(){
	minimaxSearch(curDepth);
	board[bestChose.x][bestChose.y] = COM;
	curDepth++;
	player = MAN;
}

int Evaluate(){//评估函数 
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
			//还未操作 
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
		if (!over){//不结束
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
			cout<<"玩家胜利"<<endl; 
			cout<<"按 x 退出"<<endl;
		}
		else if (isEnd() == COM){
			cout<<"电脑胜利"<<endl;
			cout<<"按 x 退出"<<endl; 
		}
		else if(isEnd() == 0){
			cout<<"游戏平局"<<endl;
			cout<<"按 x 退出"<<endl;
		}
	}
}

void init(){//初始化 
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

int isEnd(){//返回 1 人胜 
	int count = 0;
	for (int i = 0;i<3;i++){//计算行 
		count = 0;
		count = board[i][0] +board[i][1] +board[i][2];
		if (count == 3||count == -3){
			return count/3;
		}
	}
	for (int i = 0;i<3;i++){//计算列 
		count = 0;
		count = board[0][i] +board[1][i] +board[2][i];
		if (count == 3||count == -3){
			return count/3;
		}
	}
	//计算斜 
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

void show(){//绘画 
	system("cls");
	cout<<"按 r 重开"<<endl;
	cout<<"本次使用了"<<times<<"次"<<endl;
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
