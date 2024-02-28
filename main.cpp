#include <iostream>

#include "engine/src/board.cpp"
#include "engine/src/figure.cpp"

using namespace std;

int main() {
    Board board;
    board.import_json("C:\\Users\\merzl\\CLionProjects\\chess8\\saves\\data.json");
    board.print();
}
