#include "global.h"

int command_count = 0;

command commands[4];

// not with last '/'
char home_directory[MAX_PATH_LEN];

char displayed_directory[MAX_PATH_LEN];

char user_string[MAX_LEN];
