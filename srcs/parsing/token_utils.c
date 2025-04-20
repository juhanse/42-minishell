/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-woel <ade-woel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:07:13 by ade-woel          #+#    #+#             */
/*   Updated: 2025/04/17 10:48:58 by ade-woel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_next_quote(t_shell *data, int *j, int *len)
{
	char	quote;

	quote = data->prompt[(*j)++];
	(*len)++;
	while (data->prompt[*j] && data->prompt[*j] != quote)
	{
		(*j)++;
		(*len)++;
	}
	if (data->prompt[*j] == quote)
	{
		(*j)++;
		(*len)++;
	}
}

int	quote_type(char quote)
{
	if (quote == '\'')
		return (1);
	if (quote == '\"')
		return (2);
	else
		return (0);
}

char	*remove_quotes(char	*word, t_shell *data)
{
	int		i;
	int		j;
	char	quote;
	char	*cleaned;

	i = 0;
	j = 0;
	cleaned = clean_malloc(ft_strlen(word) + 1, data);
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '\"')
		{
			quote = word[i++];
			while (word[i] && word[i] != quote)
				cleaned[j++] = word[i++];
			if (word[i] == quote)
				i++;
		}
		else
			cleaned[j++] = word[i++];
	}
	cleaned[j] = '\0';
	return (cleaned);
}

int	in_word(char c)
{
	if (!ft_strrchr(METACHAR, c) && !ft_strrchr(ISSPACE, c))
		return (1);
	return (0);
}
