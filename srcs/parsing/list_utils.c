/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-woel <ade-woel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:16:48 by ade-woel          #+#    #+#             */
/*   Updated: 2025/04/14 18:16:49 by ade-woel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*new_token(int type, char *value, int quote, t_shell *data)
{
	t_token	*token;

	token = clean_malloc(sizeof(t_token), data);
	token->type = type;
	token->value = value;
	token->in_quote = quote;
	token->next = NULL;
	return (token);
}

t_token	*find_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lst_addback(t_token **lst_head, t_token *new_tok)
{
	t_token	*last;

	if (!new_tok)
		return ;
	if (!*lst_head)
	{
		*lst_head = new_tok;
		return ;
	}
	last = find_lstlast(*lst_head);
	last->next = new_tok;
}

int	lst_size(t_token *lst)
{
	int		size;
	t_token	*tmp;

	if (!lst)
		return (0);
	size = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}
