/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:17:08 by ade-woel          #+#    #+#             */
/*   Updated: 2025/04/17 11:21:27 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parse_prompt(t_shell *data)
{
	tokenize(data);
	if (!data->tokens)
		return ;
	if (!syntax_error(data->tokens) && !check_expand(data, data->tokens))
	{
		data->cmd_list = tokens_to_cmds(data->tokens, data);
		if (data->cmd_list)
			execute_command(data);
	}
	else
		return ;
}

static void	mini_loop(t_shell *data)
{
	while (1)
	{
		init_signals();
		reset_data(data);
		data->prompt = readline("minishell $ ");
		if (!data->prompt)
		{
			ft_printf("exit\n");
			break ;
		}
		if (*data->prompt)
		{
			add_history(data->prompt);
			if (valid_input(data->prompt) == SUCCESS)
				parse_prompt(data);
			free(data->prompt);
			data->prompt = NULL;
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*data;

	(void)av;
	if (ac != 1)
		return (ft_putendl_fd("Error, invalid arguments", 2), 1);
	init_data(&data, envp);
	mini_loop(data);
	free_data(data);
	return (0);
}
