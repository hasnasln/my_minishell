/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 12:06:11 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/21 13:21:48 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "../my_include/shell.h"

void	handle_empty_prompt_signal(int signo);
void	handle_heredoc_signal(int signo);
void	handle_executing_command_signal(int signo);

void	handle_signal(int signo)
{
	t_shell	*shell;

	shell = get_shell();
	if (shell->status == STATE_EMPTY_PROMPT)
		handle_empty_prompt_signal(signo);
	else if (shell->status == STATE_HEREDOC)
		handle_heredoc_signal(signo);
	else if (shell->status == STATE_EXECUTING_COMMAND)
		handle_executing_command_signal(signo);
	else if (shell->status == STATE_WAIT_HEREDOC)
		if (signo == SIGINT)
			get_shell()->flag = 1;
}

void	handle_empty_prompt_signal(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		get_shell()->exit_status = 1;
	}
}

void	handle_heredoc_signal(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		exit(1);
	}
}

void	handle_executing_command_signal(int signo)
{
	t_shell	*shell;

	shell = get_shell();
	if (signo == SIGINT || signo == SIGQUIT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		if (signo == SIGINT)
			shell->exit_status = 128 + SIGINT;
		else
			shell->exit_status = 128 + SIGQUIT;
	}
}

void	listen_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
