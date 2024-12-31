/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_include_brackets.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmaca <matmaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:13:32 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/03 13:31:27 by matmaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../my_include/shell.h"

char	**split_include_brackets(char *text, char *brackets)
{
	int		len;
	int		i;
	char	**result;

	len = bracket_counter(text, brackets) * 2 + 1;
	result = (char **)malloc((len + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	result[len] = NULL;
	i = -1;
	while (++i < len)
	{
		result[i] = get_part(text, brackets, i % 2);
		if (result[i] == NULL)
		{
			while (--i >= 0)
				free(result[i]);
			free(result);
			return (NULL);
		}
		text += ft_strlen(result[i]);
	}
	return (result);
}

int	bracket_counter(char *text, char *brackets)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (text[i])
	{
		j = i;
		while (is_bracket(text[j], brackets) && text[i] == text[j])
			j++;
		if (is_bracket(text[i], brackets))
		{
			count++;
			j--;
		}
		i = j + 1;
	}
	return (count);
}

int	is_bracket(char c, char *brackets)
{
	int	i;

	i = -1;
	while (brackets[++i])
		if (brackets[i] == c)
			return (1);
	return (0);
}

char	*smash(char *text, int start, int end)
{
	char	*result;
	int		i;

	i = -1;
	result = (char *)malloc(sizeof(char) * (end - start + 2));
	if (result == NULL)
		return (NULL);
	while (start + (++i) <= end)
		result[i] = text[start + i];
	result[i] = '\0';
	return (result);
}

char	*get_part(char *text, char *brackets, int flag)
{
	int	len;

	len = 0;
	while (is_bracket(text[len], brackets) == flag && text[len] != '\0')
		len++;
	return (smash(text, 0, len - 1));
}
