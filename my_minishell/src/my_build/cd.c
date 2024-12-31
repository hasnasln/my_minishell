/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmaca <matmaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:46:12 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/03 13:24:42 by matmaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../my_include/shell.h"

static void	update_pwds(t_shell *minishell, char *old_pwd);
static void	olny_cd(t_shell *minishell, char *old_pwd, int fd);

int	cd(char **cmd, int fd, t_shell *minishell)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (cmd[1] != NULL && cmd[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", fd);
		free(old_pwd);
		minishell->exit_status = 1;
		return (1);
	}
	else if (cmd[0] && cmd[1] == NULL)
		olny_cd(minishell, old_pwd, 1);
	else if (cmd[1])
	{
		if (chdir(cmd[1]) == 0)
			update_pwds(minishell, old_pwd);
		else
		{
			if (old_pwd)
				free(old_pwd);
			perror("chdir");
			minishell->exit_status = 1;
		}
	}
	return (0);
}

static void	olny_cd(t_shell *minishell, char *old_pwd, int fd)
{
	char	*home;

	if (find_envlst_node(minishell->env_list, "HOME") == NULL)
	{
		ft_putstr_fd("Dont have home\n", fd);
		minishell->exit_status = 1;
		return ;
	}
	home = find_envlst_node(minishell->env_list, "HOME")->data;
	if (home == NULL)
	{
		ft_putstr_fd("Dont have home\n", fd);
		minishell->exit_status = 1;
	}
	else
	{
		if (chdir(home) == 0)
			update_pwds(minishell, old_pwd);
		else
		{
			perror ("chdir");
			minishell->exit_status = 1;
		}
	}
}

static void	update_pwds(t_shell *minishell, char *old_pwd)
{
	t_env_var	*node;

	node = find_envlst_node(minishell->env_list, "OLDPWD");
	if (node == NULL)
	{
		if (!add_envlst_node(minishell->env_list,
				create_envlst_node(ft_strdup("OLDPWD"), old_pwd)))
			my_exit2(1);
	}
	else
	{
		free(node->data);
		node->data = old_pwd;
	}
	node = find_envlst_node(minishell->env_list, "PWD");
	if (node == NULL)
		return ;
	free(node->data);
	node->data = getcwd(NULL, 0);
}
