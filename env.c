#include "minshell.h"

int update_var(char *var, t_list *g_env) {
    size_t len;

    len = (size_t)ft_strchr(var, '=') - (size_t)var;
    while (g_env)
    {
        if(!ft_strncmp((char *)g_env->content, var, len + 1)) 
        {
            free(g_env->content);
            g_env->content = strdup(var);
            return 1;
        }
       g_env = g_env->next;
    }
    return 0;
}

char** set_var(char **cmd, t_list *g_env, t_list **l_var) {
    int i;
    // int pos;
    char **newcmd;

    i = 0;
    while(ft_strchr(cmd[i], '=')){
        if (ft_strchr(cmd[i], '=') == cmd[i])
            break;
        if(!update_var(cmd[i], g_env))
            if(!update_var(cmd[i], *l_var))
                ft_lstadd_back(l_var, ft_lstnew((void *)ft_strdup(cmd[i])));
        i++;
    }
    newcmd = ft_copyarr(&cmd[i]);
    ft_freearray((void**)cmd);
    return newcmd;
}

// void export_var() {

// }

void unset_var(char **cmd, t_list **g_env, t_list **l_var) {
    int i;
    int len;
    // int flag;
    t_list *g_point;
    t_list *l_point;
    t_list *prev;

    i = 0;
    while(cmd[i]) {
        len = ft_strlen(cmd[i]);
        g_point = *g_env;
        while (g_point)
        {
            if (strncmp(g_point->content, cmd[i], len) == 0 && ((char*)g_point->content)[len] == '=') {
                if (g_point == *g_env)
                    *g_env = (*g_env)->next;
                else 
                    prev->next = g_point->next;
                free(g_point->content);
                free(g_point);
                break;
            }
            prev = g_point;
            g_point = g_point->next;
        }
        l_point = *l_var;
        while (l_point)
        {
            if (strncmp(l_point->content, cmd[i], len) == 0 && ((char*)l_point->content)[len] == '=') {
                if (l_point == *l_var)
                    *l_var = (*l_var)->next;
                else 
                    prev->next = l_point->next;
                free(l_point->content);
                free(l_point);
                break;
            }
            prev = l_point;
            l_point = l_point->next;
        }
        i++;
    }
}