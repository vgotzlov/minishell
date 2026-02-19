/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:18:08 by msnizek           #+#    #+#             */
/*   Updated: 2025/05/26 14:36:14 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*pdest;
	unsigned char	*psrc;

	if (!dest && !src)
		return (NULL);
	pdest = (unsigned char *)dest;
	psrc = (unsigned char *)src;
	while (n > 0)
	{
		*pdest++ = *psrc++;
		n--;
	}
	return (dest);
}
/*
int	main(void)
{
	char	src[] = "12345";
	char	dest[6];

	ft_memcpy(dest, src, 6);
	printf("%s", dest);
	return (0);
}*/
