/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-woel <ade-woel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:16:38 by ade-woel          #+#    #+#             */
/*   Updated: 2025/04/15 17:03:36 by ade-woel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*expand_exit(char *res, int *i, t_shell *data)
{
	char	*expanded_exit;
	char	*new;

	expanded_exit = ft_itoa(g_exit_code);
	new = clean_strjoin(res, expanded_exit, data);
	free(expanded_exit);
	free(res);
	*i += 2;
	return (new);
}

static char	*expand_var(char *res, char *str, int *i, t_shell *data)
{
	char	*expanded_var;
	char	*key;
	char	*new;
	int		j;

	j = *i + 1;
	while (str[j] && is_exp_char(str[j]))
		j++;
	key = clean_substr(str, (*i + 1), (j - *i - 1), data);
	expanded_var = find_env_value(key, data->env, data);
	free(key);
	if (expanded_var)
	{
		new = clean_strjoin(res, expanded_var, data);
		free(res);
		free(expanded_var);
		res = new;
	}
	*i = j;
	return (res);
}

char	*expander(t_shell *data, char *str)
{
	char	*res;
	int		i;

	res = clean_malloc(sizeof(char), data);
	res[0] = '\0';
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
				res = expand_exit(res, &i, data);
			else if (str[i + 1] && is_exp_char(str[i + 1]))
				res = expand_var(res, str, &i, data);
			else
				res = strjoin_char(res, str[i], &i, data);
		}
		else
			res = strjoin_char(res, str[i], &i, data);
	}
	return (res);
}

int	check_expand(t_shell *data, t_token *tokens)
{
	t_token	*tmp;
	char	*expanded;

	tmp = tokens;
	while (tmp)
	{
		if (should_expand(tmp->value, tmp->in_quote))
		{
			expanded = expander(data, tmp->value);
			free(tmp->value);
			tmp->value = expanded;
		}
		tmp = tmp->next;
	}
	return (0);
}
