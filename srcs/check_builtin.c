#include "../include/minishell.h"

void    free_str_arr(char **arr)
{
    int idx;

    if (!arr)
        return ;
    idx = 0;
    while (arr[idx])
    {
        free(arr[idx]);
        idx++;
    }
    free(arr);
}

char    **build_str_arr_from_lst(t_list *lst)
{
    char    **arr;
    t_list  *curr;
    int     idx;

    arr = malloc(ft_lstsize(lst) + 1);
    if (!arr)
        return (NULL);
    arr[ft_lstsize(lst)] = NULL;
    curr = lst;
    idx = 0;
    while (curr)
    {
        arr[idx] = ft_strdup(curr->content);
        if (!arr[idx])
        {
            free_str_arr(arr);
            break;
        }
        idx++;
        curr = curr->next;
    }
    return (arr);
}

int exec_builtin(char *builtin, t_list *args, t_minishell *minishell)
{
    char    **argv;

    argv = build_str_arr_from_lst(args);
    if (!argv)
        return (-1);
    if (ft_strequals(builtin, ECHO_BUILTIN))
        builtin_echo(argv, minishell->env);
    if (ft_strequals(builtin, CD_BUILTIN))
        builtin_cd(minishell, argv);
    if (ft_strequals(builtin, ENV_BUILTIN))
        builtin_env(minishell);
    if (ft_strequals(builtin, EXP_BUILTIN))
        builtin_export(minishell);
    if (ft_strequals(builtin, PWD_BUILTIN))
        builtin_pwd(argv);
    if (ft_strequals(builtin, UNSET_BUILTIN))
        builtin_unset(minishell, argv);
    free_str_arr(argv);
    return (1);
}

char    *is_builtin(t_command *cmd)
{
    char    *builtin;

    builtin = cmd->args->content;
    if (ft_strequals(builtin, ECHO_BUILTIN))
        return (ECHO_BUILTIN);
    if (ft_strequals(builtin, CD_BUILTIN))
        return (CD_BUILTIN);
    if (ft_strequals(builtin, ENV_BUILTIN))
        return (ENV_BUILTIN);
    if (ft_strequals(builtin, EXP_BUILTIN))
        return (EXP_BUILTIN);
    if (ft_strequals(builtin, PWD_BUILTIN))
        return (PWD_BUILTIN);
    if (ft_strequals(builtin, UNSET_BUILTIN))
        return (UNSET_BUILTIN);
    return (NULL);
}

int check_builtin(t_minishell *minishell)
{
    t_command   *cmd;
    char        *builtin;

    if (minishell->cmd_count == 1)
    {
        cmd = minishell->commands->content;
        builtin = is_builtin(cmd);
        if (builtin)
        {
            cmd = minishell->commands->content;
            if (exec_builtin(builtin, cmd->args, minishell) == -1)
            {
                minishell->last_exit_code = EXIT_FAILURE;
                return (-1);
            }
            minishell->last_exit_code = EXIT_SUCCESS;
            return (1);
        }
    }
    return (0);
}