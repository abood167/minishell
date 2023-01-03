valgrind --suppressions=readline.supp --track-origins=yes --track-fds=yes --leak-check=full --show-leak-kinds=all --trace-children=yes --gen-suppressions=no --quiet ./minishell
# -s