/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:10:47 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/14 18:10:48 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_remove_env(t_shell *data, int pos)
{
	int	i;

	free(data->env[pos]);
	i = pos;
	while (data->env[i + 1])
	{
		data->env[i] = data->env[i + 1];
		i++;
	}
	data->env[i] = NULL;
}

void	ft_unset(t_shell *data, char **args)
{
	int		i;
	int		j;
	size_t	len;

	if (!args[1])
		return ;
	j = 1;
	while (args[j])
	{
		i = 0;
		len = ft_strlen(args[j]);
		while (data->env[i])
		{
			if (ft_strncmp(data->env[i], args[j], len) == 0 \
			&& data->env[i][len] == '=')
			{
				ft_remove_env(data, i);
				break ;
			}
			i++;
		}
		j++;
	}
}
