/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_my_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:12:42 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/21 12:11:37 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../my_include/shell.h"

int	check_exit_value(char **line);
int	check_exit_others(char **line);

static void	put_error_and_exit(char **line)
{
	ft_putstr_fd("exit\nbash: exit: ", 2);
	ft_putstr_fd(line[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	my_exit2(255);
}

int	is_one_of_my_function(char **cmd)
{
	if (check_builtin_possibility(cmd[0], "exit"))
		return (1);
	else if (check_builtin_possibility(cmd[0], "echo"))
		return (1);
	else if (check_builtin_possibility(cmd[0], "cd"))
		return (1);
	else if (check_builtin_possibility(cmd[0], "export"))
		return (1);
	else if (check_builtin_possibility(cmd[0], "env"))
		return (1);
	else if (check_builtin_possibility(cmd[0], "pwd"))
		return (1);
	else if (check_builtin_possibility(cmd[0], "unset"))
		return (1);
	else
		return (0);
}

void	execute_myfunction(t_shell *shell, t_cmd_list_node *cmd_n,
		int fd_in, int fd_out)
{
	(void)fd_in;
	if (check_builtin_possibility(cmd_n->cmd[0], "exit"))
		if (check_exit_others(cmd_n->cmd))
			my_exit(check_exit_value(cmd_n->cmd));
	if (get_shell()->exit_status == -7)
		get_shell()->exit_status = 1;
	else
		get_shell()->exit_status = 0;
	if (check_builtin_possibility(cmd_n->cmd[0], "echo"))
		echo(cmd_n->cmd, fd_out);
	else if (check_builtin_possibility(cmd_n->cmd[0], "cd"))
		cd(cmd_n->cmd, fd_out, shell);
	else if (check_builtin_possibility(cmd_n->cmd[0], "export"))
		export(cmd_n->cmd, shell, fd_out);
	else if (check_builtin_possibility(cmd_n->cmd[0], "env"))
	{
		if (check_env_args(cmd_n->cmd))
			env(shell, 1);
	}
	else if (check_builtin_possibility(cmd_n->cmd[0], "pwd"))
		pwd(fd_out);
	else if (check_builtin_possibility(cmd_n->cmd[0], "unset"))
		unset(cmd_n->cmd, shell);
}

int	check_exit_value(char **line)
{
	int		i;
	char	*tmp;

	if (line[1] == NULL)
		return (get_shell()->exit_status);
	if (line[1][0] == '\0')
		put_error_and_exit(line);
	i = 0;
	while (line[1][i] == ' ')
		i++;
	if (line[1][i] == '-' || line[1][i] == '+')
		i++;
	while (line[1][i] != '\0')
	{
		if (ft_isdigit(line[1][i]) == 0 && line[1][i] != ' ')
			put_error_and_exit(line);
		i++;
	}
	tmp = line[1];
	line[1] = ft_strtrim(line[1], " ");
	free(tmp);
	return (ft_atoi(line[1]));
}

int	check_exit_others(char **line)
{
	int	i;

	i = 0;
	if (line[1] == NULL)
		return (1);
	while (line[1][i] == ' ')
		i++;
	while (line[1][i] != '\0' && line[1][i] != ' ')
	{
		if (ft_isdigit(line[1][i]) == 0)
			return (1);
		i++;
	}
	while (line[1][i] == ' ')
		i++;
	if (line[1][i] != '\0')
		put_error_and_exit(line);
	if (line[2] != NULL)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		get_shell()->exit_status = -7;
		return (0);
	}
	return (1);
}
