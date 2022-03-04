#include "utils.h"

#include <string.h>
#include <stdlib.h>

char** split(char* line) {
    int quote_cnt = 0;
    for (int i = 0; line[i] != '\0'; ++i)
        if (line[i] == '\"') ++quote_cnt;
    if (quote_cnt % 2) return NULL;
    int cnt = 0, cnt_p = 0;
    int in_quote = 0;
    int num = 8, num_p = 8;
    int pos[256];
    char** ans = (char**) calloc(num_p, sizeof(char*));
    ans[0] = (char*) calloc(num, sizeof(char));
    for (int i = 0; line[i] != '\0'; ++i) {
        if (line[i] == '\"') in_quote = !in_quote;
        else if (!in_quote && line[i] == ' ' && cnt) {
            if (cnt_p == num_p - 1) 
                ans = (char**) reallocarray(ans, num_p *= 2, sizeof(char*));
            ans[cnt_p][cnt] = '\0'; cnt = 0;
            ans[++cnt_p] = (char*) calloc(num = 8, sizeof(char));
        }
        else {
            if (cnt == num - 1) 
                ans[cnt_p] = (char*) reallocarray(ans[cnt_p], num *= 2, sizeof(char));
            ans[cnt_p][cnt++] = line[i];
        }     
    }
    ans[cnt_p][cnt] = '\0';
    ans[cnt_p + 1] = NULL;
    return ans;
}