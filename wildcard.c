#include "minshell.h"

char* wildcard(char **line) {
	t_list *list;
	int i;

	list = NULL;
	i = 0;
	while(line[i]) {
		if (ft_strchr(line[i],'*')) {
			match();
			ft_lstadd_back(&list, ft_lstnew(ft_strdup(new_file)));
		}
		else {
			ft_lstadd_back(&list, ft_lstnew(ft_strdup(line[i])));
		}
		i++;
	}
	return ft_lsttoarr(list);
}