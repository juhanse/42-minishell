/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:10:51 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/15 11:40:39 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_update_env_var(t_shell *data, char *name_eq, char *value, int i)
{
	char	*new_var;

	new_var = clean_strjoin(name_eq, value, data);
	free(data->env[i]);
	data->env[i] = new_var;
	return (0);
}

static int	ft_find_env(t_shell *data, char *name_eq, char *value, int over)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], name_eq, ft_strlen(name_eq)) == 0)
		{
			if (over)
				return (ft_update_env_var(data, name_eq, value, i));
			return (0);
		}
		i++;
	}
	return (-1);
}

int	ft_setenv(t_shell *data, char *name, char *value, int overwrite)
{
	char	*name_eq;
	int		result;

	if (!name || !value || !data->env)
		return (-1);
	name_eq = clean_strjoin(name, "=", data);
	result = ft_find_env(data, name_eq, value, overwrite);
	if (result == -1)
		result = ft_add_env(data, name, value);
	free(name_eq);
	return (result);
}

char	**ft_copy_env(t_shell *data)
{
	int		i;
	int		count;
	char	**copy;

	count = 0;
	while (data->env[count])
		count++;
	copy = (char **)malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = clean_strdup(data->env[i], data);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	ft_sort_env(char **env)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	len = 0;
	while (env[len])
		len++;
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}
