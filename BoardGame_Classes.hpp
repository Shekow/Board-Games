#ifndef _BoardGame_CLASSES_H
#define _BoardGame_CLASSES_H
#include <iostream>
#include <bits/stdc++.h>
#include <random>
#include <time.h>
#include <iomanip>
#include <tuple>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class Board 
{
    protected:
        size_t rows, cols, moves{};
        char **board;
        vector<pair<size_t, size_t>> moveList;
        virtual bool inBounds(int x, int y) const = 0;
    public:
        virtual size_t numOfRows() const = 0;
        virtual size_t numOfColumns() const = 0;
        virtual vector<vector<char>> getBoard() const = 0;
        virtual vector<pair<size_t, size_t>> getMoves() const = 0;
        virtual void resetBoard() = 0;
        virtual bool updateBoard(size_t x, size_t y, char symbol) = 0;
        virtual bool undoLastMove() = 0;
        virtual bool isWinner() const = 0;
        virtual char getWinner() const = 0;
        virtual bool isDraw() const = 0;
        virtual void displayBoard() const = 0;
        virtual bool gameIsOver() const = 0;
};


class C_Board: public Board
{
    protected:
        size_t minSeqLen, maxMoves;
        virtual bool inBounds(int x, int y) const;
        virtual size_t numOfSeq(char symbol) const;
    public:
        C_Board(size_t rows, size_t cols, size_t minSeqLen, size_t maxMoves);
        virtual size_t numOfRows() const;
        virtual size_t numOfColumns() const;
        virtual vector<vector<char>> getBoard() const;
        virtual vector<pair<size_t, size_t>> getMoves() const;
        virtual void resetBoard();
        virtual bool updateBoard(size_t x, size_t y, char symbol);
        virtual bool undoLastMove();
        virtual bool isWinner() const;
        virtual char getWinner() const;
        virtual bool isDraw() const;
        virtual void displayBoard() const;
        virtual bool gameIsOver() const;
        virtual ~C_Board();
};


class X_O_Board: public C_Board
{
    public:
        X_O_Board();
};

class Pyramidic_X_O_Board: public C_Board
{
    public:
        Pyramidic_X_O_Board();
        virtual vector<vector<char>> getBoard() const;
        virtual vector<pair<size_t, size_t>> getMoves() const;
        virtual bool updateBoard(size_t x, size_t y, char symbol);
        virtual void displayBoard() const;
};

class Connect_4_Board: public C_Board
{
    public:
        Connect_4_Board();
        virtual vector<pair<size_t, size_t>> getMoves() const;
        virtual bool updateBoard(size_t x, size_t y, char symbol);
};

class FiveByFive_X_O_Board: public C_Board
{
    public:
        FiveByFive_X_O_Board();
        virtual bool isWinner() const;
        virtual bool gameIsOver() const;
};

class Player 
{
    protected:
        string name;
        char symbol;
    public:
        Player (char symbol, string name = "Human");
        virtual void getMove(size_t& x, size_t& y);
        string getName();
        char getSymbol();
};

class RandomPlayer: public Player 
{
    protected:
        Board *board;
    public:
        RandomPlayer(char symbol, Board *board);
        virtual void getMove(size_t &x, size_t &y);
};


class AI_Player: public Player
{
    protected:
        Board *board;
        tuple<double, size_t, size_t> evaluatePos(char cuSymbol, int dep = 5);
    public:
        AI_Player(char symbol, Board *board);
        virtual void getMove(size_t &x, size_t &y);
};

class GameManager
{
    Board* boardPtr;
    Player* playerPtr[2];
    public:
        GameManager(Board* bPtr, Player* pPtr[2]);
        void run();
};

#endif
