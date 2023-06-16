#include "builtins.h"
#include "utils.h"

#include <stdio.h>
#include <readline/history.h>
#include <string.h>
#include <unistd.h>

void pwd(void) {
    char path_name[MAX_PATH_LEN];
    if (getcwd(path_name, sizeof(path_name)))
        puts(path_name);
}

void cd(char* path) {
    char dest[MAX_PATH_LEN];
    strcpy(dest, path ? path : home_directory);
    if (dest[0] == '~') {
        char tmp[MAX_PATH_LEN];
        strcpy(tmp, dest);
        strcpy(dest, home_directory);
        strcat(dest, tmp + 1);
    }
    if (chdir(dest)) {
        perror("cd");
        return;
    }
    update_display_dir();   
}

void history(void) {
    HIST_ENTRY** hist_list = history_list();
    for (int i = 0; hist_list[i]; ++i)
        printf("%6d %s\n", i + 1, hist_list[i]->line);
}
