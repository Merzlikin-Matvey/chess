#include <string.h>
#include <libgen.h>
#include <unistd.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#define PATH_SEPARATOR "\\"
#elif __linux__
#include <unistd.h>
#define PATH_SEPARATOR "/"
#endif

void _get_resource_dir(char* buffer) {
    char exe_path[1024];
#ifdef _WIN32
    GetModuleFileName(NULL, exe_path, 1024);
    strncpy(buffer, dirname(exe_path), 1024);
#elif __linux__
    readlink("/proc/self/exe", exe_path, 1024);
    strncpy(buffer, dirname(exe_path), 1024);
#endif
    strcat(buffer, PATH_SEPARATOR "res");

    if (access(buffer, F_OK) != 0) {
        char* env_path = getenv("CHESS_ENGINE_PATH");
        if (env_path != NULL) {
            strncat(env_path, PATH_SEPARATOR "res", 1024);
            strncpy(buffer, env_path, 1024);
        } else {
            strncpy(buffer, "", 1024);
        }
        if (env_path != NULL) {
            strncpy(buffer, env_path, 1024);
        } else {
            strncpy(buffer, "", 1024);
        }
    }
}