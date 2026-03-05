/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:18:29 by msnizek           #+#    #+#             */
/*   Updated: 2025/09/10 11:30:12 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_decimal(int n)
{
	long	ln;
	int		count;
	char	*digits;

	ln = n;
	digits = "0123456789";
	if (ln < 0)
	{
		print_character('-');
		ln = -ln;
		count = 1;
	}
	else
		count = 0;
	if (ln < 10)
	{
		print_character(digits[ln]);
		return (count + 1);
	}
	else
	{
		count = count + print_decimal(ln / 10);
		print_character(digits[ln % 10]);
		return (count + 1);
	}
}

int	print_unsigned(unsigned long n, int base, int uppercase)
{
	int		count;
	char	*digits;

	if (uppercase)
		digits = "0123456789ABCDEF";
	else
		digits = "0123456789abcdef";
	if (n < (unsigned long) base)
	{
		print_character(digits[n]);
		return (1);
	}
	else
	{
		count = print_unsigned(n / base, base, uppercase);
		return (count + print_unsigned(n % base, base, uppercase));
	}
}

int	print_pointer(void *ptr)
{
	unsigned long	address;
	int				count;

	if (ptr == NULL)
	{
		write(1, "(nil)", 5);
		count = 5;
		return (count);
	}
	address = (unsigned long)ptr;
	count = 0;
	count += print_string("0x");
	count += print_unsigned(address, 16, 0);
	return (count);
}
