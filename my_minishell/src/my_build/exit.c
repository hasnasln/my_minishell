/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmaca <matmaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:46:19 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/03 13:26:15 by matmaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../../my_include/shell.h"

void	put_null(t_shell *shell);

void	my_exit(int status)
{
	t_shell	*shell;

	shell = get_shell();
	if (shell->line != NULL)
		free(shell->line);
	if (shell->env_list != NULL)
		free_envlst(shell->env_list);
	if (shell->hides != NULL)
		free_hidden_item_lst(shell->hides, 1);
	if (shell->all_cmd != NULL)
		free_cmd_list(shell->all_cmd);
	if (shell->new_enw != NULL)
		free_2d(shell->new_enw);
	if (shell->al_fd != NULL)
		free_2d_int(shell->al_fd, shell->pipe_count);
	if (shell->subarrays != NULL)
		free_2d(shell->subarrays);
	if (shell->sub_subarrays != NULL)
		free_2d(shell->sub_subarrays);
	put_null(shell);
	printf("exit\n");
	exit(status % 256);
}

void	put_null(t_shell *shell)
{
	shell->line = NULL;
	shell->env_list = NULL;
	shell->hides = NULL;
	shell->all_cmd = NULL;
	shell->new_enw = NULL;
	shell->al_fd = NULL;
	shell->subarrays = NULL;
	shell->sub_subarrays = NULL;
	shell = NULL;
}

void	my_exit2(int status)
{
	t_shell	*shell;

	shell = get_shell();
	if (shell->line != NULL)
		free(shell->line);
	if (shell->env_list != NULL)
		free_envlst(shell->env_list);
	if (shell->hides != NULL)
		free_hidden_item_lst(shell->hides, 1);
	if (shell->all_cmd != NULL)
		free_cmd_list(shell->all_cmd);
	if (shell->new_enw != NULL)
		free_2d(shell->new_enw);
	if (shell->al_fd != NULL)
		free_2d_int(shell->al_fd, shell->pipe_count);
	if (shell->subarrays != NULL)
		free_2d(shell->subarrays);
	if (shell->sub_subarrays != NULL)
		free_2d(shell->sub_subarrays);
	put_null(shell);
	exit(status % 256);
}
