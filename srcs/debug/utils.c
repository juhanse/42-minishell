/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-woel <ade-woel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:16:20 by ade-woel          #+#    #+#             */
/*   Updated: 2025/04/14 18:16:21 by ade-woel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*token_type_to_str(t_type type)
{
	if (type == WORD)
		return ("WORD");
	if (type == PIPE)
		return ("PIPE");
	if (type == REDIR_IN)
		return ("REDIR_IN");
	if (type == REDIR_OUT)
		return ("REDIR_OUT");
	if (type == APPEND)
		return ("APPEND");
	if (type == HERE_DOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

void	print_tokens(t_token *token_list)
{
	int	i;

	i = 0;
	while (token_list)
	{
		printf("Token %d:\n", i);
		printf("  Type : %s\n", token_type_to_str(token_list->type));
		printf("  Value: %s\n", token_list->value);
		printf("  Quote status : %d\n", token_list->in_quote);
		token_list = token_list->next;
		i++;
	}
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	if (!*tab)
		printf("Tab vide\n");
	else
	{
		while (tab[i])
		{
			printf("%s\n", tab[i]);
			i++;
		}
	}
}
