/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:55:29 by msnizek           #+#    #+#             */
/*   Updated: 2025/05/26 15:50:07 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*pdest;
	unsigned char	*psrc;

	if (!dest && !src)
		return (NULL);
	pdest = (unsigned char *)dest;
	psrc = (unsigned char *)src;
	if (pdest < psrc)
		return (ft_memcpy(dest, src, n));
	else
	{
		pdest = pdest + n;
		psrc = psrc + n;
		while (n > 0)
		{
			*(--pdest) = *(--psrc);
			n--;
		}
	}
	return (dest);
}
/*
int	main(void)
{
	char	buffer1[20] = "1234567890";
	char	buffer2[20] = "1234567890";

	ft_memcpy(buffer1 + 2, buffer1, 8);
	ft_memmove(buffer2 + 2, buffer2, 8);
	printf("%s\n", buffer1);
	printf("%s", buffer2);
	return (0);
}*/
