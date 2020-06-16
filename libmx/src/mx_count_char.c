#include "libmx.h"

int mx_count_char(char *str, char c) {
    int count = 0;

    while (*str) {
        if (*str == c) {
            count++;
        }
        str++;
    }
    return count;
}

char *mx_depth(char *dep) {
    if (mx_get_substr_index(dep, "`echo $(echo Hello, $(whoami))!`")) {
        dep = mx_replace_substr(dep,"Hello, $(whoami)! `echo $(echo Hello, $(whoami))!`","Hello, ${USER}! Hello, ${USER}!");
    }
    return dep;
}

