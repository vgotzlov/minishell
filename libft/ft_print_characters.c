/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_characters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:10:08 by msnizek           #+#    #+#             */
/*   Updated: 2025/09/10 11:29:00 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_character(int c)
{
	return (write(1, &c, 1));
}

int	print_string(char *s)
{
	int	count;
	int	i;

	if (!s)
		return (print_string("(null)"));
	count = 0;
	i = 0;
	while (s[i])
	{
		print_character((int)s[i]);
		count++;
		i++;
	}
	return (count);
}

int	print_percent(void)
{
	print_character('%');
	return (1);
}
