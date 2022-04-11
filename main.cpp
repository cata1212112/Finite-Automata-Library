#include <iostream>
#include "DFA.h"
#include "NFA.h"

using namespace std;

int main() {
    DFA test;
    cin >> test;
    DFA minimizat = test.Minimization();
    minimizat.stari_bune();
    cout << minimizat;
    return 0;
}
