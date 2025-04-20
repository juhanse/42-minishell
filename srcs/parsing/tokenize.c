/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-woel <ade-woel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:16:54 by ade-woel          #+#    #+#             */
/*   Updated: 2025/04/17 10:46:55 by ade-woel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	token_pipe(t_shell *data, int *i)
{
	t_token	*token;

	token = new_token(PIPE, clean_strdup("|", data), 0, data);
	lst_addback(&data->tokens, token);
	*i += 1;
}

static void	token_redir(t_shell *data, char current, char next, int *i)
{
	t_token	*token;

	if (current == next)
	{
		if (current == '<')
			token = new_token(HERE_DOC, clean_strdup("<<", data), 0, data);
		if (current == '>')
			token = new_token(APPEND, clean_strdup(">>", data), 0, data);
		*i += 2;
	}
	else
	{
		if (current == '<')
			token = new_token(REDIR_IN, clean_strdup("<", data), 0, data);
		if (current == '>')
			token = new_token(REDIR_OUT, clean_strdup(">", data), 0, data);
		*i += 1;
	}
	lst_addback(&data->tokens, token);
}

static void	token_quoted(t_shell *data, int start, int *i)
{
	t_token	*token;
	char	*unquoted;
	int		j;
	int		len;

	len = 0;
	j = *i;
	while (data->prompt && data->prompt[++j] != data->prompt[start])
		len++;
	unquoted = clean_substr(data->prompt, start + 1, len, data);
	token = new_token(WORD, unquoted, quote_type(data->prompt[start]), data);
	lst_addback(&data->tokens, token);
	*i += len + 2;
}

static void	token_word(t_shell *data, int start, int *i)
{
	t_token	*token;
	char	*word;
	char	*clean_word;
	int		j;
	int		len;

	len = 0;
	j = *i;
	while (data->prompt && data->prompt[j] && in_word(data->prompt[j]))
	{
		if (data->prompt[j] == '\'' || data->prompt[j] == '\"')
			get_next_quote(data, &j, &len);
		else
		{
			j++;
			len++;
		}
	}
	word = clean_substr(data->prompt, start, len, data);
	clean_word = remove_quotes(word, data);
	free(word);
	token = new_token(WORD, clean_word, 0, data);
	lst_addback(&data->tokens, token);
	*i += len;
}

void	tokenize(t_shell *data)
{
	int	i;

	i = 0;
	while (data->prompt[i] && ft_strrchr(ISSPACE, data->prompt[i]) != NULL)
		i++;
	if (data->prompt[i] == '\0')
		return ;
	while (data->prompt[i])
	{
		while (data->prompt[i] && ft_strrchr(ISSPACE, data->prompt[i]) != NULL)
			i++;
		if (data->prompt[i] == '\0')
			break ;
		if (data->prompt[i] == '|')
			token_pipe(data, &i);
		else if (data->prompt[i] == '<' || data->prompt[i] == '>')
			token_redir(data, data->prompt[i], data->prompt[i + 1], &i);
		else if (data->prompt[i] == '\'' || data->prompt[i] == '\"')
			token_quoted(data, i, &i);
		else if (data->prompt[i])
			token_word(data, i, &i);
	}
}
