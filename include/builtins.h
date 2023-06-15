#pragma once

#include "global.h"

// not with last '/'
extern char home_directory[MAX_PATH_LEN];

extern char displayed_directory[MAX_PATH_LEN];

extern void pwd(void);

extern void cd(char* path);
