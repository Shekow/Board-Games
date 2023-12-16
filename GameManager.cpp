#include <iostream>
#include"../include/BoardGame_Classes.hpp"
using namespace std;

GameManager::GameManager(Board* bPtr, Player* pPtr[2])
{
    boardPtr = bPtr, playerPtr[0] = pPtr[0], playerPtr[1] = pPtr[1];
}

void GameManager::run()
{
    size_t x, y, idx{};
    boardPtr->displayBoard();
    cout << "==========================\n";
    while (!boardPtr->gameIsOver())
    {
        do
        {
            playerPtr[idx]->getMove(x, y);
        } while (!boardPtr->updateBoard(x, y, playerPtr[idx]->getSymbol()));
        boardPtr->displayBoard();
        cout << "==========================\n";
        idx = (idx + 1) % 2;
    }
    if (boardPtr->isWinner())
    {
        size_t idx = (boardPtr->getWinner() == playerPtr[0]->getSymbol() ? 0 : 1);
        cout << playerPtr[idx]->getName() << " (" << playerPtr[idx]->getSymbol() << ")" << " wins!";
    }
    else cout << "Draw!";
    cout << endl;
}
