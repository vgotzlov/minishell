/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:12:29 by msnizek           #+#    #+#             */
/*   Updated: 2025/05/26 14:02:51 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n > 0)
	{
		*p = (unsigned char) c;
		p++;
		n--;
	}
	return (s);
}
/*
int	main(void)
{
	char	buffer[10];
	int		i;

	ft_memset(buffer, 'A', sizeof(buffer));
	i = 0;
	while (i < 10)
	{
		printf("%c", buffer[i]);
		i++;
	}
	printf("\n");
	return (0);
}*/
