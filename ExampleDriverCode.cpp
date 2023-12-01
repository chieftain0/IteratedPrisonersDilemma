#include <iostream>
#include "IPD.h"
using namespace std;

int main()
{
    int N = 0;
    Player p1, p2;
    int strategy1 = 0, strategy2 = 0;
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
        }
    }
    cout << endl;

    cout << "Detective, how many iterations would you like to run? ";
    cin >> N;
    cout << endl;

    p1.updateStrategy(strategy1);
    p2.updateStrategy(strategy2);
    Game g(N);
    g.addPlayer(&p1);
    g.addPlayer(&p2);
    g.play();
    g.reportResults();
    g.removePlayer(p1.getPlayerID());
    g.removePlayer(p2.getPlayerID());

    // Nasty bit of code
    // system("pause");

    return 0;
}
