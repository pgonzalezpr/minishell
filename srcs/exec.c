#include "../include/minishell.h"

int exec_pipeline(t_minishell *minishell)
{
    t_list      *curr;
    pid_t       p_id;
    int         status;

	if (init_pipes(minishell) == -1 || exec_here_docs(minishell) == -1)
        return (-1);
    if (check_builtin(minishell) != 0)
        return (1);
    curr = minishell->commands;
    p_id = 0;
    while (curr)
    {
        p_id = create_child(curr->content);
        curr = curr->next;
    }
    close_pipes(minishell);
    waitpid(p_id, &status, 0);
    minishell->last_exit_code = WEXITSTATUS(status);
    return (1);
}
