/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:16:11 by ade-woel          #+#    #+#             */
/*   Updated: 2025/04/16 13:44:42 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*redir_type_to_str(t_type type)
{
	if (type == REDIR_IN)
		return ("<");
	else if (type == REDIR_OUT)
		return (">");
	else if (type == APPEND)
		return (">>");
	else if (type == HERE_DOC)
		return ("<<");
	return ("UNKNOWN");
}

static void	print_redirs(t_redir *redirs)
{
	if (!redirs)
		printf("  - redirs : (none)\n");
	else
	{
		printf("  - redirs :\n");
		while (redirs)
		{
			printf("      • type : %s, file : %s\n",
				redir_type_to_str(redirs->type), redirs->file);
			redirs = redirs->next;
		}
	}
}

void	print_tab_str(char **tab, char *key)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		if (strncmp(tab[i], key, ft_strlen(key)) == 0)
		{
			printf("%s\n", tab[i]);
			return ;
		}
		i++;
	}
}

void	print_cmd_list(t_cmd *cmd_list)
{
	int	i;
	int	cmd_num;

	i = 0;
	cmd_num = 1;
	while (cmd_list)
	{
		printf("🔹 Commande #%d\n", cmd_num++);
		if (cmd_list->cmd)
			printf("  - cmd : %s\n", cmd_list->cmd);
		else
			printf("  - cmd : (null)\n");
		printf("  - args : ");
		if (cmd_list->args)
		{
			while (cmd_list->args[i])
				printf("[%s] ", cmd_list->args[i++]);
			printf("\n");
		}
		else
			printf("(none)\n");
		print_redirs(cmd_list->redirs);
		cmd_list = cmd_list->next;
	}
}
