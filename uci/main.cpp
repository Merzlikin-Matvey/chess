#include "chess-lib.hpp"


int main() {
    std::cout << "START GAME" << std::endl;
    auto uci = chess::uci::UCI();
    uci.start_handle();
}
