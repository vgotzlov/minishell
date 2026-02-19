/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:35:03 by msnizek           #+#    #+#             */
/*   Updated: 2025/06/02 15:19:18 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*(unsigned char *) s == (unsigned char) c)
			return ((char *) s);
		s++;
	}
	if (*(unsigned char *) s == (unsigned char) c)
		return ((char *) s);
	return (NULL);
}
/*
int	main(void)
{
	const char	str[] = "Ahoj";
	char		*ptr;

	ptr = ft_strchr(str, 'h');
	if (ptr != NULL)
		printf("%s", ptr);
	else
		printf("Cannot find");
	return (0);
}*/
