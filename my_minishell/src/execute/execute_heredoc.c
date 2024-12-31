/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:06:21 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/21 13:36:34 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../my_include/shell.h"

void	herdoc_in(char *limit, int output_fd)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = readline("\x1b[31m> \x1b[0m");
		if (!line || len_and_name_compare(limit, line))
		{
			free(line);
			break ;
		}
		tmp = line;
		line = env_expend(get_shell(), line);
		if (line == NULL)
		{
			free(tmp);
			my_exit2(1);
		}
		ft_putstr_fd(line, output_fd);
		ft_putstr_fd("\n", output_fd);
		free(line);
	}
}

void	execute_heredoc(t_shell *shell, t_cmd_list_node *node, int *fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	node->pid = pid;
	if (pid == -1)
	{
		perror("fork");
		my_exit2(1);
	}
	if (pid == 0)
	{
		shell->status = STATE_HEREDOC;
		herdoc_in(node->cmd[0], fd[1]);
		my_exit2(0);
	}
	get_shell()->status = STATE_WAIT_HEREDOC;
	waitpid(pid, &status, 0);
	shell->exit_status = 0;
	close(fd[1]);
}
