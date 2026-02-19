/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:35:31 by msnizek           #+#    #+#             */
/*   Updated: 2025/05/28 13:28:36 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	else
		return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
/*
int	main(void)
{
	char	a[] = "abc";
	char	b[] = "abd";

	printf("%d \n", ft_strncmp(a, b, 2));
	printf("%d \n", ft_strncmp(a, b, 3));
	printf("%d \n", ft_strncmp(a, a, 5));
	return (0);
}*/
