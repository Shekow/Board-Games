#include <iostream>
#include "Board.cpp"
#include "Player.cpp"
#include "GameManager.cpp"

using namespace std;

int main() 
{
    srand(time(NULL));
    Board *board;
    Player *player[2];
    int op;
    cout << "====================Board Games===================" << endl;
    cout << "1-Classic Tic Tac Toe" << endl;
    cout << "2-Pyramidic Tic Tac Toe" << endl;
    cout << "3-Connect Four" << endl;
    cout << "4-5 x 5 Tic Tac Toe" << endl;
    cout << "==================================================" << endl;
    cout << "Response: ";
    cin >> op;
    switch (op)
    {
        case 1:
        {
            board = new X_O_Board();
            break;
        }
        case 2:
        {
            board = new Pyramidic_X_O_Board();
            break;
        }
        case 3:
        {
            board = new Connect_4_Board();
            break;
        }
        case 4:
        {
            board = new FiveByFive_X_O_Board();
            break;
        }
        default:
        {
            return 0;
        }
    }
    for (int i: {0, 1})
    {
        char c = (i == 0 ? 'X' : 'O');
        cout << "====================" << (i == 0 ? "First" : "Second") << " Player===================" << endl;
        cout << "1-Human Player" << endl;
        cout << "2-Random Computer Player" << endl;
        cout << "3-AI" << endl;
        cout << "===================================================" << endl;
        cout << "Response: ";
        cin >> op;
        switch (op) 
        {
            case 1:
            {
                cout << "Name: ";
                string name;
                cin.ignore();
                getline(cin, name);
                player[i] = new Player(c, name);
                break;
            }
            case 2:
            {
                player[i] = new RandomPlayer(c, board);
                break;
            }
            case 3:
            {
                player[i] = new AI_Player(c, board);
                break;
            }
            default:
            {
                return 0;
            }
        }
    }
    GameManager gm(board, player);
    gm.run();
}
