/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:46:26 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/21 15:34:00 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../my_include/shell.h"

static void	handle_simple_export(t_shell *minishell, int fd);
static void	handle_export_with_values(char **cmd, t_shell *minishell, int i);
static void	update_existing_node(t_env_var *node, char *new_data, char *value);
static void	add_new_node(t_env_list *env_list, char **result_split,
				char *value);

int	export(char **cmd, t_shell *minishell, int fd)
{
	if (cmd[1] == NULL)
		handle_simple_export(minishell, fd);
	else
		handle_export_with_values(cmd, minishell, 0);
	return (0);
}

void	handle_simple_export(t_shell *minishell, int fd)
{
	t_env_var	**export_ary;

	export_ary = create_export_ary(minishell->env_list);
	if (export_ary == NULL)
		my_exit2(1);
	sort_nodearr(export_ary, minishell->env_list->list_size);
	display_export_arry(export_ary, minishell->env_list->list_size, fd);
	free(export_ary);
}

void	handle_export_with_values(char **cmd, t_shell *minishell, int i)
{
	char		**result_split;
	t_env_var	*node;

	while (cmd[++i] != NULL)
	{
		result_split = ft_split(cmd[i], '=');
		if (cmd[i][0] == '=' || ft_isdigit(result_split[0][0]))
		{
			if (cmd[i][0] == '=')
				printf("bash: export: `=': not a valid identifier\n");
			else
				printf("bash: export: `%s': not a valid identifier\n",
					result_split[0]);
			minishell->exit_status = 1;
			free_2d(result_split);
			continue ;
		}
		node = find_envlst_node(minishell->env_list, result_split[0]);
		if (node != NULL)
			update_existing_node(node, result_split[1], cmd[i]);
		else
			add_new_node(minishell->env_list, result_split, cmd[i]);
		free_2d(result_split);
	}
}

void	update_existing_node(t_env_var *node, char *new_data, char *value)
{
	char		*tmp;
	int			i;

	i = find(value, "=", 0);
	if (i != -1 && new_data == NULL)
	{
		tmp = ft_strdup("");
		if (tmp == NULL)
			my_exit2(1);
		free(node->data);
		node->data = tmp;
	}
	else if (new_data != NULL)
	{
		tmp = ft_strdup(new_data);
		if (tmp == NULL)
			my_exit2(1);
		free(node->data);
		node->data = tmp;
	}
}

void	add_new_node(t_env_list *env_list, char **result_split, char *value)
{
	t_env_var	*new_node;
	int			i;

	i = find(value, "=", 0);
	if (i == -1)
		new_node = create_envlst_node(ft_strdup(result_split[0]),
				NULL);
	else if (result_split[1] == NULL)
		new_node = create_envlst_node(ft_strdup(result_split[0]),
				ft_strdup(""));
	else
		new_node = create_envlst_node(ft_strdup(result_split[0]),
				ft_strdup(result_split[1]));
	if (new_node == NULL)
		my_exit2(1);
	add_envlst_node(env_list, new_node);
}
