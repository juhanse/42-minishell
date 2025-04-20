/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-woel <ade-woel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:47:57 by ade-woel          #+#    #+#             */
/*   Updated: 2025/04/16 17:49:28 by ade-woel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**env_plan_b(t_shell *data)
{
	char	**env;
	char	cwd[500];

	env = clean_malloc(sizeof(char *) * 4, data);
	env[0] = clean_strjoin("PWD=", getcwd(cwd, 500), data);
	env[1] = clean_strdup("SHLVL=1", data);
	env[2] = clean_strdup("_=/usr/bin/env", data);
	env[3] = NULL;
	return (env);
}

static void	copy_env(t_shell *data, char **new_env, char **envp_var)
{
	char	*shlvl;

	*new_env = clean_strdup(*envp_var, data);
	if (ft_strncmp(*new_env, "SHLVL=", 6) == 0)
	{
		shlvl = ft_itoa(ft_atoi(ft_strchr(*envp_var, '=') + 1) + 1);
		free(*new_env);
		*new_env = clean_strjoin("SHLVL=", shlvl, data);
		free(shlvl);
	}
}

static int	get_env_size(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}

char	**init_env(char **envp, t_shell *data)
{
	char	**env_cpy;
	int		size;
	int		i;

	env_cpy = NULL;
	if (!envp || envp[0] == NULL)
		env_cpy = env_plan_b(data);
	else
	{
		size = get_env_size(envp);
		env_cpy = clean_malloc(((size + 1) * sizeof(char *)), data);
		i = 0;
		while (i < size)
		{
			copy_env(data, &env_cpy[i], &envp[i]);
			i++;
		}
		env_cpy[i] = NULL;
	}
	return (env_cpy);
}
