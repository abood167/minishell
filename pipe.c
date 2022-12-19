#include "minishell.h"

/*Solution for validation
first clone line
make sure quotes closes
empty strip redirect (to find issues)
split && || and | (special)
make sure no empty and does not start/end have in between with special
*/

char	*pipe_shell(char *line, t_pipex *pipex)
{
    t_list *pipe_line;
    t_list *start;

	pipe_line = ft_split_shell(line, 1);
    start = pipe_line;
    free(line);
    line = NULL;
    while(pipe_line){
        if(((char *)pipe_line->content)[0] == '|')   
            pipe_line = pipe_line->next;
        if (pipe_line->next)
            pipe(pipex->out); //error handle?
        pipex->pid = fork();
        if (pipex->pid == 0) {
            pipex->is_child = 1;
            break;
        }
        if(pipex->in != 0)
            close(pipex->in);
        if(pipex->out[1] != 1)
            close(pipex->out[1]);
        pipex->in = pipex->out[0];
		pipex->out[1] = 1;
        pipe_line = pipe_line->next;
    }
    if (pipe_line)
        line = ft_strdup((char*)pipe_line->content);
    ft_lstclear(&start, free);
    if(pipex->pid != 0) {  
        waitpid(pipex->pid, &pipex->status, 0);
        pipex->status = WEXITSTATUS(pipex->status);
    }
    return line;
}