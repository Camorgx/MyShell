#include "built_in.hpp"

#include <cstdio>
#include <readline/history.h>

void history() {
    HIST_ENTRY** hist_list = history_list();
    for (int i = 0; hist_list[i]; ++i)
        std::printf("%6d %s\n", i + 1, hist_list[i]->line);
}
