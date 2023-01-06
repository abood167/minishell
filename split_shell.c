#include "minishell.h"

//Mode 2 = || &&
//Mode 1 = |
t_list*	ft_split_shell(char *str, int mode, int brace)
{
	t_list	*split;
	int		start;
	int		pos;
	int		quote;

	split = NULL;
	pos = 0;
	start = 0;
    quote = 0;
	while (str[pos])
	{
		if (in_quote(str[pos], &quote))
            (void)NULL;
        else if(brace && str[pos] == '(') 
            brace++;
        else if(brace && str[pos] == ')') 
            brace--;
        else if(brace <= 1 && ((mode == 2 && !ft_strncmp(&str[pos], "&&", 2)) || !ft_strncmp(&str[pos], "||", mode))) { 
            if (pos - start > 0)
                ft_lstadd_back(&split, ft_lstnew(ft_substr(str, start, pos - start)));      
            ft_lstadd_back(&split, ft_lstnew(ft_substr(str, pos, mode)));
            pos += mode;
            start = pos;
            continue;
        }
        pos++;
	}
	if (pos - start > 0)
		ft_lstadd_back(&split, ft_lstnew(ft_strdup(&str[start])));
	return (split);
}

static int complete(char *oldline, t_mini *m) {
    int bak;
    char* str;

	bak = m->status;
	m->status = 0;
	rl_getc_function = getc;
    str = readline("> ");
    if(str == NULL) {
        if(!m->status) {
            ft_putstr_fd("minishell: syntax error: unexpected end of file\nexit\n", 2); //confirm if same as mac //test for leaks
            free_loop();
            free_exit();
            exit(2);
        }
        free(m->line);
        m->line = NULL;
        rl_getc_function = rl_getc;
        return 1;
    }
    m->line = ft_strmerge(oldline, str);
	m->status = bak;
    rl_getc_function = rl_getc;
    return 2;
}

int split_valid(t_list *split, char *oldline, int *val) {
    int key;
    int i;
    char *str;

    key = 1;
    while(split) {
        if (key == 1)
        {
            str = (char*) split->content;
            i = 0;
            while(str[i] && (str[i] == ' ' || str[i] == '('))
                i++;
            if (str[i] == '|' || !ft_strncmp(&str[i], "&&", 2) || str[i] == ')') {
                syntax_error(&str[i]); //need to do update status
                return ((*val = 1) && 0);
            }
            else if(!str[i])
                key = 0;

        }
        key = !key;
        split = split->next;
    }
    if(key)
        return ((*val = complete(oldline, get_mini())) && 0);
    return 1;
}

int bracket_invalid(char *str, int *val) {
	int i;
    int quote;
    int brace;

    quote = 0;
    brace = 0;
    i = 0;
	while (str[i] && brace >= 0)
	{
		if (in_quote(str[i], &quote))
			(void)NULL;
        else if (str[i] == '(') {
            brace++;
            i++;
            while(str[i] == ' ' || str[i] == '\n')
                i++;
            if (str[i] == '|' || !ft_strncmp(&str[i], "&&", 2) || str[i] == ')') {
                syntax_error(&str[i]);
                return *val = 1;
            }
            continue;
        }
        else if (str[i] == ')') {
            brace--;
            i++;
            while(str[i] == ' ' || str[i] == '\n')
                i++;
            if (str[i] && str[i] != ')' && str[i] != '|' && ft_strncmp(&str[i], "&&", 2)) {
                syntax_error(&str[i]);
                return *val = 1;
            }
            continue;
        }
        else if (str[i] != ' ' && str[i] != '\n') {
            while(str[i] && !(in_quote(str[i], &quote) || str[i] == '|' || !ft_strncmp(&str[i], "&&", 2) || str[i] == '(' || str[i] == ')'))
                i++;
            if(!ft_strncmp(&str[i], "&&", 2))
                i++;
            else if(str[i] == ')') 
                continue;
            else if(str[i] == '(') {
                syntax_error(&str[++i]);
                return *val = 1;
            }
        }
        if(str[i])
            i++;
    }
    if (brace > 0)
        return (*val = complete(str, get_mini()));
    else if (brace) {
        syntax_error(&str[i - 1]);
        return (1);
    }
    return 0;
}

int invalid_syntax(char *str, t_mini *m) {
    int quote;
    int i;
    char *temp;
    t_list *split;
    t_list *sub_split;
    t_list *start;
    
    quote = 0;
    i =0;
    while(str[i] == ' ')
        i++;
    if(!str[i])
        return 1;
    while(str[i]) 
        in_quote(str[i++], &quote);
    if(quote) 
        return complete(str, m);
    temp = strip_redirect(ft_strdup(str), m, 1, 0);
    if(!temp)
        return 1;
    if(bracket_invalid(temp, &i)) {
        free(temp);
        return i;
    }
    free(temp);
    split = ft_split_shell(str, 2, 0);
    if(!split)
        return 0;
    if(!split_valid(split, str, &i)) {
        ft_lstclear(&split, free);
        return i;
    }
    start = split;
    while(split) {
        sub_split = ft_split_shell((char *)split->content, 1, 0);     
        if(!split_valid(sub_split, str, &i)) {
            ft_lstclear(&sub_split, free);
            ft_lstclear(&start, free);
            return i;
        }
        ft_lstclear(&sub_split, free);
        split = split->next;
        if (split)
            split = split->next;
    }
    ft_lstclear(&start, free);
    return 0;
}

void syntax_error(char *str) {
    char **split;
    char  *word;
    int     i;

    get_mini()->status = 2;
    if(!str || !str[0] || str[0] == '\n')
        ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
    else if(!ft_strncmp(str, "||", 2))
        ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 2);
    else if(!ft_strncmp(str, "&&", 2))
        ft_putstr_fd("minishell: syntax error near unexpected token `&&'\n", 2);
    else if(str[0] == '|' || str[0] == '<' || str[0] == '>' || str[0] == '(' || str[0] == ')') {
        ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
        ft_putchar_fd(str[0], 2);
        ft_putstr_fd("'\n", 2);
    }
    else if(!ft_strncmp(str, "*", 1)) {
        ft_putstr_fd("minishell: *: ambiguous redirect\n", 2);  
        get_mini()->status = 1;
    }
    else {
        split = ft_split(str, ' ');
        ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
        i = 0;
        word = get_next_word(split[0], &i, ')');
        ft_putstr_fd(word, 2);
        ft_putstr_fd("'\n", 2);
        ft_freearray((void**)split);
        free(word);
    }
}
