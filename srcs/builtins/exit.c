/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:10:35 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/15 11:38:13 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_is_numeric(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	ft_exit_shell(t_shell *data, int code)
{
	free_data(data);
	exit(code);
}

void	ft_exit(t_shell *data)
{
	long	exit_code;

	printf("exit\n");
	if (!data->cmd_list->args[1])
		ft_exit_shell(data, 0);
	if (!ft_is_numeric(data->cmd_list->args[1]))
	{
		ft_dprintf(STDERR_FILENO, ERR_EXIT_NUM, data->cmd_list->args[1]);
		ft_exit_shell(data, 2);
	}
	if (data->cmd_list->args[2])
	{
		ft_dprintf(STDERR_FILENO, ERR_EXIT_ARGS);
		return ;
	}
	exit_code = ft_atoi(data->cmd_list->args[1]);
	ft_exit_shell(data, (int)(exit_code % 256));
}
