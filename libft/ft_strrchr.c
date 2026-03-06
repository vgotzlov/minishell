/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:08:33 by msnizek           #+#    #+#             */
/*   Updated: 2025/05/28 12:25:49 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;

	last = NULL;
	while (*s)
	{
		if (*(unsigned char *) s == (unsigned char) c)
			last = (char *) s;
		s++;
	}
	if (*(unsigned char *) s == (unsigned char) c)
		last = (char *) s;
	return (last);
}
/*
int	main(void)
{
	const char	str[] = "AhojPraha";
	char		*ptr;

	ptr = ft_strrchr(str, 'h');
	if (ptr != NULL)
		printf("%s", ptr);
	else
		printf("Cannot find");
	return (0);
}*/
