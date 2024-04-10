#include <utils.h>
#include <chess-engine.hpp>
#include <string>
#include <filesystem>

std::string chess::get_path_to_res(std::string file_name) {
    char path[1024];
    _get_resource_dir(path);
    std::filesystem::path res_path(path);
    res_path /= file_name;
    return res_path.string();
}