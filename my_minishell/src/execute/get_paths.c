/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmaca <matmaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:11:43 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/03 13:33:46 by matmaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "../../my_include/shell.h"

int	is_dir(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == -1)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

int	have_a_slash(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	**construct_absolute_or_relative_path(char *cmd)
{
	char	*paths;
	char	*tmp;
	char	**split_r;

	paths = getcwd(NULL, 0);
	if (paths == NULL)
		my_exit2(1);
	tmp = ft_strjoin(paths, "/");
	if (tmp == NULL)
		my_exit2(1);
	free(paths);
	paths = ft_strjoin(tmp, cmd);
	if (paths == NULL)
		my_exit2(1);
	free(tmp);
	split_r = ft_split(paths, ':');
	if (split_r == NULL)
		my_exit2(1);
	free(paths);
	return (split_r);
}

char	**get_path_in_env(t_env_list *env_list, char *cmd, int i)
{
	char	*paths;
	char	*tmp;
	char	**split_r;

	paths = get_in_envlst_path_node(env_list);
	if (paths == NULL)
		return (NULL);
	split_r = ft_split(paths, ':');
	if (split_r == NULL)
		my_exit2(1);
	while (split_r[i])
	{
		tmp = ft_strjoin(split_r[i], "/");
		if (tmp == NULL)
			my_exit2(1);
		free(split_r[i]);
		split_r[i] = tmp;
		tmp = ft_strjoin(split_r[i], cmd);
		if (tmp == NULL)
			my_exit2(1);
		free(split_r[i]);
		split_r[i] = tmp;
		i++;
	}
	return (split_r);
}

char	*get_paths(t_shell *shell, char *cmd)
{
	char	*paths;
	char	**split_r;
	int		flag;

	paths = NULL;
	split_r = NULL;
	flag = 0;
	if (cmd[0] == '.' && cmd[1] == '/')
		split_r = construct_absolute_or_relative_path(cmd);
	else if (cmd[0] == '/')
	{
		split_r = ft_split(cmd, ':');
		if (split_r == NULL)
			my_exit2(1);
		flag = 1;
	}
	else if (have_a_slash(cmd))
		split_r = construct_absolute_or_relative_path(cmd);
	else
		split_r = get_path_in_env(shell->env_list, cmd, 0);
	return (find_real_path(split_r, cmd, flag, paths));
}
