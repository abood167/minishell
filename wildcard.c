#include "minshell.h"

int match_pattern(const char *pattern, const char *str) {
  while (*pattern != '\0'  ) {
    // Handle wildcard characters in the pattern
    if (*pattern == '*'  && *str != '.') {
      // The "*" wildcard matches any sequence of characters
      pattern++;
      // Try to match the rest of the pattern with the remaining part of the string
      while (*str != '\0') {
        if (match_pattern(pattern, str)) {
          return 1; // match found
        }
        str++;
      }
      return *pattern == '\0'; // match found if end of pattern reached
    } else if (*pattern == '?'  ) {
      // The "?" wildcard matches any single character
      str++;
    } else {
      // Regular characters must match exactly
      if (*pattern != *str) {
        return 0; // no match
      }
    }
    pattern++;
    str++;
  }

  // Match found if end of pattern and string reached
  return *pattern == '\0' && *str == '\0';
}



char **ft_wildcard(char **line) {
	t_list *list;
	int i;

	DIR *dir = opendir(".");
 	 struct dirent *entry;
	list = NULL;
	i = 0;
	while(line[i]) {
		if (ft_strchr(line[i],'*')) {
			while ((entry = readdir(dir)) != NULL) {
    // Check if the filename matches the pattern "*.txt"
   				if (match_pattern(line[i], entry->d_name)) {
			      ft_lstadd_back(&list, ft_lstnew(ft_strdup(entry->d_name)));
    			}
        }
			// match();
		}
		else {
			ft_lstadd_back(&list, ft_lstnew(ft_strdup(line[i])));
		}
		i++;
	}
	 closedir(dir);
	return (ft_lsttoarr(list));
}