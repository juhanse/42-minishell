/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:10:38 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/16 13:53:22 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_list_export(t_shell *data)
{
	int		i;
	int		j;
	char	**sorted_env;

	sorted_env = ft_copy_env(data);
	ft_sort_env(sorted_env);
	i = 0;
	while (sorted_env[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		j = 0;
		while (sorted_env[i][j] && sorted_env[i][j] != '=')
			ft_putchar_fd(sorted_env[i][j++], STDOUT_FILENO);
		if (sorted_env[i][j] == '=')
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(sorted_env[i] + j + 1, STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		free(sorted_env[i++]);
	}
	free(sorted_env);
}

static void	ft_add_update_env(t_shell *data, char *cmd)
{
	char	*value;
	char	*clean;
	char	*equal_sign;
	char	*clean_name;
	char	*clean_value;

	equal_sign = ft_strchr(cmd, '=');
	if (!equal_sign)
	{
		clean = export_remove_quotes(data, cmd);
		free(clean);
		return ;
	}
	*equal_sign = '\0';
	value = equal_sign + 1;
	clean_name = export_remove_quotes(data, cmd);
	clean_value = export_remove_quotes(data, value);
	ft_setenv(data, clean_name, clean_value, 1);
	*equal_sign = '=';
	free(clean_name);
	free(clean_value);
}

void	ft_export2(t_shell *data, char *merged, char **args, int *i)
{
	if (merged)
	{
		if (export_is_valid(merged))
			ft_add_update_env(data, merged);
		else
		{
			ft_dprintf(STDERR_FILENO, ERR_EXPORT, merged);
			g_exit_code = 1;
		}
		free(merged);
		*i += 2;
	}
	else
	{
		if (export_is_valid(args[*i]))
			ft_add_update_env(data, args[*i]);
		else
		{
			ft_dprintf(STDERR_FILENO, ERR_EXPORT, args[*i]);
			g_exit_code = 1;
		}
		(*i)++;
	}
}

void	ft_export(t_shell *data, int is_export)
{
	int		i;
	char	**args;
	char	*merged;

	args = data->cmd_list->args;
	if (is_export && !args[1])
	{
		ft_list_export(data);
		return ;
	}
	i = 0;
	if (is_export)
		i = 1;
	while (args[i])
	{
		merged = NULL;
		if (!ft_strchr(args[i], '='))
			merged = export_merge_split(args, i);
		ft_export2(data, merged, args, &i);
	}
}
