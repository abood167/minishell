#include "minishell.h"

int check_n(char *s)
{
	int i = 1;
	while(s[i] != '\0')
	{
		if(s[i] != 'n')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void echo_cmd(char **cmd, t_pipex pipex)
{
	int i = 1;
	int x = 1;
	int t = 0;
		
	while (cmd[i])
	{
		if(cmd[i][0] == '-' && cmd[i][1] != '\0' && cmd[i][1] == 'n')
		{
			if(check_n(cmd[i]) == 0)
			{
				x++;
				t = 1;

			}
			else
				break;
		}
		else
			break;
		
		i++;
	}
	i = x;

	while (cmd[i])
	{
		
		ft_putstr_fd(cmd[i],pipex.out[1]);
		if(cmd[(i + 1)] != NULL)
		{
			ft_putstr_fd(" ",pipex.out[1]);
		}
		i++;
	}
	
	if (t == 0)
    {
        ft_putstr_fd("\n",pipex.out[1]);
    }
}

void cd_cmd(char **cmd, t_list *g_env, t_list *l_var)
{
	char *tmp;
	if(cmd[1] == NULL)
	{
		tmp = get_var("HOME", 4, g_env, l_var);
		if(tmp == NULL)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		else if (chdir(getenv("HOME")) < 0) {
			ft_putstr_fd("minishell: cd: ", 2);
			perror(getenv("HOME"));
		}
	}
	else
	{
		 if (chdir(cmd[1]) < 0) 
		 {
			ft_putstr_fd("minishell: cd: ", 2);
			perror(cmd[1]);	//handle error
		 }
	}
}