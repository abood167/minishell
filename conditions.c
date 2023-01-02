#include "minishell.h"

int is_brace_block(char *line) {
    int brace;
    int i;
    int start;

    start = 1;
    brace = 0;
    i = 0;
    while(line[i] && (start || brace)) {
        if(line[i] == '(') {
            brace++;
            start = 0;
        }
        else if (line[i] == ')')
            brace--;
        i++;
    }
    while(line[i] && line [i] == ' ')
        i++;
    if(!line[i])
        return 1;
    return 0;
}

int start_with_brace(char *line) {
    int i;

    i = 0;
    while(line[i] && line [i] == ' ') 
        i++;
    if(line[i] == '(')
        return 1;
    return 0;
}

static char* brace_peel(char *line) {
    unsigned int start;
    unsigned int end;

    start = 0;
    while(line[start] != '(')
        start++;
    start++;

    end = ft_strlen(line) - 1;
    while(line[end] != ')')
        end--;
    end -= start;
    return ft_substr(line, start, end);
}

//Return 0, continue with line having a value
//use here_doc count just like in pipe
int shell_conditions(t_mini *m) { 
    pid_t pid;
    if (m->line)   {
        m->buffer = ft_split_shell(m->line, 2, 1);
        free(m->line);
        m->line = NULL;
    }
    if(!ft_strcmp((char*)m->buffer->content, "&&")) {
        ft_lstdelfirst(&m->buffer, free);
        if(m->status)
            ft_lstdelfirst(&m->buffer, free);
        return 1;
    }
    else if(!ft_strcmp((char*)m->buffer->content, "||")) {
        ft_lstdelfirst(&m->buffer, free);
        if(!m->status)
            ft_lstdelfirst(&m->buffer, free);
        return 1;
    }
    else if(is_brace_block((char*)m->buffer->content)) {
        pid = fork();
        if (pid == 0) {
            m->line = brace_peel((char*)m->buffer->content);
            ft_lstclear(&m->buffer, free);
            return shell_conditions(m);
        }
        waitpid(pid, &m->status, 0);
        m->status = WEXITSTATUS(m->status);
        ft_lstdelfirst(&m->buffer, free);
        return 1;
    }
    else {
        m->line = (char*)m->buffer->content;
        ft_lstdelfirst(&m->buffer, NULL);
        return 0;
    }
}