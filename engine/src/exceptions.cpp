#include <iostream>

using namespace std;


class IteratorException : public exception{
public:
    IteratorException(const string& message){
        cout << message << endl;
    }
};