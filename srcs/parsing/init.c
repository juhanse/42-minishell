/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-woel <ade-woel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:16:45 by ade-woel          #+#    #+#             */
/*   Updated: 2025/04/16 18:22:14 by ade-woel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_cmds(t_cmd **current, t_cmd **head, t_shell **data)
{
	*current = clean_malloc(sizeof(t_cmd), *data);
	**current = (t_cmd){0};
	(*data)->cmd_count = 1;
	if (!*head)
		*head = *current;
}

void	init_data(t_shell **data, char **envp)
{
	*data = clean_malloc(sizeof(t_shell), *data);
	**data = (t_shell){0};
	(*data)->env = init_env(envp, *data);
	return ;
}
