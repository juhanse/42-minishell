/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-woel <ade-woel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:16:32 by ade-woel          #+#    #+#             */
/*   Updated: 2025/04/16 18:23:49 by ade-woel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**add_args(char **args, char *incoming_arg, t_shell *data)
{
	int		i;
	int		count;
	char	**new;

	i = 0;
	count = 0;
	while (args && args[count])
		count++;
	new = clean_malloc(((count + 2) * sizeof(char *)), data);
	while (i < count)
	{
		new[i] = clean_strdup(args[i], data);
		i++;
	}
	new[count] = clean_strdup(incoming_arg, data);
	new[count + 1] = NULL;
	free_tab (args);
	return (new);
}

void	add_to_cmd(t_token *token, t_cmd *cmd, t_shell *data)
{
	cmd->args = add_args(cmd->args, token->value, data);
	if (!cmd->cmd)
		cmd->cmd = token->value;
	return ;
}

t_redir	*add_redir(t_token *token, t_redir *redirs, t_shell *data)
{
	t_redir	*new_redir;
	t_redir	*tmp;

	new_redir = clean_malloc(sizeof(t_redir), data);
	new_redir->type = token->type;
	new_redir->fd = -1;
	new_redir->file = clean_strdup(token->next->value, data);
	new_redir->next = NULL;
	if (!redirs)
		return (new_redir);
	tmp = redirs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redir;
	return (redirs);
}

t_cmd	*add_pipe(t_cmd *cmd, t_shell *data)
{
	t_cmd	*new_cmd;

	data->cmd_count++;
	new_cmd = clean_malloc(sizeof(t_cmd), data);
	new_cmd->prev = cmd;
	new_cmd->next = NULL;
	new_cmd->args = NULL;
	new_cmd->cmd = NULL;
	new_cmd->redirs = NULL;
	cmd->next = new_cmd;
	return (new_cmd);
}

t_cmd	*tokens_to_cmds(t_token *tokens, t_shell *data)
{
	t_cmd	*head;
	t_cmd	*current;

	head = NULL;
	current = NULL;
	while (tokens)
	{
		if (!current)
			init_cmds(&current, &head, &data);
		if (tokens->type == WORD)
			add_to_cmd(tokens, current, data);
		else if (is_redir(tokens->type))
		{
			current->redirs = add_redir(tokens, current->redirs, data);
			tokens = tokens->next;
		}
		else if (tokens->type == PIPE)
			current = add_pipe(current, data);
		tokens = tokens->next;
	}
	return (head);
}
