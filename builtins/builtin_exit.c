/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:25:26 by msnizek           #+#    #+#             */
/*   Updated: 2026/03/23 14:14:37 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_quotes(char *str)
{
	int	i;
	int	j;

	if (!str)
		return ;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

static int	is_overflow(unsigned long long res, int next_digit, int sign)
{
	if (res > 922337203685477580ULL)
		return (1);
	if (res == 922337203685477580ULL)
	{
		if (sign == 1 && next_digit > 7)
			return (1);
		if (sign == -1 && next_digit > 8)
			return (1);
	}
	return (0);
}
static int	parse_atoll(const char *str, long long *out)
{
	unsigned long long	result = 0;
	int					sign = 1;
	int					i = 0;

	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-') sign = -1;
		i++;
	}
	if (!str[i]) return (0);
	while (str[i])
	{
		if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) 
			break;
		if (str[i] < '0' || str[i] > '9')
			return (0);
		if (is_overflow(result, str[i] - '0', sign))
			return (0);
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	while (str[i])
	{
		if (str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13)) return (0);
		i++;
	}
	*out = (long long)result * sign;
	return (1);
}
int	builtin_exit(t_shell *sh, char **argv)
{
	long long	status;

	if (sh->interactive)
		ft_putstr_fd("exit\n", 2);
	if (!argv[1])
		exit((unsigned char)sh->last_status);
	remove_quotes(argv[1]);
	if (!parse_atoll(argv[1], &status))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(2);
	}
	if (argv[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		sh->last_status = 1;
		return (1);
	}
	exit((unsigned char)status);
}
