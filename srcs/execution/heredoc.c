/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:09:48 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/15 12:10:31 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_heredoc(char *delimiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

static void	execute_heredoc(char *delimiter, int pipe_fd[2])
{
	close(pipe_fd[0]);
	handle_heredoc(delimiter, pipe_fd[1]);
	close(pipe_fd[1]);
	exit(0);
}

static void	process_heredoc(t_redir *redir)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		exec_signals();
		execute_heredoc(redir->file, pipe_fd);
	}
	else if (pid > 0)
	{
		close(pipe_fd[1]);
		redir->fd = pipe_fd[0];
		waitpid(pid, NULL, 0);
	}
	else
	{
		perror("minishell: fork");
		exit(EXIT_FAILURE);
	}
}

void	ft_handle_heredocs(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == HERE_DOC)
			process_heredoc(redir);
		redir = redir->next;
	}
}
