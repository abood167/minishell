#include "minshell.h"

char	*pipe_shell(char *line, t_pipex *pipex)
{
	int i;
    char **pipe_line;
    char *cur_line;

	pipe_line = ft_split(line, '|');
    i = 0;
    while(pipe_line[i + 1]){
        pipe(pipex->out); //error handle?
        pipex->pid = fork();
        if (pipex->pid == 0) {
            pipex->is_child = 1;
            break;
        }
        close(pipex->in);
        close(pipex->out[1]);
        pipex->in = pipex->out[0];
		pipex->out[1] = 1;
        i++;
    }
    cur_line = ft_strdup(pipe_line[i]);
    free(line);
    ft_freearray((void **)pipe_line);
    return cur_line;
}