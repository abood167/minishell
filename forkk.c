#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
  // The command buffer.
  char command[1024];

  // The main shell loop.
  while (1) {
    // Print the prompt.
    printf("$ ");

    // Read a command from the user.
    fgets(command, sizeof(command), stdin);

    // Execute the command.
    system(command);
  }

  return 0;
}

void echo_n_cmd(char **cmd)
{
    int i = 1;
    check_getenv(cmd);
    while (cmd[i])
    {
        if (strncmp(cmd[1],"-n",2) == 0)
        {
            cmd[i] = ft_strdup("");
        }
        else
        {
            printf("%s",cmd[i]);
            printf(" ");
        }
        i++;
    }
      if (strncmp(cmd[1],"-n",2) != 0)
        {
            printf("\n");
        }
}