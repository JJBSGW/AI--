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
        board.resize(SIZE, vector<int>(SIZE, EMPTY));// ��ʼ�����̴�С�Ϳ�λ
        currentPlayer = PLAYER_X;// ��ʼ���ΪX
    }
	
	// ��ӡ����״̬
    void printBoard() {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                char c = board[i][j] == PLAYER_X ? 'X' : (board[i][j] == PLAYER_O ? 'O' : '.');
                std::cout << c << " ";
            }
            cout << endl;
        }
    }
	
	// ��ҽ����ƶ�
    bool makeMove(int x, int y) {
        if (board[x][y] == EMPTY) {
            board[x][y] = currentPlayer;
            currentPlayer = -currentPlayer; // Switch player
            return true;
        }
        return false;
    }
	
	// �����Ϸ�Ƿ�����������ػ�ʤ��
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
        // б
        if (abs(board[0][0] + board[1][1] + board[2][2]) == 3) {
            winner = board[1][1];
            return true;
        }
        if (abs(board[0][2] + board[1][1] + board[2][0]) == 3) {
            winner = board[1][1];
            return true;
        }
        // ƽ��
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == EMPTY) return false;
            }
        }
        winner = 0; 
        return true;
    }
	
	// ��ȡ���п��ܵ��ƶ�
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
	
	// ������Ϸ
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
	
	// ��ȡ����ƶ�
    pair<int, int> getBestMove() {
        vector<pair<int, int> > moves = game.getAvailableMoves();
        if (moves.empty()) return make_pair(-1, -1);//���˷����޷��ƶ� 

        srand(time(0));//����� 
        pair<int, int> bestMove = moves[rand() % moves.size()];//���ѡ����ʼ�� 

        for (int i = 0; i < 50000; ++i) { // ģ�⣿����Ϸ
            TicTacToe simGame = game;
            simGame.makeMove(bestMove.first, bestMove.second);
            while (true) {
                int winner;
                if (simGame.isGameOver(winner)) {
                    break;// �����Ϸ����������ѭ��
                }
                vector<pair<int, int> > availableMoves = simGame.getAvailableMoves();
                pair<int, int> randomMove = availableMoves[rand() % availableMoves.size()];//����ӿ����ƶ�ѡһ�� 
                simGame.makeMove(randomMove.first, randomMove.second);
            }
        }
        return bestMove; // ����ģ���ʤ���������ƶ�
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
