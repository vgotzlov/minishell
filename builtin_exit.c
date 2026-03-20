/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnizek <msnizek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:25:26 by msnizek           #+#    #+#             */
/*   Updated: 2026/03/19 13:55:00 by msnizek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *arg)
{
	int		i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (arg[i] == '\0')
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_exit_args(char **argv)
{
	if (!argv[1])
		return (0);
	if (!is_numeric(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(255);
	}
	if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	return (0);
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

static long long	ft_atoll(const char *str, long long *out)
{
	unsigned long long	result;
	int					sign;
	int					i;

	sign = 1;
	result = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	if (!str[i] || !(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (is_overflow(result, str[i] - '0', sign))
			return (0);
		result = (result * 10) + (str[i++] - '0');
	}
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] != '\0')
		return (0);
	return (*out = (long long)result * sign);
}

int	builtin_exit(t_shell *sh, char **argv)
{
	long long	status;

	if (sh->interactive)
		ft_putstr_fd("exit\n", 2);
	if (check_exit_args(argv) != 0)
		return (sh->last_status = 1, 1);
	if (argv[1])
	{
		if (!ft_atoll(argv[1], &status))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			free_shell(sh);
			exit(255);
		}
		status = status % 256;
	}
	else
		status = sh->last_status;
	free_shell(sh);
	exit((int)status);
}
