#include <string.h>
#include <libgen.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#define PATH_SEPARATOR "\\"
#elif __linux__
#include <unistd.h>
#define PATH_SEPARATOR "/"
#endif

void _get_resource_path(char* buffer) {
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
        strncpy(buffer, "aboba", 1024);
    }
}