#include <cstdlib>
#include <iostream>

using namespace std;

int main() {
    const char* path = getenv("CHESS_ENGINE_RESOURCE_PATH");
    if (path) {
        cout << "CHESS_ENGINE_RESOURCE_PATH: " << path << endl;
    } else {
        cout << "CHESS_ENGINE_RESOURCE_PATH is not set" << endl;
    }
}