/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:08:33 by msnizek           #+#    #+#             */
/*   Updated: 2025/06/02 15:18:00 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		lenght;
	int		i;

	lenght = ft_strlen(s);
	dup = (char *) malloc(sizeof(char) * (lenght + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < lenght)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
/*
int	main(void)
{
	char	str[] = "Ahoj";
	char	*dup;

	dup = ft_strdup(str);
	printf("%s", dup);
	return (0);
}*/
