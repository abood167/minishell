#include "minshell.h"

void printlist(char **list) {
    while(*list) {
        printf("%s\n", *list);
        list++;
    }
}