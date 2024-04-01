#include <iostream>
#include <chess-engine/chess-engine.h>

using namespace std;
using namespace chess;

int main() {
    Board b;
    b.load_default_positions();
    b.print();
}