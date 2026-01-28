/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:19:20 by oztozdem          #+#    #+#             */
/*   Updated: 2025/04/29 16:57:01 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_putchar_len(char c, int *len, int fd)
{
	write(fd, &c, 1);
	(*len)++;
}

static void	ft_putstr_len(char *str, int *len, int fd)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(fd, "(null)", 6);
		*len = *len + 6;
	}
	else
	{
		while (str[i])
		{
			ft_putchar_len(str[i], len, fd);
			i++;
		}
	}
}

static void	ft_putnbr_len(int n, int *len, int fd)
{
	unsigned int	b;

	if (n < 0)
	{
		ft_putchar_len('-', len, fd);
		n = n * -1;
		b = n;
	}
	else
		b = n;
	if (b >= 10)
	{
		ft_putnbr_len(b / 10, len, fd);
		ft_putchar_len(b % 10 + '0', len, fd);
	}
	else
		ft_putchar_len(b + '0', len, fd);
}

static void	ft_printf_check(int fd, char c, va_list *args, int *len)
{
	if (c == 'c')
		ft_putchar_len(va_arg(*args, int), len, fd);
	else if (c == 's')
		ft_putstr_len(va_arg(*args, char *), len, fd);
	else if (c == 'd')
		ft_putnbr_len(va_arg(*args, int), len, fd);
}

/* dprintf: printf avec un fd */
int	ft_dprintf(int fd, const char *str, ...)
{
	int		i;
	int		len;
	va_list	args;

	i = 0;
	len = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[++i] == '\0')
				return (va_end(args), -1);
			ft_printf_check(fd, str[i++], &args, &len);
		}
		else
		{
			ft_putchar_len((char)str[i], &len, fd);
			i++;
		}
	}
	va_end(args);
	return (len);
}
