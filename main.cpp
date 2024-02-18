#include <iostream>

#include "engine/src/board.cpp"
#include "engine/src/figure.cpp"

using namespace std;

int main() {
    Board board;
    board.encode_from_json("C:\\Users\\User\\CLionProjects\\chess1\\saves\\data.json", board);
    board.print();
    board.info();
}