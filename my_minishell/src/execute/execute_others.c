/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_others.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:06:45 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/19 16:35:21 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../../my_include/shell.h"

static void	execute_others_child(t_shell *shell, t_cmd_list_node *cmd_n)
{
	char	*paths;

	dup2(cmd_n->fd_in, 0);
	dup2(cmd_n->fd_out, 1);
	paths = get_paths(shell, cmd_n->cmd[0]);
	execve(paths, cmd_n->cmd, shell->new_enw);
}

void	execute_others(t_shell *shell, t_cmd_list_node *cmd_n)
{
	pid_t	child_pid;
	int		status;

	child_pid = fork();
	cmd_n->pid = child_pid;
	if (child_pid < 0)
	{
		perror("fork");
		my_exit2(1);
	}
	else if (child_pid == 0)
	{
		shell->status = -10;
		execute_others_child(shell, cmd_n);
	}
	else
	{
		waitpid(cmd_n->pid, &status, 0);
		if (get_shell()->exit_status == 0)
			shell->exit_status = WEXITSTATUS(status);
		if (cmd_n->fd_out != 1)
			close(cmd_n->fd_out);
		if (cmd_n->fd_in != 0)
			close(cmd_n->fd_in);
	}
}
