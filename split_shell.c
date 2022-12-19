#include "minishell.h"

//Mode 2 = || &&
//Mode 1 = |
t_list*	ft_split_shell(char *str, int mode)
{
	t_list	*split;
	int		start;
	int		pos;
	int		quote;

	split = NULL;
	pos = 0;
	start = 0;
	while (str[pos])
	{
		if (!in_quote(str[pos], &quote))
		{
            if((mode == 2 && (!ft_strncmp(&str[pos], "&&", 2) || !ft_strncmp(&str[pos], "||", 2))) || (mode == 1 && !ft_strncmp(&str[pos], "|", 1))) { 
	            if (pos - start > 0)
				    ft_lstadd_back(&split, ft_lstnew(ft_substr(str, start, pos - start)));      
				ft_lstadd_back(&split, ft_lstnew(ft_substr(str, pos, mode)));
                pos += mode;
                start = pos;
                continue;
            }
		}
        pos++;
	}
	if (pos - start > 0)
		ft_lstadd_back(&split, ft_lstnew(ft_strdup(&str[start])));
	return (split);
}

int split_valid(t_list *split) {
    int key;
    int i;
    char *str;

    key = 1;
    while(split) {
        if (key == 1)
        {
            str = (char*) split->content;
            i = 0;
            while(str[i] && str[i] == ' ')
                i++;
            if (str[i] == '|' || str[i] == '&') {
                ft_putstr_fd("Error description tbd\n", 2); //need to do
                return 0;
            }
        }
        key = !key;
        split = split->next;
    }
    if(key)
        ft_putstr_fd("Error description tbd\n", 2);
    return !key;
}

//make status to 2 if true
int invalid_syntax(char *str, t_pipex *pipex) {
    int quote;
    int i;
    char *temp;
    t_list *split;
    t_list *sub_split;
    t_list *start;
    
    quote = 0;
    i =0;
    while(str[i]) 
        in_quote(str[i++], &quote);
    if(quote) 
    {
        ft_putstr_fd("Quotes must close\n", 2); 
        return 1;
    }
    temp = strip_redirect(ft_strdup(str), pipex, 1);
    if(!temp)
        return 1;
    free(temp);
    split = ft_split_shell(str, 2);
    if(!split)
        return 0;
    if(!split_valid(split)) {
        ft_lstclear(&split, free);
        return 1;
    }
    start = split;
    while(split) {
        sub_split = ft_split_shell((char *)split->content, 1);     
        if(!split_valid(sub_split)) {
            ft_lstclear(&sub_split, free);
            ft_lstclear(&start, free);
            return 1;
        }
        ft_lstclear(&sub_split, free);
        split = split->next;
        if (split)
            split = split->next;
    }
    ft_lstclear(&start, free);
    return 0;
}