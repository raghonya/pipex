/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putpointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 20:55:35 by raghonya          #+#    #+#             */
/*   Updated: 2023/01/23 20:55:40 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	putlowhex_ptr(uintptr_t n, unsigned int *count)
{
	if (n > 15)
		putlowhex_ptr (n / 16, count);
	printf_putchar_fd ("0123456789abcdef"[n % 16], STDOUT_FILENO);
	*count += 1;
}

void	checkptr(uintptr_t n, unsigned int *count)
{
	write (STDOUT_FILENO, "0x", 2);
	*count += 2;
	putlowhex_ptr (n, count);
}
