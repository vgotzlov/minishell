/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:34:07 by msnizek           #+#    #+#             */
/*   Updated: 2025/05/28 14:02:01 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;

	p = s;
	while (n > 0)
	{
		if (*p == (unsigned char)c)
			return ((void *) p);
		p++;
		n--;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	numbers[] = {1, 2, 3, 4, 5};
	char	*num;

	num = ft_memchr(numbers, 4, 5);
	if (num != NULL)
		printf("%d", *num);
	else
		printf("Cannot find");
	return (0);
}*/
