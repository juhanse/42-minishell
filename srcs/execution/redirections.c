/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:09:58 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/16 22:51:21 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_open_file(t_redir *redir)
{
	int	fd;

	if (redir->type == REDIR_IN)
		fd = open(redir->file, O_RDONLY);
	else if (redir->type == REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (redir->fd);
	if (fd == -1)
	{
		ft_dprintf(2, ERR_SUCH_FOD, redir->file);
		g_exit_code = 1;
	}
	return (fd);
}

static int	ft_redirect_fd(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		perror("minishell: dup2");
		g_exit_code = 1;
		return (0);
	}
	close(old_fd);
	return (1);
}

static void	ft_process_redir(t_redir *redir)
{
	int	fd;
	int	target_fd;

	fd = ft_open_file(redir);
	if (fd < 0)
		return ;
	target_fd = STDOUT_FILENO;
	if (redir->type == REDIR_IN || redir->type == HERE_DOC)
		target_fd = STDIN_FILENO;
	if (!ft_redirect_fd(fd, target_fd))
		exit(EXIT_FAILURE);
}

void	apply_redirections(t_redir *redirs)
{
	t_redir	*current;

	current = redirs;
	while (current)
	{
		ft_process_redir(current);
		current = current->next;
	}
}
