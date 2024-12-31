/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:56:24 by haslan            #+#    #+#             */
/*   Updated: 2023/10/22 15:04:12 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	counter_word(const char *text, char bracket)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (text[i] != '\0')
	{
		while (text[i] == bracket)
			i++;
		if (text[i] != '\0')
			counter++;
		while (text[i] != bracket && text[i])
			i++;
	}
	return (counter);
}

static char	**all_free(char **split_s, int i)
{
	while (i >= 0)
	{
		free(split_s[i]);
		i--;
	}
	free(split_s);
	return (NULL);
}

static int	start_index(char *text, char bracket, int word_no)
{
	int	i;
	int	counter;

	counter = -1;
	i = 0;
	while (text[i] != '\0')
	{
		while (text[i] == bracket)
			i++;
		if (text[i] != '\0')
		{
			counter++;
			if (counter == word_no)
				return (i);
		}
		while (text[i] != bracket && text[i])
			i++;
	}
	return (0);
}

static char	*ft_places_words(char *result, char *text, char bracket,
		int word_no)
{
	int	i;
	int	j;

	i = 0;
	j = start_index(text, bracket, word_no);
	while (!(text[j + i] == bracket || text[j + i] == '\0'))
		i++;
	result = (char *)malloc((i + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (!(text[j + i] == bracket || text[j + i] == '\0'))
	{
		result[i] = text[j + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int		word_number;
	char	**split_s;
	int		i;

	i = 0;
	word_number = counter_word(s, c);
	split_s = (char **)malloc((word_number + 1) * sizeof(char *));
	if (!split_s || !s)
		return (NULL);
	while (i < word_number)
	{
		split_s[i] = ft_places_words(split_s[i], (char *)s, c, i);
		if (!split_s[i])
			return ((char **)all_free(split_s, i));
		i++;
	}
	split_s[i] = NULL;
	return (split_s);
}
