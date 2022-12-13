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

char** set_var(char **cmd, t_list *g_env, t_list **l_var, int ac) {
    int i;
    int pos;
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
    if (ac == 1)
        ft_freearray((void**)cmd);
    return newcmd;
}

// void export_var() {

// }

// void unset_var() {

// }