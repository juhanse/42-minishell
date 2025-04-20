/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-woel <ade-woel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:16:27 by ade-woel          #+#    #+#             */
/*   Updated: 2025/04/14 18:16:28 by ade-woel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*clean_malloc(size_t size, t_shell *data)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
	{
		free_data(data);
		print_error(ERR_MALLOC, 1);
		exit (EXIT_FAILURE);
	}
	return (ret);
}

char	*clean_strdup(const char *str, t_shell *data)
{
	char	*dup;

	dup = ft_strdup(str);
	if (!dup)
	{
		free_data(data);
		print_error(ERR_MALLOC, 1);
		exit(EXIT_FAILURE);
	}
	return (dup);
}

char	*clean_strjoin(const char *s1, const char *s2, t_shell *data)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	if (!joined)
	{
		free_data(data);
		print_error(ERR_MALLOC, 1);
		exit(EXIT_FAILURE);
	}
	return (joined);
}

char	*clean_substr(char const *s, int start, size_t len, t_shell *data)
{
	char	*substr;

	substr = ft_substr(s, start, len);
	if (!substr)
	{
		free_data (data);
		print_error(ERR_MALLOC, 1);
		exit(EXIT_FAILURE);
	}
	return (substr);
}
