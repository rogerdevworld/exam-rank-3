#include <unistd.h>
#include <stdarg.h>

int	ft_putstr(char *s)
{
	if (!s)
		return (write(1, "(null)", 6));
	int len = 0;
	while (s[len])
		len++;
	return (write(1, s, len));
}

int	ft_putnbr(long n, int base)
{
	char	*s = "0123456789abcdef";
	char	buf[20];
	int		i = 0, len = 0;

	if (n < 0)
		len += write(1, "-", 1), n = -n;
	while (n || i == 0)
		buf[i++] = s[n % base], n /= base;
	while (i--)
		len += write(1, &buf[i], 1);
	return (len);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		i = 0, len = 0;

	va_start(ap, fmt);
	while (fmt[i])
	{
		if (fmt[i] == '%' && fmt[i + 1])
		{
			i++;
			if (fmt[i] == 's')
				len += ft_putstr(va_arg(ap, char *));
			else if (fmt[i] == 'd')
				len += ft_putnbr(va_arg(ap, int), 10);
			else if (fmt[i] == 'x')
				len += ft_putnbr((unsigned)va_arg(ap, unsigned), 16);
		}
		else
			len += write(1, &fmt[i], 1);
		i++;
	}
	va_end(ap);
	return (len);
}