#include <iostream>
#include <chess-engine/chess-engine.hpp>

int main() {
    char path[1024];
    _get_resource_path(path);
    std::cout << "The path is: " << path << std::endl;
    return 0;
}