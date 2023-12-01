#include <iostream>
#include <limits>
#include "IPD.h"
using namespace std;

// Despite of all of the functions being idiot-proof,
// main() still makes preliminary input checks
int main()
{
    int N = 0;
    Player p1, p2;
    int strategy1 = 0, strategy2 = 0;
    char choice;
    cout << "Hello Offenders" << endl;
    cout << "Let's play a game!" << endl;
    cout << endl;
    cout << "Your God-given right is to choose your strategy" << endl;
    cout << "1. Random" << endl;
    cout << "2. Always Cooperate" << endl;
    cout << "3. Always Defect" << endl;
    cout << "4. Tit-for-Tat" << endl;
    cout << endl;

    while (strategy1 < 1 || strategy1 > 4)
    {
        cout << "Player " << p1.getPlayerID() << " choose your strategy: ";
        cin >> strategy1;
        if (strategy1 < 1 || strategy1 > 4)
        {
            cout << "Invalid input" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    cout << endl;

    while (strategy2 < 1 || strategy2 > 4)
    {
        cout << "Player " << p2.getPlayerID() << " choose your strategy: ";
        cin >> strategy2;
        if (strategy2 < 1 || strategy2 > 4)
        {
            cout << "Invalid input" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    cout << endl;

    cout << "Detective, how many iterations would you like to run the game? " << endl;
    while (N < 1)
    {
        cout << "N = ";
        cin >> N;
        if (N < 1)
        {
            cout << "Invalid input" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    cout << endl;

    p1.updateStrategy(strategy1);
    p2.updateStrategy(strategy2);
    Game g(N);
    g.addPlayer(&p1);
    g.addPlayer(&p2);
    g.play();
    g.reportScores();

    cout << endl;
    cout << "Moves: " << endl;
    if (p1.getNumMoves() > 10 || p2.getNumMoves() > 10)
    {
        cout << endl;
        cout << "The number of moves is large" << endl;
        cout << "Would you like to see the moves? (y/n)" << endl;
        while (choice != 'y' && choice != 'n')
        {
            cout << "Choice: ";
            cin >> choice;
            if (choice == 'y')
            {
                p1.printMoves();
                p2.printMoves();
            }
            else if (choice == 'n')
            {
                cout << endl;
            }
            else
            {
                cout << "Invalid input" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    else
    {
        p1.printMoves();
        p2.printMoves();
    }

    g.removePlayer(p1.getPlayerID());
    g.removePlayer(p2.getPlayerID());

    cout << "Thank you for playing!" << endl;

    // Nasty bit of code
    system("pause");

    return 0;
}
