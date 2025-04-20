/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:09:29 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/16 20:57:37 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_exec_child_native_cmd(t_shell *data)
{
	char	*cmd_path;

	exec_signals();
	apply_redirections(data->cmd_list->redirs);
	cmd_path = find_command_path(data, data->cmd_list->cmd);
	if (!cmd_path || data->cmd_list->cmd[0] == '\0')
	{
		ft_dprintf(STDERR_FILENO, ERR_CMD_NF, data->cmd_list->cmd);
		g_exit_code = 127;
		exit(g_exit_code);
	}
	execve(cmd_path, data->cmd_list->args, data->env);
	perror("execve");
	g_exit_code = 126;
	exit(g_exit_code);
}

void	ft_native_cmd(t_shell *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		ft_exec_child_native_cmd(data);
	else if (pid < 0)
	{
		perror("minishell: fork");
		g_exit_code = 1;
		exit(g_exit_code);
	}
	ignore_signals();
	waitpid(pid, &g_exit_code, 0);
	g_exit_code = WEXITSTATUS(g_exit_code);
	init_signals();
}

void	execute_simple(t_shell *data)
{
	int	stdin_backup;
	int	stdout_backup;

	ft_exec_backup(data, &stdin_backup, &stdout_backup);
	if (stdin_backup == -1 || stdout_backup == -1)
	{
		free_data(data);
		exit(EXIT_FAILURE);
	}
	ft_handle_heredocs(data->cmd_list);
	if (ft_isbuiltins(data->cmd_list->cmd))
	{
		apply_redirections(data->cmd_list->redirs);
		ft_builtins(data, data->cmd_list);
		ft_exec_restore(stdin_backup, stdout_backup);
	}
	else
	{
		ft_native_cmd(data);
		ft_exec_restore(stdin_backup, stdout_backup);
	}
}

void	execute_command(t_shell *data)
{
	int	stdin_backup;
	int	stdout_backup;

	g_exit_code = 0;
	if (!data->cmd_list->cmd && !data->cmd_list->args)
	{
		ft_exec_backup(data, &stdin_backup, &stdout_backup);
		ft_handle_heredocs(data->cmd_list);
		apply_redirections(data->cmd_list->redirs);
		ft_exec_restore(stdin_backup, stdout_backup);
		return ;
	}
	if (data->cmd_list->next == NULL)
		execute_simple(data);
	else
		execute_pipeline(data);
}
