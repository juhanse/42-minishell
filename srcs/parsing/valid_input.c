/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-woel <ade-woel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:17:00 by ade-woel          #+#    #+#             */
/*   Updated: 2025/04/14 18:17:01 by ade-woel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	found_spec(char *prompt)
{
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	while (*prompt)
	{
		if (*prompt == '\"' && !s_quote)
			d_quote = !d_quote;
		else if (*prompt == '\'' && !d_quote)
			s_quote = !s_quote;
		else if (*prompt == ';' && !s_quote && !d_quote)
			return (1);
		else if (*prompt == '\\' && !s_quote && !d_quote)
			return (1);
		prompt++;
	}
	return (0);
}

static int	unclosed_quotes(char *prompt)
{
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	while (*prompt)
	{
		if (*prompt == '\"' && !s_quote)
			d_quote = !d_quote;
		else if (*prompt == '\'' && !d_quote)
			s_quote = !s_quote;
		prompt++;
	}
	if (s_quote || d_quote)
		return (1);
	return (0);
}

int	valid_input(char *prompt)
{
	if (unclosed_quotes(prompt))
	{
		ft_printf("minishell: error unclosed quotes\n");
		return (1);
	}
	if (found_spec(prompt))
	{
		ft_printf("minishell: error unsupported character\n");
		return (1);
	}
	return (0);
}
