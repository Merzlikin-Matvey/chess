#pragma once
#include "ai.hpp"
#include "board.hpp"


namespace chess::uci {
    enum UCI_LOG_TYPE {
        DEBUG = 0,
        INPUT = 1,
        OUTPUT = 2,
    };


    struct PositionCommandArgs {
        std::string type;
        std::string fen_string;
        std::vector<std::string> moves_string;
    };

    class UCI {
    public:
        UCI();
        void start_handle();

    private:
        std::string logs_path;
        Board board_;
        engine::AI ai_;

        std::istream *input_stream_;
        std::ostream *output_stream_;

        void command_uci(std::string line);
        void command_isready(std::string line);
        void command_position(std::string line);
        void command_go(std::string line);

        void send(std::string message) const;
        void add_log(std::string message, UCI_LOG_TYPE type = DEBUG) const;

        void clear_logs() const;
    };
}
