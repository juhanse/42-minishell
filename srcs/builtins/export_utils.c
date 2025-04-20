/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:51:13 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/16 13:52:19 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*export_remove_quotes(t_shell *data, char *s)
{
	int		i;
	int		j;
	char	*cleaned;
	char	*str;

	i = 0;
	j = 0;
	str = s;
	cleaned = clean_malloc((ft_strlen(str) + 1), data);
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
			cleaned[j++] = str[i];
		i++;
	}
	cleaned[j] = '\0';
	return (cleaned);
}

char	*export_merge_split(char **args, int i)
{
	if (!args[i + 1])
		return (NULL);
	if (args[i + 1][0] == '=')
		return (ft_strjoin(args[i], args[i + 1]));
	return (NULL);
}

int	export_is_valid(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (str[0] == '\'' || str[0] == '"')
		str++;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			i++;
			continue ;
		}
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
