#include "minishell.h"

int alt_open(int *fd, char *file, int flag, int write) {
    t_mini *m;

    m = get_mini();
    if(*fd > 1)
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
    if(*fd > 2)
        close(*fd);
}

int alt_pipe(int out[]) {
    if (out[0] != get_mini()->in)
        alt_close(&out[0]);
    alt_close(&out[1]);
    pipe(out);  //error handle?
    return 1;
}

void	shift_pipe(t_mini *m)
{
	alt_close(&m->in);
	alt_close(&m->out[1]);
	m->in = m->out[0];
    m->out[1] = -1;
}