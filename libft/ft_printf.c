/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:55:09 by msnizek           #+#    #+#             */
/*   Updated: 2025/09/10 11:31:12 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	formats(va_list args, char format)
{
	int	count;

	count = 0;
	if (format == 'c')
		count += print_character(va_arg(args, int));
	else if (format == 's')
		count += print_string(va_arg(args, char *));
	else if (format == 'p')
		count += print_pointer(va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		count += print_decimal(va_arg(args, int));
	else if (format == 'u')
		count += print_unsigned(va_arg(args, unsigned int), 10, 0);
	else if (format == 'x')
		count += print_unsigned(va_arg(args, unsigned int), 16, 0);
	else if (format == 'X')
		count += print_unsigned(va_arg(args, unsigned int), 16, 1);
	else if (format == '%')
		count += print_percent();
	return (count);
}

int	ft_printf(const char *s, ...)
{
	va_list		args;
	size_t		i;
	int			count;

	if (!s)
		return (0);
	va_start(args, s);
	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1])
		{
			i++;
			count += formats(args, s[i]);
		}
		else
			count += print_character(s[i]);
		i++;
	}
	va_end(args);
	return (count);
}
/*
int	main(void)
{
	int	len1;
	int	len2;
	int	a;
	int	b;
	int	c;
	int	min;
	int max;

	// lenght of the string
	len1 = ft_printf("Hello %d %c\n", 42, '!');
	len2 = printf("Hello %d %c\n", 42, '!');
	printf("ft_printf returned: %d\n", len1);
	printf("printf returned:    %d\n", len2);
	if (len1 != len2)
	    printf("Return values differ!\n");
	else
    	printf("Return values match!\n");
	printf("\n");
	// %c
	printf("My:\n");
	ft_printf("%c", 'a');
	ft_printf("%c ", 'b');
	ft_printf(" %c ", 'c');
	ft_printf(" %c %c %c", 'd', 'e', ' ');
	printf("\nOG:\n");
	printf("%c", 'a');
	printf("%c ", 'b');
	printf(" %c ", 'c');
	printf(" %c %c %c", 'd', 'e', ' ');
	// %s
	printf("\nMy:\n");
	ft_printf("%s", "Hi");
	ft_printf(" %s ", "");
	ft_printf("%s", "42");
	ft_printf("%s %s %s", "How", "are", "you?");
	printf("\nOG:\n");
	printf("%s", "Hi");
	printf(" %s ", "");
	printf("%s", "42");
	printf("%s %s %s", "How", "are", "you?");
	// %p
	a = 1;
	b = 0;
	c = -1;
	min = INT_MIN;
	max = INT_MAX;
	printf("\nMy:\n");
	ft_printf("%p", (void *)&a);
	ft_printf(" %p ", (void *)&b);
	ft_printf(" %p ", (void *)&c);
	ft_printf(" %p %p ", (void *)&min, (void *)&max);
	printf("\nOG:\n");
	printf("%p", (void *)&a);
	printf(" %p ", (void *)&b);
	printf(" %p ", (void *)&c);
	printf(" %p %p ", (void *)&min, (void *)&max);
	// %d %i
	printf("\nMy:\n");
	ft_printf("%d %d %d %d %d", 0, 1, -1, INT_MIN, INT_MAX);
	ft_printf("%i %i %i %i %i", 0, 1, -1, INT_MIN, INT_MAX);
	printf("\nOG:\n");
	printf("%d %d %d %d %d", 0, 1, -1, INT_MIN, INT_MAX);
	printf("%i %i %i %i %i", 0, 1, -1, INT_MIN, INT_MAX);
	// %u
	printf("\nMy:\n");
	ft_printf("%u %u %u %u %u", 0, 1, -1, INT_MIN, INT_MAX);
	printf("\nOG:\n");
	printf("%u %u %u %u %u", 0, 1, -1, INT_MIN, INT_MAX);
	printf("\nMy:\n");
	// %x
	ft_printf("%x %x %x %x %x", 0, 1, -1, INT_MIN, INT_MAX);
	printf("\nOG:\n");
	printf("%x %x %x %x %x", 0, 1, -1, INT_MIN, INT_MAX);
	// %X
	printf("\nMy:\n");
	ft_printf("%X %X %X %X %X", 0, 1, -1, INT_MIN, INT_MAX);
	printf("\nOG:\n");
	printf("%X %X %X %X %X", 0, 1, -1, INT_MIN, INT_MAX);
	// %%
	printf("\nMy:\n");
	ft_printf("%%");
	ft_printf(" %% ");
	printf("\nOG:\n");
	printf("%%");
	printf(" %% ");
	return (0);
}*/
