#include <dirent.h>
#include <fnmatch.h>
#include <stdio.h>
#include <stdlib.h>

// Function that checks if a string matches a wildcard pattern
int	match_pattern(const char *pattern, const char *str)
{
	while (*pattern != '\0')
	{
		// Handle wildcard characters in the pattern
		if (*pattern == '*')
		{
			// The "*" wildcard matches any sequence of characters
			pattern++;
			// Try to match the rest of the pattern with the remaining part of the string
			while (*str != '\0')
			{
				if (match_pattern(pattern, str))
				{
					return (1); // match found
				}
				str++;
			}
			return (*pattern == '\0'); // match found if end of pattern reached
		}
		else if (*pattern == '?')
		{
			// The "?" wildcard matches any single character
			str++;
		}
		else
		{
			// Regular characters must match exactly
			if (*pattern != *str)
			{
				return (0); // no match
			}
		}
		pattern++;
		str++;
	}
	// Match found if end of pattern and string reached
	return (*pattern == '\0' && *str == '\0');
}

int	main(int argc, char *argv[])
{
	// Get all filenames in the current directory
	DIR *dir = opendir(".");
	struct dirent *entry;

	// Iterate over the filenames in the directory
	while ((entry = readdir(dir)) != NULL)
	{
		// Check if the filename matches the pattern "*.txt"
		if (match_pattern("*.c", entry->d_name))
		{
			printf("%s\n", entry->d_name);
		}
	}

	closedir(dir);
	return (0);
}