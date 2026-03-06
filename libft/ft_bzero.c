/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:40:17 by msnizek           #+#    #+#             */
/*   Updated: 2025/05/26 14:06:49 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
/*
int	main(void)
{
	char	buffer[10];
	int		i;

	ft_bzero(buffer, sizeof(buffer));
	i = 0;
	while (i < 10)
	{
		printf("%d", buffer[i]);
		i++;
	}
	printf("\n");
	return (0);
}*/
