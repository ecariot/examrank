/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcariot <emcariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 18:45:17 by emcariot          #+#    #+#             */
/*   Updated: 2022/01/10 14:19:24 by emcariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


//STRING

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

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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
	return (ft_strlen(str));
}

int	ft_printchar(char c)
{
	write(1, &c, 1);
	return (1);
}

//NUMBER

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	long long i;

	i = nb;
	if (nb < 0)
	{
		ft_putchar('-');
		i = i * -1;
	}
	if (i > 9)
		ft_putnbr(i / 10);
	ft_putchar(i % 10 + '0');
}

static int	ft_int_len(long nb)
{
	int len;

	len = 0;
	if (nb == 0)
		len = 1;
	if (nb < 0)
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
	long n;
	int len;

	n = nb;
	len = ft_int_len(n);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (n == 0)
		str[0] = 48;
	else if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[len] = (n % 10) + 48;
		n = n / 10;
		len--;
	}
	return(str);
}

int	ft_print_nbr(int n)
{
	int len;
	char *num;

	len = 0;
	num = ft_itoa(n);
	len = ft_print_string(num);
	free(num);
	return (len);
}

//HEXA

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

void	ft_put_hex(unsigned int num, const char str)
{
	if (num >= 16)
	{
		ft_put_hex(num / 16, str);
		ft_put_hex(num % 16, str);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
		{
			if (str == 'x')
				ft_putchar_fd((num - 10 + 'a'), 1);
		}
	}
}

int	ft_print_hexa(unsigned int num, const char str)
{
	if (num == 0)
		return (write(1, "0", 1));
	else
		ft_put_hex(num, str);
	return (ft_hex_len(num));
}

//MAIN

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != c)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return (str);
}

int	ft_ana_args(va_list tprint, const char arg)
{
	int print_return;

	print_return = 0;
	if (arg == 's')
		print_return += ft_print_string(va_arg(tprint, char *));
	else if (arg == 'i')
		print_return += ft_print_nbr(va_arg(tprint, int));
	else if (arg == 'x')
		print_return += ft_print_hexa(va_arg(tprint, unsigned int), arg);
	return (print_return);
}

int	ft_ana_args(va_list tprint, const char *ar)
{
	int print_return;

	print_return = 0;
	if (arg == 's')
		print_return += ft_putstring(va_arg(tprint, char *))
}

int	ft_printf(const char *str, ...)
{
	va_list tprint;
	int i;
	int print_return;

	va_start(tprint, str);
	i = 0;
	print_return = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (ft_strchr("xis", str[i + 1]))
				print_return += ft_ana_args(tprint, str[i + 1]);
			i += 2;
		}
		else 
		{
			print_return += ft_printchar(str[i]);
			i++;
		}
	}
	va_end(tprint);
	return (print_return);
}

#include <stdio.h>
int main ()
{
	printf("%s\n", "hello");
	ft_printf("%s\n", "hello");
	printf("%i\n", 42);
	ft_printf("%i\n", 42);
	printf("%x\n", 42);
	ft_printf("%x\n", 42);
	return (0);
}