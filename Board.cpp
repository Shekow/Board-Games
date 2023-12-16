#include <iostream>
#include "../include/BoardGame_Classes.hpp"
using namespace std;

bool C_Board::inBounds(int x, int y) const
{
    return (x >= 0 && x < rows && y >= 0 && y < cols);
}

size_t C_Board::numOfSeq(char symbol) const
{ // R, D, DR, DL
    int dx[] = {0, 0, 1, -1, 1, -1, 1, -1};
    int dy[] = {1, -1, 0, 0, 1, -1, -1, 1};
    size_t total{};
    for (int i{}; i < rows; i++)
    {
        for (int j{}; j < cols; j++)
        {
            if (board[i][j] != symbol) continue;
            for (int d{}; d < 8; d += 2)
            {
                size_t ctr{};
                for (int x{i}, y{j}; inBounds(x, y) && board[x][y] == board[i][j]; x += dx[d], y += dy[d]) ctr++;
                if (ctr >= minSeqLen) total++;
            }
        }
    }
    return total;
}

C_Board::C_Board(size_t rows, size_t cols, size_t minSeqLen, size_t maxMoves): minSeqLen(minSeqLen), maxMoves(maxMoves)
{
    this->rows = rows, this->cols = cols;
    board = new char*[rows];
    for (size_t i{}; i < rows; i++)
    {
        board[i] = new char[cols]{};
    }
}
size_t C_Board::numOfRows() const
{
    return rows;
}
size_t C_Board::numOfColumns() const
{
    return cols;
}
vector<vector<char>> C_Board::getBoard() const
{
    vector<vector<char>> boardVector(rows, vector<char>(cols));
    for (size_t i{}; i < rows; i++)
    {
        for (size_t j{}; j < cols; j++)
        {
            boardVector[i][j] = board[i][j];
        }
    }
    return boardVector;
}

vector<pair<size_t, size_t>> C_Board::getMoves() const
{
    vector<pair<size_t, size_t>> moves;
    if (gameIsOver()) return moves;
    for (size_t i{}; i < rows; i++)
    {
        for (size_t j{}; j < cols; j++)
        {
            if (!board[i][j])
            {
                moves.push_back({i, j});
            }
        }
    }
    return moves;
}
void C_Board::resetBoard()
{
    for (size_t i{}; i < rows; i++)
    {
        for (size_t j{}; j < cols; j++)
        {
            board[i][j] = 0;
        }
    }
    moves = 0;
}
bool C_Board::updateBoard(size_t x, size_t y, char symbol)
{
    if (gameIsOver()) return false;
    if (!inBounds(x, y) || board[x][y]) return false;
    board[x][y] = toupper(symbol);
    moves++;
    moveList.push_back({x, y});
    return true;
}
bool C_Board::undoLastMove()
{
    if (moveList.empty()) return false;
    board[moveList.back().first][moveList.back().second] = 0;
    moveList.pop_back();
    moves--;
    return true;
}

bool C_Board::isWinner() const
{
    return numOfSeq('X') != numOfSeq('O');
}
char C_Board::getWinner() const
{
    if (!isWinner()) return 0;
    return (numOfSeq('X') > numOfSeq('O') ? 'X' : 'O');
}
bool C_Board::isDraw() const
{
    return moves == maxMoves && !isWinner();
}
bool C_Board::gameIsOver() const
{
    return isWinner() || isDraw();
}
C_Board::~C_Board()
{
    delete [] board;
}



X_O_Board::X_O_Board(): C_Board(3, 3, 3, 9)
{

}

void X_O_Board::displayBoard() const
{
    for (int i{}; i < rows; i++)
    {
        for (int j{}; j < cols; j++)
        {
            char c = board[i][j];
            cout << (board[i][j] ? board[i][j] : '.');
        }
        cout << endl;
    }
}

Pyramidic_X_O_Board::Pyramidic_X_O_Board(): C_Board(3, 5, 3, 9)
{

}
vector<vector<char>> Pyramidic_X_O_Board::getBoard() const
{
    vector<vector<char>> boardVector;
    for (size_t i{}; i < rows; i++)
    {
        vector<char> tmpVector;
        int cor = (cols - (2 * i + 1)) / 2;
        for (size_t j{}; j + 2 * cor < cols; j++)
        {
            tmpVector.push_back(board[i][j + cor]);
        }
        boardVector.push_back(tmpVector);
    }
    return boardVector;
}

vector<pair<size_t, size_t>> Pyramidic_X_O_Board::getMoves() const
{
    vector<pair<size_t, size_t>> moves;
    if (gameIsOver()) return moves;
    for (size_t i{}; i < rows; i++)
    {
        int cor = (cols - (2 * i + 1)) / 2;
        for (size_t j{}; j + 2 * cor < cols; j++)
        {
            if (!board[i][j + cor]) moves.push_back({i, j});
        }
    }
    return moves;
}


bool Pyramidic_X_O_Board::updateBoard(size_t x, size_t y, char symbol)
{
    int cor = (cols - (2 * x + 1)) / 2;
    return y + cor * 2 < cols && C_Board::updateBoard(x, y + cor, symbol);
}

void Pyramidic_X_O_Board::displayBoard() const
{
    for (int i{}; i < rows; i++)
    {
        int cor = (cols - (2 * i + 1)) / 2;
        for (int j{}; j < cor; j++)
        {
            cout << ' ';
        }
        for (int j{}; j < 2 * i + 1; j++)
        {
            cout << (board[i][j + cor] ? board[i][j + cor] : '.');
        }
        cout << endl;
    }
}


Connect_4_Board::Connect_4_Board(): C_Board(6, 7, 4, 6 * 7)
{

}

vector<pair<size_t, size_t>> Connect_4_Board::getMoves() const
{
    vector<pair<size_t, size_t>> moves;
    if (gameIsOver()) return moves;
    for (size_t j{}; j < cols; j++)
    {
        if (!board[0][j])
        {
            moves.push_back({0, j});
        }
    }
    return moves;
}

bool Connect_4_Board::updateBoard(size_t x, size_t y, char symbol)
{
    if (!inBounds(0, y) || board[0][y]) return false;
    int nx = rows - 1;
    for (;nx >= 0 && board[nx][y]; nx--);
    return C_Board::updateBoard(nx, y, symbol);
}
void Connect_4_Board::displayBoard() const
{
    for (int i{}; i < rows; i++)
    {
        for (int j{}; j < cols; j++)
        {
            cout << (board[i][j] ? board[i][j] : '.');
        }
        cout << endl;
    }
}

FiveByFive_X_O_Board::FiveByFive_X_O_Board(): C_Board(5, 5, 3, 24)
{

}
void FiveByFive_X_O_Board::displayBoard() const
{
    for (int i{}; i < rows; i++)
    {
        for (int j{}; j < cols; j++)
        {
            cout << (board[i][j] ? board[i][j] : '.');
        }
        cout << endl;
    }
}

bool FiveByFive_X_O_Board::isWinner() const
{
    gameIsOver() && C_Board::isWinner();
}
bool FiveByFive_X_O_Board::gameIsOver() const
{
    return moves == maxMoves;
}