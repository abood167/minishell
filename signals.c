#include "minishell.h"

void ctrl_c()
{
    t_pipex *pipex;
    pipex = get_pipex();
	//Maybe do wait here and then apply pipex.status?
	pipex->status = 130;
	if(rl_getc_function == getc)
		return;
	// kill(pipex->pid, SIGTERM); //could cause leaks? // free stuff and do exit instead?
	if(pipex->pid && ft_lstlast(pipex->pid)->content != 0)
		return;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void ft_int_signal()
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c );
}