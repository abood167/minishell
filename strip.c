#include "minshell.h"

char** strip_copy(char **cmd, int len){
    char **strip;
    int i;
    int j;
    
    i = 0;
    j = 0;
    strip = (char **)malloc(sizeof(char *) * (len + 1));
    while (i < len) {
        if (ft_strncmp(cmd[j], ">>", 2) == 0) {
            j += 1 + 1 * (cmd[j][2] == '\0');
            continue;
        }
        else if (ft_strncmp(cmd[j], ">", 1) == 0) {
            j += 1 + 1 * (cmd[j][2] == '\0');
            continue;
        }
        else if (ft_strncmp(cmd[j], "<<", 2) == 0) {
            j += 1 + 1 * (cmd[j][2] == '\0');
            continue;
        }
        else if (ft_strncmp(cmd[j], "<", 1) == 0) {
            j += 1 + 1 * (cmd[j][2] == '\0');
            continue;
        }
        strip[i] = ft_strdup(cmd[j]);
        i++;
        j++;
    }
    ft_freearray((void **)cmd);
    strip[i] = NULL;
    return (strip);
}

char** strip_redirect(char **cmd, t_pipex *pipex) {
    int arr_len;
    int cmd_pos;

    arr_len = 0;
    for (size_t i = 0; cmd[i]; i++)
    {
        cmd_pos = 0;
        if (ft_strncmp(cmd[i], ">>", 2) == 0) {
            if (cmd[i][2] != '\0') 
                cmd_pos = 2;
            else
                i++;
            if (!cmd[i])
            { 
                printf("minishell: syntax error near unexpected token `newline'\n");
                return NULL;
            }
            // Handle closing if out is not -1
            pipex->out[1] = open(&cmd[i][cmd_pos], O_CREAT | O_WRONLY | O_APPEND, 0644); //handle error
            continue;
        }
        else if (ft_strncmp(cmd[i], ">", 1) == 0) {
            if (cmd[i][1] != '\0') {
                cmd_pos = 1;
            }
            else
                i++;
            if (!cmd[i])
            { 
                printf("minishell: syntax error near unexpected token `newline'\n"); //TODO handle more unexpected token
                return NULL;
            }                
            // Handle closing if out is not -1
            pipex->out[1] = open(&cmd[i][cmd_pos], O_CREAT | O_WRONLY | O_TRUNC, 0644); //handle error
            continue;
        }
        else if (ft_strncmp(cmd[i], "<<", 2) == 0) {
            if (cmd[i][2] != '\0') 
                cmd_pos = 2;
            else
                i++;
            if (!cmd[i])
            { 
                printf("minishell: syntax error near unexpected token `newline'\n");
                return NULL;
            }
            // Handle closing if in/out is not -1
            here_doc(pipex, &cmd[i][cmd_pos]);  //handle error
            continue;
        }
        else if (ft_strncmp(cmd[i], "<", 1) == 0) {
            if (cmd[i][1] != '\0') {
                cmd_pos = 1;
            }
            else
                i++;
            if (!cmd[i])
            { 
                printf("minishell: syntax error near unexpected token `newline'\n");
                return NULL;
            }                
            // Handle closing if in is not -1
            pipex->in = open(&cmd[i][cmd_pos], O_RDONLY); // handle error
            if (pipex->in < 0) {
                write(2, "minishell: ", 7);
		        perror(&cmd[i][cmd_pos]);
                return NULL;
            }
            continue;
        }
        arr_len++;
    }
    return(strip_copy(cmd, arr_len));
} 