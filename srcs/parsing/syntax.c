/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:16:50 by ade-woel          #+#    #+#             */
/*   Updated: 2025/04/16 17:14:50 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	syntax_redir(t_token *token)
{
	if (is_redir(token->type) && token->next == NULL)
		return (print_error(ERR_TOK_NL, 2), 1);
	if (is_redir(token->type) && token->next->type != WORD)
	{
		if (token->next->type == PIPE)
			ft_putendl_fd(ERR_TOK_PIPE, 2);
		else if (token->next->type == REDIR_IN)
			ft_putendl_fd(ERR_TOK_RIN, 2);
		else if (token->next->type == REDIR_OUT)
			ft_putendl_fd(ERR_TOK_ROUT, 2);
		else if (token->next->type == HERE_DOC)
			ft_putendl_fd(ERR_TOK_HD, 2);
		else if (token->next->type == APPEND)
			ft_putendl_fd(ERR_TOK_APP, 2);
		g_exit_code = 2;
		return (1);
	}
	return (0);
}

int	syntax_error(t_token *tokens)
{
	t_token	*prev;

	prev = NULL;
	if (!tokens)
		return (0);
	if (tokens->type == PIPE)
		return (print_error(ERR_TOK_PIPE, 2), 1);
	while (tokens)
	{
		if (is_redir(tokens->type) && syntax_redir(tokens))
			return (1);
		if (tokens->type == PIPE
			&& (!prev || prev->type != WORD || !tokens->next))
			return (print_error(ERR_TOK_PIPE, 2), 1);
		prev = tokens;
		tokens = tokens->next;
	}
	return (0);
}
