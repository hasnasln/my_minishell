/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:46:15 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/16 18:49:59 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "../../my_include/shell.h"

static int	check_flag(char *src);
int			find_first_non_flag(char **cmd_f);
int			write_content(char **cmd_f, int write_i, int fd);

int	echo(char **cmd_f, int fd)
{
	int	write_i;

	write_i = find_first_non_flag(cmd_f);
	if (write_i == -1)
		return (-1);
	if (write_content(cmd_f, write_i, fd) == -1)
	{
		get_shell()->exit_status = 1;
		if (fd != 1)
			close(fd);
		return (-1);
	}
	if (fd != 1)
		close(fd);
	get_shell()->exit_status = 0;
	return (0);
}

int	find_first_non_flag(char **cmd_f)
{
	int	j;

	j = 1;
	while (cmd_f[j] != NULL && check_flag(cmd_f[j]))
		j++;
	return (j - 1);
}

int	write_content(char **cmd_f, int write_i, int fd)
{
	int	write_j;

	while (cmd_f[++write_i] != NULL)
	{
		write_j = -1;
		while (cmd_f[write_i][++write_j] != '\0')
			if (write(fd, &cmd_f[write_i][write_j], 1) == -1)
				return (perror("write"), -1);
		if (cmd_f[write_i + 1] != NULL)
			if (write(fd, " ", 1) == -1)
				return (perror("write"), -1);
	}
	if (cmd_f[1] == NULL || (cmd_f[1] != NULL && !check_flag(cmd_f[1])))
		if (write(fd, "\n", 1) == -1)
			return (perror("write"), -1);
	return (0);
}

static int	check_flag(char *src)
{
	int	i;

	i = 2;
	if (src[0] == '-' && src[1] == 'n')
	{
		while (src[i] == 'n')
			i++;
		if (src[i] == '\0')
			return (1);
		else
			return (0);
	}
	else
		return (0);
}
