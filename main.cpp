#include <iostream>
#include "src/chess-engine.h"

using namespace std;

int main() {
    Board b;
    b.load_default_positions();
    for (auto move : b.available_moves()){
        cout << move << endl;
    }
}