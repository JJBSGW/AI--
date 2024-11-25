#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

#define PLAYER_X 1
#define PLAYER_O -1
#define EMPTY 0
#define SIZE 3

class TicTacToe {
public:
    TicTacToe() {
        board.resize(SIZE, vector<int>(SIZE, EMPTY));// 初始化棋盘大小和空位
        currentPlayer = PLAYER_X;// 初始玩家为X
    }
	
	// 打印棋盘状态
    void printBoard() {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                char c = board[i][j] == PLAYER_X ? 'X' : (board[i][j] == PLAYER_O ? 'O' : '.');
                std::cout << c << " ";
            }
            cout << endl;
        }
    }
	
	// 玩家进行移动
    bool makeMove(int x, int y) {
        if (board[x][y] == EMPTY) {
            board[x][y] = currentPlayer;
            currentPlayer = -currentPlayer; // Switch player
            return true;
        }
        return false;
    }
	
	// 检查游戏是否结束，并返回获胜者
    bool isGameOver(int &winner) {
        // Check rows and columns
        for (int i = 0; i < SIZE; ++i) {
            if (abs(board[i][0] + board[i][1] + board[i][2]) == 3) {
                winner = board[i][0];
                return true;
            }
            if (abs(board[0][i] + board[1][i] + board[2][i]) == 3) {
                winner = board[0][i];
                return true;
            }
        }
        // 斜
        if (abs(board[0][0] + board[1][1] + board[2][2]) == 3) {
            winner = board[1][1];
            return true;
        }
        if (abs(board[0][2] + board[1][1] + board[2][0]) == 3) {
            winner = board[1][1];
            return true;
        }
        // 平局
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == EMPTY) return false;
            }
        }
        winner = 0; 
        return true;
    }
	
	// 获取所有可能的移动
    vector<pair<int, int> > getAvailableMoves() {
        vector<pair<int, int> > moves;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == EMPTY) {
                    moves.push_back(make_pair(i, j));
                }
            }
        }
        return moves;
    }
	
	// 重置游戏
    void reset() {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                board[i][j] = EMPTY;
            }
        }
        currentPlayer = PLAYER_X;
    }

private:
    vector<vector<int> > board;
    int currentPlayer;
};

class MCTS {
public:
    MCTS(TicTacToe &game) : game(game) {}
	
	// 获取最佳移动
    pair<int, int> getBestMove() {
        vector<pair<int, int> > moves = game.getAvailableMoves();
        if (moves.empty()) return make_pair(-1, -1);//满了返回无法移动 

        srand(time(0));//随机化 
        pair<int, int> bestMove = moves[rand() % moves.size()];//随机选择起始点 

        for (int i = 0; i < 50000; ++i) { // 模拟？局游戏
            TicTacToe simGame = game;
            simGame.makeMove(bestMove.first, bestMove.second);
            while (true) {
                int winner;
                if (simGame.isGameOver(winner)) {
                    break;// 如果游戏结束，跳出循环
                }
                vector<pair<int, int> > availableMoves = simGame.getAvailableMoves();
                pair<int, int> randomMove = availableMoves[rand() % availableMoves.size()];//随机从可用移动选一个 
                simGame.makeMove(randomMove.first, randomMove.second);
            }
        }
        return bestMove; // 返回模拟获胜次数最多的移动
    }

private:
    TicTacToe &game;
};

void start() {
    TicTacToe game;
    MCTS mcts(game);
    int winner;
	
    while (true) {
        game.printBoard();
        pair<int, int> move;
        
        if (game.getAvailableMoves().size() == 0) {
            cout << "Draw!" << endl;
            break;
        }

        // Player X's turn
        cout << "Player X, enter your move (row and column): ";
        int x, y;
        cin >> x >> y;
        if (!game.makeMove(x, y)) {
            cout << "Invalid move! Try again." << endl;
            continue;
        }

        if (game.isGameOver(winner)) {
            if (winner == PLAYER_X) {
                game.printBoard();
                cout << "Player X wins!" << endl;
                break;
            } else if (winner == PLAYER_O) {
                game.printBoard();
                cout << "Player O wins!" << endl;
                break;
            } else {
                game.printBoard();
                cout << "Draw!" << endl;
                break;
            }
        }

        // Player O's turn using MCTS
        move = mcts.getBestMove();
        game.makeMove(move.first, move.second);
        cout << "Player O makes move: " << move.first << ", " << move.second << endl;

        if (game.isGameOver(winner)) {
            if (winner == PLAYER_X) {
                game.printBoard();
                cout << "Player X wins!" << endl;
                break;
            } else if (winner == PLAYER_O) {
                game.printBoard();
                cout << "Player O wins!" << endl;
                break;
            } else {
                game.printBoard();
                cout << "Draw!" << endl;
                break;
            }
        }
    }
}

int main(){
	start();
	return 0;
}
