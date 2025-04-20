/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:10:32 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/16 22:52:45 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_add_env(t_shell *data, char *name, char *value)
{
	int		i;
	int		count;
	char	*tmp;
	char	*new_var;
	char	**new_env;

	count = 0;
	while (data->env[count])
		count++;
	new_env = (char **)malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (-1);
	i = -1;
	while (++i < count)
		new_env[i] = data->env[i];
	tmp = clean_strjoin(name, "=", data);
	new_var = clean_strjoin(tmp, value, data);
	free(tmp);
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free(data->env);
	data->env = new_env;
	return (0);
}

char	*ft_getenv(t_shell *data, char *name)
{
	int		i;
	size_t	name_len;

	if (!name || !data->env)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], name, name_len) == 0 && \
		data->env[i][name_len] == '=')
			return (data->env[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

void	ft_env(t_shell *data, char **args)
{
	int	i;

	if (args[1])
	{
		ft_dprintf(STDERR_FILENO, ERR_SUCH_FOD, args[1]);
		return ;
	}
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "_=", 2) != 0)
			printf("%s\n", data->env[i]);
		i++;
	}
	printf("_=/usr/bin/env\n");
}
