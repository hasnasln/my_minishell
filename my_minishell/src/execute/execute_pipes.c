/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:07:04 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/19 17:49:45 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../../my_include/shell.h"

static void	execute_child(t_shell *shell, t_cmd_list_node *cmd_n, int cmd_no)
{
	char	*paths;
	int		i;

	i = 0;
	(void)cmd_no;
	dup2 (cmd_n->fd_in, 0);
	dup2 (cmd_n->fd_out, 1);
	while (i < shell->pipe_count)
	{
		close(shell->al_fd[i][0]);
		close(shell->al_fd[i][1]);
		i++;
	}
	if (is_one_of_my_function(cmd_n->cmd))
	{
		execute_myfunction(shell, cmd_n, 0, 1);
		if (cmd_n->fd_out != 1)
			close(cmd_n->fd_out);
		my_exit2(shell->exit_status);
	}
	else
	{
		paths = get_paths(shell, cmd_n->cmd[0]);
		execve(paths, cmd_n->cmd, shell->env);
	}
}

void	execute(t_shell *shell, t_cmd_list_node *cmd_n, int cmd_no)
{
	pid_t			pid;

	pid = fork();
	cmd_n->pid = pid;
	if (pid < 0)
	{
		perror("fork");
		my_exit2(1);
	}
	else if (pid == 0)
		execute_child (shell, cmd_n, cmd_no);
	else
	{
		if (cmd_n->fd_out != 1)
			close(cmd_n->fd_out);
		if (cmd_n->fd_in != 0)
			close(cmd_n->fd_in);
		cmd_n->fd_in = -1;
		cmd_n->fd_out = -1;
	}
}

void	wait_all_chld_and_close_fd(t_shell *shell)
{
	int				status;
	int				i;
	t_cmd_list_node	*node;

	node = shell->all_cmd->tail;
	while (node != NULL)
		if (node->op_code == RMNODE)
			break ;
	else
		node = node->prev;
	waitpid(node->pid, &status, 0);
	shell->exit_status = WEXITSTATUS(status);
	i = -1;
	while (++i < shell->pipe_count)
		wait(NULL);
	i = -1;
	while (++i < shell->pipe_count)
	{
		close(shell->al_fd[i][0]);
		shell->al_fd[i][0] = -1;
		close(shell->al_fd[i][1]);
		shell->al_fd[i][1] = -1;
	}
}

int	execute_pipes(t_shell *shell)
{
	t_cmd_list_node	*node;
	int				counter;

	counter = 0;
	get_shell()->exit_status = 0;
	node = shell->all_cmd->head;
	while (node)
	{
		if (node->op_code == RMNODE && node->cmd[0] != NULL)
		{
			execute(shell, node, counter);
			counter++;
		}
		node = node->next;
	}
	wait_all_chld_and_close_fd(shell);
	return (counter);
}
