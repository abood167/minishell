#include "minishell.h"

void	wait_pipe(t_mini *m)
{
    t_list *node;
	int	status;

    node = m->pid;
    while(node) {
        waitpid((pid_t)(intptr_t)node->content, &status, 0);
        m->status = WEXITSTATUS(status);
        node = node->next;
    }
    ft_lstclear(&m->pid, NULL);
}

char	*pipe_shell(char *line, t_mini *m)
{
    t_list *pipe_line;
    t_list *start;

	pipe_line = ft_split_shell(line, 1, 1);
    start = pipe_line;
    free(line);
    line = NULL;
    while(pipe_line){
        if(((char *)pipe_line->content)[0] == '|')   
            pipe_line = pipe_line->next;
        if (pipe_line->next)
            alt_pipe(m->out); //error handle
        ft_lstadd_back(&m->pid, ft_lstnew((void*)(intptr_t)fork()));
        if (ft_lstlast(m->pid)->content == 0) {
            m->is_child = 1;
            break;
        }
        shift_pipe(m);
        heredoc_count(pipe_line->content, &m->here_doc);
        pipe_line = pipe_line->next;
    }
    if (pipe_line)
        line = ft_strdup((char*)pipe_line->content);
    ft_lstclear(&start, free);
    if(ft_lstlast(m->pid)->content != 0)
        wait_pipe(m);
    return line;
}
