/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:22:31 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/19 13:55:26 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../../my_include/shell.h"

void	initalize_pipes(int	**fd, int pipe_num)
{
	int	j;
	int	tmp;

	j = 0;
	while (j < pipe_num)
	{
		fd[j] = (int *)malloc(sizeof(int) * 2);
		if (fd[j] == NULL)
		{
			free_2d_int(fd, j);
			my_exit2(1);
		}
		tmp = pipe(fd[j]);
		if (tmp == -1)
		{
			free_2d_int(fd, j);
			my_exit2(1);
		}
		j++;
	}
}

void	setup_pipes(t_shell *shell, char **subarrys)
{
	int				i;
	int				**fd;

	i = -1;
	while (subarrys[++i] != NULL)
		if (subarrys[i][0] == '|')
			shell->pipe_count++;
	if (shell->pipe_count == 0)
		return ;
	fd = (int **)malloc(sizeof(int *) * shell->pipe_count);
	if (fd == NULL)
		my_exit2(1);
	i = -1;
	initalize_pipes(fd, shell->pipe_count);
	shell->al_fd = fd;
}

void	fix_fd(t_shell *shell, t_cmd_list_node *node, int s)
{
	if (s == 0)
	{
		node->fd_in = 0;
		node->fd_out = shell->al_fd[s][1];
	}
	else if (s == shell->pipe_count)
	{
		node->fd_in = shell->al_fd[s - 1][0];
		node->fd_out = 1;
	}
	else
	{
		node->fd_in = shell->al_fd[s - 1][0];
		node->fd_out = shell->al_fd[s][1];
	}
}

void	connect_the_pipes(t_shell *shell)
{
	t_cmd_list_node	*node;
	int				s;

	node = shell->all_cmd->head;
	s = 0;
	if (shell->pipe_count > 0)
	{
		while (node)
		{
			if (node->op_code == MNODE)
			{
				fix_fd(shell, node, s);
				s++;
			}
			node = node->next;
		}
	}
	else
	{
		node->fd_in = 0;
		node->fd_out = 1;
	}
}
