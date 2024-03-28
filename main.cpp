#include <iostream>
#include "src/chess-engine.h"

using namespace std;

int main() {
    chessBoard b;
    b.load_default_positions();
    b.print();
}