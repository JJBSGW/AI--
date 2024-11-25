#include <iostream>
#include <vector>
#include <limits>
#include<stdlib.h> 
#include<conio.h>  
#include<algorithm> 

using namespace std;

#define MAN 1 //�� 
#define COM -1 //�� 

int board[3][3]={{0,0,0},{0,0,0},{0,0,0}};
bool over = false;
int player = 0;
int curDepth = 0;//��ǰ���
int times = 0;

int alphaBetaSearch(int depth , int alpha , int beta , bool Player);

struct chose{
	int x;
	int y;
};

chose bestChose;//���ѡ��

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
	//times = 0;
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
	player = COM;//������Ȩ 
}

void init(){//��ʼ�� 
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
					}//beta��֦ 
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
				}//alpha��֦ 
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
                //cout << "��λ���ѱ�ռ�ã���ѡ������λ�á�" << endl;
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
