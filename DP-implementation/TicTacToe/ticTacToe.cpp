//
// Created by Ujjwal Shukla on 09/10/23.
//
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <deque>
#include <algorithm>

using namespace std;


//logically the code is correct but don't use enum in real, otherwise there will be issue in printing and comparing. Simply use char.
enum PieceType {
    X,
    O,
};

class Piece {
public:
    PieceType pieceType;
    Piece(PieceType pieceType) {
        this->pieceType = pieceType;
    }
    PieceType* getPieceType() {
        return &this->pieceType;
    }
};

class XPiece: public Piece{
public:
    XPiece(): Piece(X) {};
};

class OPiece: public Piece {
public:
    OPiece(): Piece(O) {};
};

class Player {
    Piece* piece;
    string name;
public:
    Player(Piece* piece, const string& name) {
        this->piece = piece;
        this->name = name;
    }
    string getName() {
        return this->name;
    }
    Piece* getPiece() {
        return this->piece;
    }
};

class Board {
    int size;
public:
    vector<vector<PieceType*> > board;
    Board(int size) {
        this->size = size;
        for (int i=0;i<size;i++) {
            vector<PieceType*> row;
            for(int j=0;j<size;j++) {
                row.push_back(nullptr);
            }
            this->board.push_back(row);
        }
    }

    vector<pair<int, int> > getFreeCells() {
        vector<pair<int, int> > freeCells;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if(this->board[i][j] == nullptr) {
                    freeCells.push_back(make_pair(i,j));
                }
            }
        }
        return freeCells;
    }

    void printBoard() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                PieceType* piece = this->board[i][j];
                if (piece == nullptr) {
                    cout<< "  " << " |";
                } else {
                    cout<< piece << " |";
                }
            }
            cout<<"\n";
        }
    }

    bool addPiece(int x, int y, PieceType* piece) {
        if(this->board[x][y] == nullptr) {
            board[x][y] = piece;
            return true;
        }
        return false;
    }
    int getSize() {
        return this->size;
    }
};

class TicTacToeGame {
    deque<Player*> playerDeque;
    Board* board;
    bool checkWinner(int row, int column, PieceType* piece) {
        bool rowMatch = true;
        bool columnMatch = true;
        bool diagonalMatch = true;
        bool antiDiagonalMatch = true;
        auto board = this->board->board;
        //need to check in row
        for(int i=0;i<board.size();i++) {

            if(board[row][i] == nullptr || board[row][i] != piece) {
                rowMatch = false;
            }
        }

        //need to check in column
        for(int i=0;i<board.size();i++) {

            if(board[i][column]  == nullptr || board[i][column] != piece) {
                columnMatch = false;
            }
        }

        //need to check diagonals
        for(int i=0, j=0; i<board.size();i++,j++) {
            if (board[i][j] == nullptr || board[i][j] != piece) {
                diagonalMatch = false;
            }
        }

        //need to check anti-diagonals
        for(int i=0, j=board.size()-1; i<board.size();i++,j--) {
            if (board[i][j] == nullptr || board[i][j] != piece) {
                antiDiagonalMatch = false;
            }
        }

        return rowMatch || columnMatch || diagonalMatch || antiDiagonalMatch;
    }
public:



    TicTacToeGame() {
        this->board = new Board(3);
        Player* XPlayer = new Player(new XPiece(), "XPlayer");
        Player* OPlayer = new Player(new OPiece(), "OPlayer");
        playerDeque.push_back(XPlayer);
        playerDeque.push_back(OPlayer);
    }

    void startGame() {
        bool haveWinner = false;
        Player* winner;
        while(!haveWinner) {
            Player* player = this->playerDeque.front();
            playerDeque.pop_front();
            this->board->printBoard();
            cout<<"enter the position to add piece " << player->getName()<<" piece "<<player->getPiece()<<"\n";
            auto freeCells = this->board->getFreeCells();
            if (freeCells.empty()) {
                break;
            }
            int x, y;
            cin>>x>>y;
            auto move = make_pair(x, y);
            if (find(freeCells.begin(), freeCells.end(), move) == freeCells.end() || x>=board->getSize() || y >= board->getSize()) {
                cout<<"invalid move, try again"<<"\n";
                playerDeque.push_front(player);
            }
            board->addPiece(x, y, player->getPiece()->getPieceType());
            if (checkWinner(x, y, player->getPiece()->getPieceType())) {
                haveWinner = true;
                winner = player;
                break;
            }
        }
        if (haveWinner) {
            cout<<" winner is "<<winner->getName()<<" with piece "<<winner->getPiece();
        }
        else {
            cout<<"game tied";
        }
    }
};

int main() {
//    Board* board = new Board(3);
//    board->printBoard();
//    XPiece x;
//    cout<<x<<"\n";
    auto ticTacToe = new TicTacToeGame();
    ticTacToe->startGame();

    return 0;
}

