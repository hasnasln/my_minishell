/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_circle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmaca <matmaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:13:13 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/03 11:13:14 by matmaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../../my_include/shell.h"

void	close_pipes(int **fd, int pipe_num)
{
	int	i;

	i = 0;
	while (i < pipe_num)
	{
		if (fd[i][0] != -1)
		{
			close(fd[i][0]);
			fd[i][0] = -1;
		}
		if (fd[i][1] != -1)
		{
			close(fd[i][1]);
			fd[i][1] = -1;
		}
		free(fd[i]);
		i++;
	}
	free(fd);
}

void	clear_circle(t_shell *shell)
{
	if (shell->line != NULL)
		free(shell->line);
	if (shell->hides != NULL)
		free_hidden_item_lst(shell->hides, 0);
	if (shell->al_fd != NULL)
		close_pipes(shell->al_fd, shell->pipe_count);
	if (shell->all_cmd != NULL)
		free_cmd_list(shell->all_cmd);
	if (shell->new_enw != NULL)
		free_2d(shell->new_enw);
	shell->line = NULL;
	shell->al_fd = NULL;
	shell->all_cmd = NULL;
	shell->new_enw = NULL;
	shell->pipe_count = 0;
}
