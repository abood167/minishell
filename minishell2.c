#include "minishell.h"

void	free_loop(void)
{
	if (!get_mini()->buffer)
		ft_lstclear(&get_mini()->doc_str, free);
	ft_freearray((void **)get_mini()->envp);
	ft_freearray((void **)get_mini()->cmds);
	ft_freearray((void **)get_mini()->paths);
	get_mini()->envp = NULL;
	get_mini()->cmds = NULL;
	get_mini()->paths = NULL;
	ft_lstclear(&get_mini()->pid, NULL);
	free(get_mini()->line);
	get_mini()->line = NULL;
	alt_close(&get_mini()->in);
	alt_close(&get_mini()->out[0]);
	alt_close(&get_mini()->out[1]);
}

void	free_exit(void)
{
	alt_close(&get_mini()->in);
	alt_close(&get_mini()->out[0]);
	alt_close(&get_mini()->out[1]);
	ft_lstclear(&get_mini()->pid, NULL);
	ft_lstclear(&get_mini()->doc_str, free);
	ft_lstclear(&get_mini()->buffer, free);
	ft_lstclear(&get_mini()->g_env, free);
	ft_lstclear(&get_mini()->l_var, free);
	rl_clear_history();
}



int get_input2() {
	if (shell_conditions(get_mini()))
		return 1 ;
	if (has_pipe(get_mini()->line))
		get_mini()->line = pipe_shell(get_mini()->line, get_mini());
	if (!get_mini()->line || has_brace(get_mini()->line, get_mini()))
		return 1 ;
	get_mini()->line = set_var(get_mini()->line, get_mini()->g_env, &get_mini()->l_var);
	get_mini()->line = strip_redirect(get_mini()->line, get_mini(),0, 0);
	if (!get_mini()->line)
		return 1 ;
	get_mini()->line = ft_wildcard(get_mini()->line, opendir("."));
	get_mini()->cmds = ft_splitquote(get_mini()->line, ' ');
	return 0;
}

int get_input()
{
	int	syntax;

	if (!get_mini()->buffer)
	{
		get_mini()->line = readline("minishell % ");
		if (get_mini()->line == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			free_loop();
			free_exit();
			exit(get_mini()->status);
		}
		if (get_mini()->line[0])
			add_history(get_mini()->line);
		syntax = 2;
		while (syntax == 2)
			syntax = invalid_syntax(get_mini()->line, get_mini());
		if (syntax)
			return 1 ;
		if (strip_heredoc(get_mini()->line, get_mini()))
			return 1 ;
	}
	return get_input2();
}