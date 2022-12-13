#include "minshell.h"

void printlist(char **list) {
    while(*list) {
        printf("%s\n", *list);
        list++;
    }
}

t_list* ft_arrtolst(char **arr) {
    t_list *list;
    
    list = NULL;
    while(*arr) {
        ft_lstadd_back(&list, ft_lstnew((void *)ft_strdup(*arr)));
        arr++;
    }
    return list;
}

char** ft_lsttoarr(t_list *list) {
    char    **arr;
    int     i;

    arr = (char **)malloc((char **)malloc(sizeof(char *) * (ft_lstsize(list) + 1)));
    i = 0;
    while (list)
    {
        arr[i++] = ft_strdup((char *)list->content);
        list = list->next;
    }
    arr[i] = NULL;
}