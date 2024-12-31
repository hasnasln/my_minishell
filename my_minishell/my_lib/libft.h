/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:38:09 by haslan            #+#    #+#             */
/*   Updated: 2024/08/15 17:04:32 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>

int					ft_atoi(const char *str);

void				ft_bzero(void *ptr, size_t n);

void				*ft_calloc(size_t coun, size_t size);

int					ft_isdigit(int c);

char				*ft_itoa(int n);

void				*ft_memcpy(void *dest, const void *src, size_t n);

char				**ft_split(char const *s, char c);

char				*ft_strchr(const char *str, int c);

char				*ft_strjoin(char const *s1, char const *s2);

size_t				ft_strlen(const char *str);

int					ft_strncmp(const char *str1, const char *str2, size_t n);

char				*ft_strtrim(char const *s1, char const *set);

char				*ft_substr(char const *s, unsigned int start, size_t len);

void				ft_putstr_fd(char *s, int fd);

char				*ft_strdup(const char *s1);

int					ft_isalpha(int c);

#endif