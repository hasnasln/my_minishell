/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:10:27 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/21 13:13:03 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../my_include/shell.h"

void	single_cmd(t_shell *shell, t_cmd_list_node *cmd_n)
{
	if (is_one_of_my_function(cmd_n->cmd))
		execute_myfunction(shell, cmd_n, cmd_n->fd_in, cmd_n->fd_out);
	else
	{
		get_shell()->exit_status = 0;
		execute_others(shell, cmd_n);
	}
}

void	write_error(char *cmd, char *error, int code)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	my_exit2(code);
}

char	*find_real_path(char **split_r, char *cmd, int flag, char *paths)
{
	int	i;

	i = -1;
	while (split_r != NULL && split_r[++i])
	{
		if (is_dir(split_r[i]))
			write_error(cmd, "is a directory", 126);
		else if (access(split_r[i], F_OK) == 0)
		{
			if (access(split_r[i], X_OK) == 0)
			{
				paths = ft_strdup(split_r[i]);
				free_2d(split_r);
				return (paths);
			}
			else
				write_error(cmd, "Permission denied", 126);
		}
	}
	free_2d(split_r);
	if (flag == 0)
		write_error(cmd, "command not found...", 127);
	else
		write_error(cmd, "No such file or directory", 127);
	return (NULL);
}

char	*get_in_envlst_path_node(t_env_list *env_list)
{
	t_env_var	*node;

	node = find_envlst_node(env_list, "PATH");
	if (node == NULL)
		return (NULL);
	else
		return (node->data);
}
