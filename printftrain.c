/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printftrain.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:16:35 by emcariot          #+#    #+#             */
/*   Updated: 2022/01/13 13:21:13 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>


//string

int	ft_print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	ft_print_string(char *str)
{
	if (!str)
	{
		ft_putstr("(null)");
		return (6);
	}
	else
		ft_putstr(str);
	return (ft_strlen(str));;
}

//nbr

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	long i;

	i = nb;
	if (i < 0)
	{
		i = i * -1;
		ft_putchar('-');
	}
	while (i > 9)
		ft_putnbr(i / 10);
	ft_putchar(i % 10 + '0');
}

int	ft_int_len(long nb)
{
	int len;

	len = 0;
	if  (nb == 0)
		len = 1;
	else if (nb < 0)
	{
		nb = nb * -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char *ft_itoa(int nb)
{
	char *str;
	int len;
	long i;

	i = nb;
	len = ft_int_len(i);
	str = malloc(sizeof(char) * (len + 1));
	str[len--] = '\0';
	if (!str)
		return (NULL);
	if (i == 0)
		str[0] = 48;
	if (i < 0)
	{
		str[0] = '-';
		i = i * -1;
	}
	while (i > 0)
	{
		str[len] = i % 10 + 48;
		i = i / 10;
		len++;
	}
	return (str);
}

int	ft_print_int(int nb)
{
	char *num;
	int len;

	num = ft_itoa(nb);
	len = ft_print_string(num);
	free(num);
	return (len);
}

//hex

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int	ft_hex_len(unsigned int num)
{
	int len;

	len = 0;
	while (num != 0)
	{
		num = num / 16;
		len++;
	}
	return (len);
}

void	ft_put_hex(unsigned int nb, const char c)
{
	if (nb >= 16)
	{
		ft_put_hex(nb / 16, c);
		ft_put_hex(nb % 16, c);
	}
	else
	{
		if (nb <= 9)
			ft_putchar_fd((nb + 48), 1);
		else
		{
			if (c == 'x')
				ft_putchar_fd((nb - 10 + 'a'), 1);
		}	
	}
}

int	ft_print_hex(unsigned int num, const char c)
{
	if (num == 0)
		return(write(1, "0", 1));
	else
		ft_put_hex(num, c);
	return (ft_hex_len(num));
}

//main

char *ft_strchr(const char *s, int c)
{
	char *str;

	str = (char *)s;
	while (*str != c)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return (str);
}

int	ft_ana_arg(va_list tprint, const char arg)
{
	int print_return;

	print_return = 0;
	if (arg == 's')
		print_return += ft_print_string(va_arg(tprint, char *));
	else if (arg == 'i')
		print_return += ft_print_int(va_arg(tprint, int));
	else if (arg == 'x')
		print_return += ft_print_hex(va_arg(tprint, unsigned int), arg);
	return (print_return);
}

int	ft_prinf(const char *str, ...)
{
	int print_return;
	int i;
	va_list tprint;

	print_return = 0;
	i = 0;
	va_start(tprint, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (ft_strchr("xis", str[i + 1]))
				print_return += ft_ana_arg(tprint, str[i + 1]);
			i += 2;
		}
		else
		{
			print_return += ft_print_char(str[i]);
		}
		i++;
	}
	va_end(tprint);
	return (print_return);
}