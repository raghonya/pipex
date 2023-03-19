/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 20:50:51 by raghonya          #+#    #+#             */
/*   Updated: 2023/01/23 20:50:52 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	putuint(unsigned int n, unsigned int *count)
{
	if (n > 9)
		putuint (n / 10, count);
	printf_putchar_fd (n % 10 + 48, STDOUT_FILENO);
	*count += 1;
}

void	putlowhex(unsigned int n, unsigned int *count)
{
	if (n > 15)
		putlowhex (n / 16, count);
	printf_putchar_fd ("0123456789abcdef"[n % 16], STDOUT_FILENO);
	*count += 1;
}

void	putuphex(unsigned int n, unsigned int *count)
{
	if (n > 15)
		putuphex (n / 16, count);
	printf_putchar_fd ("0123456789ABCDEF"[n % 16], STDOUT_FILENO);
	*count += 1;
}

int	check_perc(int i, const char *s, va_list *a, unsigned int *count)
{
	if (s[i + 1] == '%')
	{
		printf_putchar_fd ('%', STDOUT_FILENO);
		*count += 1;
	}
	else if (s[i + 1] == 'c')
	{
		printf_putchar_fd (va_arg(*a, int), STDOUT_FILENO);
		*count += 1;
	}
	else if (s[i + 1] == 's')
		printf_putstr_fd (va_arg(*a, char *), STDOUT_FILENO, count);
	else if (s[i + 1] == 'i' || s[i + 1] == 'd')
		printf_putnbr_fd (va_arg(*a, int), STDOUT_FILENO, count);
	else if (s[i + 1] == 'u')
		putuint (va_arg(*a, unsigned int), count);
	else if (s[i + 1] == 'x')
		putlowhex (va_arg(*a, unsigned int), count);
	else if (s[i + 1] == 'X')
		putuphex (va_arg(*a, unsigned int), count);
	else if (s[i + 1] == 'p')
		checkptr (va_arg(*a, uintptr_t), count);
	else
		return (0);
	return (1);
}

int	ft_printf(const char *s, ...)
{
	int				i;
	unsigned int	count;
	va_list			arg;

	i = 0;
	count = 0;
	va_start (arg, s);
	while (s[i] != 0)
	{
		if (s[i] == '%' && check_perc (i, s, &arg, &count))
			i++;
		else
		{
			printf_putchar_fd (s[i], 1);
			count++;
		}
		i++;
	}
	va_end (arg);
	return (count);
}
