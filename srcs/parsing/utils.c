/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-woel <ade-woel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:16:57 by ade-woel          #+#    #+#             */
/*   Updated: 2025/04/17 10:08:37 by ade-woel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	reset_data(t_shell *data)
{
	if (data->tokens)
	{
		free_tokens(data->tokens);
		data->tokens = NULL;
	}
	if (data->cmd_list)
	{
		free_cmds(data->cmd_list);
		data->cmd_list = NULL;
	}
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
}

int	is_redir(t_type type)
{
	if (type == REDIR_IN || type == REDIR_OUT || type == APPEND
		|| type == HERE_DOC)
		return (1);
	return (0);
}

void	print_error(char *error_msg, int exit_status)
{
	ft_putendl_fd(error_msg, 2);
	g_exit_code = exit_status;
}
