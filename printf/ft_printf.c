/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:15:16 by aahadji           #+#    #+#             */
/*   Updated: 2025/02/07 18:44:09 by aahadji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	add_number(char temp, va_list *args, int w_len)
{
	int	lenght;

	lenght = 0;
	if (temp == 'd' || temp == 'i')
		lenght += ft_putnbr_fd((int)va_arg(*args, int), 1);
	else if (temp == 'u')
		lenght += ft_putnbr_u_fd((unsigned int)va_arg(*args, unsigned int), 1);
	else if (temp == 'X')
		lenght += ft_put_hex_fd((unsigned int)va_arg(*args, unsigned int), 1);
	else if (temp == 'x')
		lenght += ft_put_hex_fd((unsigned int)va_arg(*args, unsigned int), 0);
	else if (temp)
	{
		lenght += ft_putchar_fd('%', 1);
		lenght += ft_putchar_fd(temp, 1);
	}
	else if (w_len > 0)
		lenght += ft_putchar_fd('%', 1);
	return (lenght);
}

static int	add_char(char temp, va_list *args, int w_len)
{
	int		lenght;
	char	ch;

	lenght = 0;
	if (temp == '%')
		lenght += ft_putchar_fd('%', 1);
	else if (temp == 'c')
	{
		ch = (char)va_arg(*args, int);
		lenght += ft_putchar_fd(ch, 1);
	}
	else if (temp == 's')
		lenght += ft_putstr_fd((char *)va_arg(*args, char *), 1);
	else if (temp == 'p')
		lenght += ft_put_address((void *)va_arg(*args, void *));
	else
		lenght += add_number(temp, args, w_len);
	return (lenght);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	i;
	int		lenght;

	va_start(args, format);
	lenght = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] != '%')
		{
			if (ft_putchar_fd(format[i], 1) > 0)
				lenght++;
			else
				return (-1);
		}
		else if (format[i] == '%')
			lenght += add_char(format[++i], &args, lenght);
		i++;
	}
	va_end(args);
	return (lenght);
}

/*/#include <stdio.h>
int	main(void)
{
	int i = NULL;
	char *test= NULL;
	printf("%i",ft_printf("%p",test));
	printf("%i",ft_printf("%p",test));

	return (0);
}*/
