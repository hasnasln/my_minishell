/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 12:00:33 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/21 15:34:21 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> 
#include <unistd.h>
#include "../../my_include/shell.h"

static t_cmd_list_node	*get_node(t_cmd_list *all_cmd,
	t_cmd_list_node **node_to_update)
{
	t_cmd_list_node	*node;

	node = all_cmd->head;
	while (node != NULL)
	{
		if (node->op_code == MNODE)
			*node_to_update = node;
		if (node->op_code == RII)
			return (node->next);
		node = node->next;
	}
	return (NULL);
}

static int	handle_heredoc(t_shell *shell)
{
	t_cmd_list_node	*node;
	t_cmd_list_node	*node_to_update;
	int				fd[2];

	node = get_node(shell->all_cmd, &node_to_update);
	if (node == NULL)
		return (1);
	if (pipe(fd) == -1)
	{
		perror("pipe");
		my_exit2(1);
	}
	execute_heredoc(shell, node, fd);
	node->prev->op_code = ERII;
	node->op_code = FNAME;
	if (node->fd_in != -1 && node->fd_in != 0)
		close(node->fd_in);
	node->fd_in = fd[0];
	return (0);
}

void	heredoc_settings(t_shell *shell)
{
	int	result;

	while (1)
	{
		result = handle_heredoc(shell);
		if (result == 1 || shell->flag == 1)
		{
			break ;
		}
	}
}
