/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haslan <haslan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:46:31 by matmaca           #+#    #+#             */
/*   Updated: 2024/08/21 15:34:11 by haslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../my_include/shell.h"

int	pwd(int fd)
{
	char	pwd[1024];

	getcwd(pwd, 1024);
	ft_putstr_fd(pwd, fd);
	ft_putstr_fd("\n", fd);
	return (0);
}
