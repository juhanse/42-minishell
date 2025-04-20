/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:09:34 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/15 11:43:36 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**get_paths_from_env(char **env)
{
	int		i;
	char	*path_env;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_env = env[i] + 5;
			return (ft_split(path_env, ':'));
		}
		i++;
	}
	return (NULL);
}

static char	*build_cmd_path(t_shell *data, char *path, char *cmd)
{
	char	*buffer;
	char	*full_path;

	buffer = clean_strjoin(path, "/", data);
	if (!buffer)
		return (NULL);
	full_path = clean_strjoin(buffer, cmd, data);
	free(buffer);
	if (!full_path)
		return (NULL);
	if (access(full_path, F_OK | X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*find_command_path(t_shell *data, char *cmd)
{
	int		i;
	char	**paths;
	char	*cmd_path;

	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	paths = get_paths_from_env(data->env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		cmd_path = build_cmd_path(data, paths[i], cmd);
		if (cmd_path)
		{
			free_tab(paths);
			return (cmd_path);
		}
		i++;
	}
	free_tab(paths);
	return (NULL);
}
