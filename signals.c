#include "minishell.h"

void ctrl_c()
{
    t_pipex *pipex;
    
    pipex = get_pipex();
	//Maybe do wait here and then apply pipex.status?
	if(pipex->here_doc) 
		exit(130);
		// kill(pipex->pid, SIGTERM); //could cause leaks? // free stuff and do exit instead?
	if(pipex->pid != 0)
		return;
	pipex->status = 130;
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