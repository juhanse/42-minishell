/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:10:19 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/15 18:39:01 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_isbuiltins(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp("echo", cmd) || !ft_strcmp("pwd", cmd) \
	|| !ft_strcmp("env", cmd) || !ft_strcmp("unset", cmd) \
	|| !ft_strcmp("export", cmd) || !ft_strcmp("cd", cmd) \
	|| !ft_strcmp("exit", cmd) || ft_strchr(cmd, '='))
		return (1);
	return (0);
}

void	ft_builtins(t_shell *data, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd->cmd, "echo"))
		ft_echo(cmd->args);
	else if (!ft_strcmp(cmd->cmd, "env"))
		ft_env(data, cmd->args);
	else if (!ft_strcmp(cmd->cmd, "cd"))
		ft_cd(data, cmd->args[1]);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		ft_unset(data, cmd->args);
	else if (!ft_strcmp(cmd->cmd, "export"))
		ft_export(data, 1);
	else if (ft_strchr(cmd->cmd, '='))
		ft_export(data, 0);
	else if (!ft_strcmp(cmd->cmd, "exit"))
		ft_exit(data);
}
