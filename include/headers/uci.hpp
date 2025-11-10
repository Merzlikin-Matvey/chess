#pragma once
#include "ai.hpp"
#include "board.hpp"


namespace chess::uci {
    class UCI {
    public:
        UCI();
        void start_handle();


    private:
        std::string logs_path;
        Board board_;
        engine::AI ai_;

        void command_uci();
        void command_isready();
        void command_position();
        void command_go();


        void add_log(std::string log)const;
    };
}
