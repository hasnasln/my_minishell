/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmaca <matmaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:22:37 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/03 13:30:26 by matmaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	quotes(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\"')
		{
			while (line[++i] != '\0' && line[i] != '\"')
				;
			if (line[i] == '\0')
				return (1);
			continue ;
		}
		else if (line[i] == '\'')
		{
			while (line[++i] != '\0' && line[i] != '\'')
				;
			if (line[i] == '\0')
				return (1);
			continue ;
		}
	}
	return (0);
}

static int	check_operator_pattern(char *str, int count, char oprt)
{
	int	i;
	int	counter;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == oprt)
		{
			counter = 0;
			while (str[++i] == oprt)
				counter++;
			if (counter >= count)
				return (1);
			while (str[i] == ' ')
				i++;
			if (str[i] == oprt || str[i] == '\0')
				return (1);
		}
		i++;
	}
	if (str[i - 1] == oprt)
		return (1);
	return (0);
}

static int	check_operator_syntax(char *str, char *oprators)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (oprators[j] != '\0')
		{
			if (str[i] == oprators[j])
			{
				if (oprators[j] == '|')
				{
					if (str[i + 1] == '>' || str[i + 1] == '<')
						return (1);
					if (i != 0 && (str[i - 1] == '<' || str[i - 1] == '>'))
						return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_special_operator_patterns(char *str)
{
	if (check_operator_pattern(str, 1, '|'))
		return (1);
	if (check_operator_pattern(str, 2, '<'))
		return (1);
	if (check_operator_pattern(str, 2, '>'))
		return (1);
	if (check_operator_syntax(str, "|<>"))
		return (1);
	return (0);
}
