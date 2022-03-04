#include "utils.h"

#include <string.h>
#include <stdlib.h>

extern char* user_home_directory;
extern char* current_working_directory;

char* cwd_copy;

void full_path_work(char* dest) {
    if (strlen(dest) == 0 || (strlen(dest) == 1 && dest[0] == '.')) return;
    else if (!strcmp(dest, "..")) {
        int cnt = 0;
        char *last = NULL, *l_last = NULL;
        for (char* i = cwd_copy; *i != '\0'; ++i)
            if (*i == '/') { ++cnt; l_last = last; last = i; }
        if (cnt < 2) return;
        *l_last = '\0';
        return;
    }
    else if (strlen(dest) >= 2 && dest[0] == '~' && dest[1] == '/') {
        strcpy(cwd_copy, user_home_directory);
        if (cwd_copy[strlen(cwd_copy) - 1] != '/') {
            int len = strlen(cwd_copy);
            cwd_copy[len] = '/';
            cwd_copy[len + 1] = '\0';
        }
        full_path_work(dest + 2);
    }
    else if (strlen(dest) >= 2 && dest[0] == '.' && dest[1] == '/')
        full_path_work(dest + 2);
    else if (strlen(dest) >= 3 && dest[0] == '.' && dest[1] == '.' && dest[2] == '/') {
        int cnt = 0;
        char *last = NULL, *l_last = NULL;
        for (char* i = cwd_copy; *i != '\0'; ++i)
            if (*i == '/') { ++cnt; l_last = last; last = i;  }
        if (cnt < 2) return;
        *l_last = '\0';
        if (cwd_copy[strlen(cwd_copy) - 1] != '/') {
            int len = strlen(cwd_copy);
            cwd_copy[len] = '/';
            cwd_copy[len + 1] = '\0';
        }
        full_path_work(dest + 3);
    }
    else {
        int len = strlen(cwd_copy);
        for (int i = 0; dest[i] != '\0'; ++i) {
            if (dest[i] == '/') {
                if (cwd_copy[strlen(cwd_copy) - 1] != '/') {
                    int l = strlen(cwd_copy);
                    cwd_copy[l] = '/';
                    cwd_copy[l + 1] = '\0';
                }
                full_path_work(dest + i + 1);
                break;
            }
            cwd_copy[len++] = dest[i];
        }
        cwd_copy[len] = '\0';
    }
}

void full_path(char* dest) {
    if (dest[0] == '/') return;
    cwd_copy = (char*) calloc(strlen(dest) + strlen(current_working_directory) + 5,
                              sizeof(char));
    strcpy(cwd_copy, current_working_directory);
    if (cwd_copy[strlen(cwd_copy) - 1] != '/') {
        int len = strlen(cwd_copy);
        cwd_copy[len] = '/';
        cwd_copy[len + 1] = '\0';
    }
    full_path_work(dest);
    strcpy(dest, cwd_copy);
    free(cwd_copy);
    if (strlen(dest) != 1 && dest[strlen(dest) - 1] == '/') dest[strlen(dest) - 1] = '\0';
}