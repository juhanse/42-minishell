/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-woel <ade-woel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:16:35 by ade-woel          #+#    #+#             */
/*   Updated: 2025/04/14 18:16:36 by ade-woel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	should_expand(const char *value, int quote_status)
{
	if (!value || !ft_strchr(value, '$'))
		return (0);
	if (quote_status == 1)
		return (0);
	return (1);
}

int	is_exp_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*strjoin_char(char *res, char c, int *i, t_shell *data)
{
	char	to_join[2];
	char	*tmp;

	to_join[0] = c;
	to_join[1] = '\0';
	tmp = clean_strjoin(res, to_join, data);
	free(res);
	*i += 1;
	return (tmp);
}

char	*find_env_value(const char *key, char **env, t_shell *data)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(key);
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, len) && env[i][len] == '=')
			return (clean_strdup((env[i] + len + 1), data));
		i++;
	}
	return (NULL);
}
