/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:09:53 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/17 10:52:34 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	create_pipes(t_shell *data, int **pipes)
{
	int	i;

	i = -1;
	while (++i < data->cmd_count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
}

static void	exec_child(t_shell *data, int i, int **pipes)
{
	int		j;
	char	*find;

	find = find_command_path(data, data->cmd_list->cmd);
	if (!find || data->cmd_list->cmd[0] == '\0')
	{
		ft_dprintf(STDERR_FILENO, ERR_CMD_NF, data->cmd_list->cmd);
		g_exit_code = 127;
		exit(g_exit_code);
	}
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (data->cmd_list->next)
		dup2(pipes[i][1], STDOUT_FILENO);
	j = -1;
	while (++j < data->cmd_count - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
	}
	apply_redirections(data->cmd_list->redirs);
	execve(find, data->cmd_list->args, data->env);
	perror("execve");
	g_exit_code = 126;
	exit(g_exit_code);
}

static pid_t	start_child_process(t_shell *data, t_cmd *cmd, int i, int **p)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		data->cmd_list = cmd;
		exec_child(data, i, p);
	}
	return (pid);
}

void	execute_pipeline(t_shell *data)
{
	int		i;
	int		**pipes;
	t_cmd	*cmd;
	pid_t	last_pid;
	pid_t	pid;

	pipes = clean_malloc(sizeof(int *) * (data->cmd_count - 1), data);
	create_pipes(data, pipes);
	ignore_signals();
	cmd = data->cmd_list;
	last_pid = -1;
	i = 0;
	while (cmd)
	{
		pid = start_child_process(data, cmd, i++, pipes);
		if (pid < 0)
			handle_fork_error(data, pipes, last_pid);
		last_pid = pid;
		cmd = cmd->next;
	}
	close_pipes(data, pipes, last_pid);
	init_signals();
}
