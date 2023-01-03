#include "minishell.h"

void ctrl_c()
{
    t_mini *m;
    
    m = get_mini();
	m->status = 130;
	if(rl_getc_function == getc)
		return;
	if(m->pid && ft_lstlast(m->pid)->content != 0)
		return;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void ctrl_slash()
{
    t_mini *m;
    
    m = get_mini();
	if(!m->pid) //no childs
	{
		//fix
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	else {
		printf("Quit");
		m->status = 131;
	}
}

void ft_int_signal()
{
    t_mini *m;
    
    m = get_mini();
	m->slash_dfl = signal(SIGQUIT, ctrl_slash);
	signal(SIGINT, ctrl_c );
}