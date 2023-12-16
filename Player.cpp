#include"../include/BoardGame_Classes.hpp"
using namespace std;

Player::Player(char symbol, string name): symbol(toupper(symbol)), name(name)
{

}
void Player::getMove(size_t &x, size_t &y)
{
    cout << name << ",  " << "please enter your move: ";
    cin >> x >> y;
}
string Player::getName()
{
    return name;
}
char Player::getSymbol()
{
    return symbol;
}

RandomPlayer::RandomPlayer(char symbol, Board *board): Player(symbol, "Random Player"), board(board)
{

}
void RandomPlayer::getMove(size_t &x, size_t &y)
{
    if (board->gameIsOver()) return;
    vector<pair<size_t, size_t>> moves = board->getMoves();
    size_t randomIndex = rand() % moves.size();
    x = moves[randomIndex].first, y = moves[randomIndex].second;
}

tuple<double, size_t, size_t> AI_Player::evaluatePos(char cuSymbol, int dep)
{
    double res = 10 * (cuSymbol == symbol ? -1 : 1), nextEva;
    size_t x{}, y{};
    char nextSymbol = (cuSymbol == 'X' ? 'O' : 'X');
    
    if (board->gameIsOver())
    {
        if (board->isWinner() && board->getWinner() != symbol) res = -1;
        else res = board->isWinner();
    }
    else if (!dep)
    {
        // Could be changed in the future
        res = 0;
    }
    else
    {    
        vector<pair<size_t, size_t>> moves = board->getMoves();
        for (auto &m: moves)
        {
            board->updateBoard(m.first, m.second, cuSymbol);
            nextEva = get<0>(evaluatePos(nextSymbol, dep - 1));
            if ((cuSymbol == symbol && res < nextEva) || (cuSymbol != symbol && res > nextEva))
            {
                res = nextEva, x = m.first, y = m.second;
            }
            board->undoLastMove();
            if ((cuSymbol == symbol && res == 1) || (cuSymbol != symbol && res == -1))
            {
                return {res, x, y};
            }
        }
        
    }
    return {res, x, y};
}
AI_Player::AI_Player(char symbol, Board *board): Player(symbol, "AI Player"), board(board)
{

}
void AI_Player::getMove(size_t &x, size_t &y)
{
    if (board->gameIsOver()) return;
    int depth{}, moves = board->getMoves().size(), pro{1}, lim = 1e6;
    double res;
    for (; pro < lim && moves; pro *= moves, depth++, moves--);
    if (pro > lim) depth--;
    tie(res, x, y) = evaluatePos(symbol, depth);
}