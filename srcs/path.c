#include "../include/minishell.h"

char	*build_path(char *cmd, char *dir)
{
	char	*path;
	char	*tmp;

	path = ft_strjoin(dir, "/");
	if (!path)
		return (NULL);
	tmp = path;
	path = ft_strjoin(path, cmd);
	free(tmp);
	if (!path)
		return (NULL);
	return (path);
}

char	*get_bin_path(char *cmd, char **paths)
{
	char	*path;

	if (!cmd || !paths)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (*paths)
	{
		path = build_path(cmd, *paths);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		paths++;
	}
	return (NULL);
}

char	**get_paths(char **envp)
{
	char	**cmd_paths;

	cmd_paths = NULL;
	while (*envp)
	{
		if (ft_strncmp(*envp, VAR_PATH_WITH_EQUAL, 5) == 0)
		{
			cmd_paths = ft_split(*envp + 5, ':');
			if (!cmd_paths)
				return (NULL);
			break ;
		}
		envp++;
	}
	return (cmd_paths);
}

char	*build_cmd_path(char *cmd_name, t_minishell *minishell)
{
	char	**paths;
	char	*bin_path;

	paths = get_paths(minishell->envp);
	if (!paths)
		return (NULL);
	bin_path = get_bin_path(cmd_name, paths);
	free_str_arr(paths);
	return (bin_path);
}
