#include "minishell.h"

int alt_open(int *fd, char *file, int flag, int write) {
    t_mini *m;

    m = get_mini();
    if((fd == &m->out[1] && *fd != 1) || (fd == &m->in && *fd != 0))
        close(*fd);
    if(write)
        *fd = open(file, flag, 0644);
    else
        *fd = open(file, flag);
    if (*fd < 0)
    {
        ft_putstr_fd("minishell: ", 2);
        perror(file);
        free(file);
        m->status = 1;
        return 0;
    }
    return 1;
}

void alt_close(int *fd) {
    t_mini *m;

    m = get_mini();
    if((fd == &m->out[1] && *fd != 1) || (fd == &m->in && *fd != 0))
        close(*fd);
}

int alt_pipe(int out[]) {
    if(out[1] != 1)
        close(out[1]);
    close(out[0]);
    pipe(out);  //error handle?
}


void	shift_pipe(t_mini *m)
{
	alt_close(&m->in);
	alt_close(&m->out[1]);
	m->in = m->out[0];
}