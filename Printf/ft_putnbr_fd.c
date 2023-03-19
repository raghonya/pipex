/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:39:00 by raghonya          #+#    #+#             */
/*   Updated: 2023/01/16 14:39:01 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	printf_putnbr_fd(int n, int fd, unsigned int *count)
{
	long int	nb;

	nb = n;
	if (nb < 0)
	{
		printf_putchar_fd ('-', fd);
		nb *= -1;
		*count += 1;
	}
	if (nb > 9)
		printf_putnbr_fd (nb / 10, fd, count);
	printf_putchar_fd ((nb % 10) + 48, fd);
	(*count)++;
}
