#include "board.h"

using namespace std;

class Board;

class Iterator {
public:
    string position;
    Board *board;

    explicit Iterator(string pos) : position(pos), board(nullptr) {}

    void print() {
        cout << position << endl;
    }

    void up() {
        if (position[1] == '8') {
            throw IteratorException("Maximum value of iterator - " + position);
        } else {
            position[1]++;
        }
    }

    void right() {
        if (position[0] == 'h') {
            throw IteratorException("Maximum value of iterator - " + position);
        } else {
            position[0]++;
        }
    }

    void down() {
        if (position[1] == '1') {
            throw IteratorException("Maximum value of iterator - " + position);
        } else {
            position[1]--;
        }
    }

    void left() {
        if (position[0] == 'a') {
            throw IteratorException("Maximum value of iterator - " + position);
        } else {
            position[0]--;
        }
    }
};

class Figure {
public:
    string name;
    Iterator it;

    Figure() : it("") {}
    Figure(Iterator iter) : it(iter) {}

    void print(){
        cout << name << ' ' << it.position << endl;
    }
};




class Board {
public:
    map<string, Figure> figures;

    Board() : figures() {
        for (char i = 'a'; i < 'i'; i++) {
            for (char j = '1'; j < '9'; j++) {
                figures.emplace(string(1, i) + j, Iterator(string(1, i) + j));

            }
        }
    }
};








