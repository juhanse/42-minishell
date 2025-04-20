/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:10:04 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/17 10:49:47 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exec_backup(t_shell *data, int *stdin_backup, int *stdout_backup)
{
	*stdin_backup = dup(STDIN_FILENO);
	*stdout_backup = dup(STDOUT_FILENO);
	if (*stdin_backup == -1 || *stdout_backup == -1)
	{
		perror("minishell: dup");
		free_data(data);
		exit(EXIT_FAILURE);
	}
}

void	ft_exec_restore(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}

void	close_pipes(t_shell *data, int **pipes, pid_t last_pid)
{
	int		i;
	int		status;
	pid_t	pid;

	i = -1;
	while (++i < data->cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
	}
	free(pipes);
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
			if (WIFEXITED(status))
				g_exit_code = WEXITSTATUS(status);
		pid = wait(&status);
	}
}

void	handle_fork_error(t_shell *data, int **pipes, pid_t last_pid)
{
	free_data(data);
	close_pipes(data, pipes, last_pid);
	perror("fork");
	exit(EXIT_FAILURE);
}
