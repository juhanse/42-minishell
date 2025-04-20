/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:10:23 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/16 22:52:18 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_update_pwd(t_shell *data, char *oldpwd)
{
	char	*newpwd;

	if (oldpwd)
	{
		ft_setenv(data, "OLDPWD", oldpwd, 1);
		free(oldpwd);
	}
	newpwd = getcwd(NULL, 0);
	if (newpwd)
	{
		ft_setenv(data, "PWD", newpwd, 1);
		free(newpwd);
	}
}

static char	*ft_get_path_to_cd(t_shell *data, char *path, char *oldpwd)
{
	char	*path_to_cd;

	if (!path || ft_strcmp(path, "~") == 0)
		path_to_cd = ft_getenv(data, "HOME");
	else if (ft_strcmp(path, "-") == 0)
	{
		path_to_cd = ft_getenv(data, "OLDPWD");
		if (!path_to_cd)
		{
			ft_putendl_fd(ERR_OLDPWD, STDERR_FILENO);
			free(oldpwd);
			return (NULL);
		}
		ft_putendl_fd(path_to_cd, STDOUT_FILENO);
	}
	else
		path_to_cd = path;
	return (path_to_cd);
}

void	ft_cd(t_shell *data, char *path)
{
	char	*oldpwd;
	char	*path_to_cd;

	oldpwd = getcwd(NULL, 0);
	path_to_cd = ft_get_path_to_cd(data, path, oldpwd);
	if (!path_to_cd)
		return ;
	if (chdir(path_to_cd) != 0)
	{
		ft_dprintf(STDERR_FILENO, ERR_SUCH_FOD, path_to_cd);
		g_exit_code = 1;
		free(oldpwd);
		return ;
	}
	ft_update_pwd(data, oldpwd);
}
