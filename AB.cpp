#include <iostream>
#include <vector>
#include <limits>
#include<stdlib.h> 
#include<conio.h>  
#include<algorithm> 

using namespace std;

#define MAN 1 //人 
#define COM -1 //机 

int board[3][3]={{0,0,0},{0,0,0},{0,0,0}};
bool over = false;
int player = 0;
int curDepth = 0;//当前深度
int times = 0;

int alphaBetaSearch(int depth , int alpha , int beta , bool Player);

struct chose{
	int x;
	int y;
};

chose bestChose;//最佳选择

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
	//times = 0;
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

void comPlay(){
	times = 0;
	cout<<"COM play"<<endl;
	int bestValue = INT_MIN;
	for (int i = 0 ;i<3;i++){
		for (int j = 0;j<3;j++){
			if (board[i][j] == 0){
				board[i][j] = COM;
				int value = alphaBetaSearch(curDepth , INT_MIN , INT_MAX , false);
				board[i][j] = 0;
				if (value > bestValue){
					bestValue = value;
					bestChose.x = i;
					bestChose.y = j;
				}
			}
		}
	}
	board[bestChose.x][bestChose.y] = COM;
}

void manPlay(int x ,int y){
	cout<<"MAN paly"<<endl;
	board[x][y] = MAN;
	curDepth++;
	player = COM;//交换棋权 
}

void init(){//初始化 
    times = 0;
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
		player = COM;
		comPlay();
	}
	over = false;
	curDepth = 0;
	show(); 
}

int alphaBetaSearch(int depth , int alpha , int beta , bool Player){
	times++;
	switch (isEnd()){
		case -1:return (-10 + depth);
		case 1:return (10 + depth);
		case 0:return 0;
	}
	
	if (Player){
		int maxValue = INT_MIN;
		for (int i = 0 ;i<3;i++){
			for (int j = 0;j<3;j++){
				if (board[i][j] == 0){
					board[i][j] = MAN;
					int value = alphaBetaSearch(depth + 1, alpha , beta , false);
					board[i][j] = 0;
					maxValue = max(maxValue , value);
					alpha = max(alpha , value);
					if (beta <= alpha){
						break;
					}//beta剪枝 
				}
			}
		}
		return maxValue;
	}else{
		int minValue = INT_MAX;
		for (int i = 0 ;i<3;i++){
			for (int j = 0;j<3;j++){
				board[i][j] = COM;
				int value = alphaBetaSearch(depth + 1, alpha , beta , true);
				board[i][j] = 0;
				minValue = min(minValue , value);
				beta = min(beta , value);
				if (beta <= alpha){
					break;
				}//alpha剪枝 
			}
		}
		return minValue;
	}
}

void listen() {
    if (_kbhit()) {
        char c = _getch();
        int num = c - '1';
        int temp_x = num / 3;
        int temp_y = num % 3;

        if (!over) {
            if (board[temp_x][temp_y] != 0) {
                show();
                //cout << "该位置已被占用，请选择其他位置。" << endl;
            } else if (c >= '1' && c <= '9') {
                manPlay(temp_x, temp_y);
                if (isEnd() != 0) {
                    over = true;
                } else {
                    comPlay();
                    if (isEnd() != 0) {
                        over = true;
                    }
                }
            } else if (c == 'x' || c == 'X') {
                exit(0);
            } else if (c == 'r' || c == 'R') {
                init();
            }
        } else {
            if (c == 'x' || c == 'X') {
                exit(0);
            }
            if (c == 'r' || c == 'R') {
                init();
            }
        }
    }
}

void startAB(){
	init();
	while(true){
		listen(); 
		show();
		win_lose();
	}
}

int main(void){
	startAB();
	return 0; 
}
