#include <iostream>
using namespace std;

//All classes and functions are written to be idiot-proof
//and return the check values to the caller
class Strategy
{
private:
    int currentStrategy;
    // 1 - Random
    // 2 - Always Cooperate
    // 3 - Always Defect
    // 4 - Tit-for-Tat

public:
    // Constructors and Destructors
    Strategy()
    {
        currentStrategy = 0;
    }
    Strategy(int initialStrategy)
    {
        currentStrategy = initialStrategy;
    }
    ~Strategy()
    {
    }
    // Methods
    int setStrategy(int newStrategy)
    {
        currentStrategy = newStrategy;
        return currentStrategy;
    }
    char cooperateOrDefect(char opponentLastMove)
    {
        if (currentStrategy == 1)
        {
            return (rand() % 2 == 0) ? 'C' : 'D';
        }
        else if (currentStrategy == 2)
        {
            return 'C';
        }
        else if (currentStrategy == 3)
        {
            return 'D';
        }
        else if (currentStrategy == 4)
        {
            if (opponentLastMove == ' ')
            {
                if (rand() % 2 == 0)
                {
                    return 'C';
                }
                else
                {
                    return 'D';
                }
            }
            return opponentLastMove;
        }
        else
        {
            return 0;
        }
    }
};

class Player
{
    static int counter;

private:
    int ID;
    int score;
    char *moves;
    int numMoves;
    Strategy strategy; // make pointer to strategy

public:
    // Constructors and Destructors
    Player()
    {
        ID = ++counter;
        score = 0;
        moves = new char[1];
        numMoves = 0;
        strategy = Strategy();
    }
    Player(int InitialStrategyNum)
    {
        ID = ++counter;
        score = 0;
        moves = new char[1];
        numMoves = 0;
        strategy = Strategy(InitialStrategyNum);
    }
    ~Player()
    {
        delete[] moves;
    }

    // Methods
    char makeMove(char opponentLastMove)
    {
        char move = strategy.cooperateOrDefect(opponentLastMove);

        char *newMoves = new char[numMoves + 1];
        for (int i = 0; i < numMoves; ++i)
        {
            newMoves[i] = moves[i];
        }
        newMoves[numMoves] = move;

        delete[] moves;
        moves = newMoves;

        numMoves++;
        return move;
    }

    void printMoves()
    {
        cout << "Player " << ID << ": ";
        for (int i = 0; i < numMoves; ++i)
        {
            cout << moves[i] << " ";
        }
        cout << endl;
    }

    int setLastMove(char lastMove)
    {
        if (numMoves > 0)
        {
            moves[numMoves - 1] = lastMove;
            return 0;
        }
        return -1;
    }

    int updateStrategy(int newStrategy)
    {
        if (strategy.setStrategy(newStrategy) == newStrategy)
        {
            return 0;
        }
        return -1;
    }

    // Setters and Getters
    int getPlayerID()
    {
        return ID;
    }

    int getScore()
    {
        return score;
    }

    int getNumMoves()
    {
        return numMoves;
    }

    char *getMoves()
    {
        return moves;
    }

    int updateScore(int points)
    {
        score += points;
        return score;
    }
};

class Game
{
private:
    Player *players[2];
    int MaxNumMoves;

public:
    // Constructors and Destructors
    Game(int N)
    {
        players[0] = nullptr;
        players[1] = nullptr;
        MaxNumMoves = N;
    }
    ~Game()
    {
        players[0] = nullptr;
        players[1] = nullptr;
    }
    // Methods
    int addPlayer(Player *newPlayer)
    {
        if (players[0] == nullptr)
        {
            players[0] = newPlayer;
            return 0;
        }
        else if (players[1] == nullptr)
        {
            players[1] = newPlayer;
            return 1;
        }
        else
        {
            return -1;
        }
    }
    int removePlayer(int ID)
    {
        if (players[0] != nullptr && players[0]->getPlayerID() == ID)
        {
            players[0] = nullptr;
            return 0;
        }
        else if (players[1] != nullptr && players[1]->getPlayerID() == ID)
        {
            players[1] = nullptr;
            return 0;
        }
        else
        {
            return -1;
        }
    }

    int play()
    {
        if (players[0] == nullptr || players[1] == nullptr)
        {
            return -1;
        }

        for (int i = 0; i < MaxNumMoves; ++i)
        {
            // Get the move for player 1
            char player1Move;
            if (players[1]->getNumMoves() > 0)
            {
                char lastMove = players[1]->getMoves()[players[1]->getNumMoves() - 1];
                player1Move = players[0]->makeMove(lastMove);
            }
            else
            {
                player1Move = players[0]->makeMove(' ');
            }

            // Get the move for player 2
            char player2Move;
            if (players[0]->getNumMoves() > 0)
            {
                char lastMove = players[0]->getMoves()[players[0]->getNumMoves() - 1];
                player2Move = players[1]->makeMove(lastMove);
            }
            else
            {
                player2Move = players[1]->makeMove(' ');
            }

            // Update the scores based on the moves
            if (player1Move == 'C' && player2Move == 'C')
            {
                players[0]->updateScore(3);
                players[1]->updateScore(3);
            }
            else if (player1Move == 'C' && player2Move == 'D')
            {
                players[0]->updateScore(0);
                players[1]->updateScore(5);
            }
            else if (player1Move == 'D' && player2Move == 'C')
            {
                players[0]->updateScore(5);
                players[1]->updateScore(0);
            }
            else if (player1Move == 'D' && player2Move == 'D')
            {
                players[0]->updateScore(1);
                players[1]->updateScore(1);
            }
        }
        return 0;
    }

    void reportResults()
    {
        cout << "Game Results:" << endl;
        for (int i = 0; i < 2; ++i)
        {
            cout << "Player " << players[i]->getPlayerID() << " - Score: " << players[i]->getScore() << endl;
            players[i]->printMoves();
        }
    }
};

int Player::counter = 0;
