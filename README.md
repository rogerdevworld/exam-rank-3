# get_next_line & ft_printf

## get_next_line

### Description
`get_next_line` is a function that reads a file descriptor line by line. It returns a string containing a line, including the newline character (`\n`) if present. When the end of the file (EOF) is reached, it returns `NULL`. The function should not have memory leaks and must free all allocated memory when reaching EOF.

### Function Prototype
```c
char *get_next_line(int fd);
```

### Allowed Functions
- `read`
- `malloc`
- `free`

### Implementation *(Header File - Mandatory)*
```c
#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

char *get_next_line(int fd);

#endif
```

### Implementation
```c
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	static int	i = 0, r = 0;
	char		*line;
	int			j = 0;

	if (fd < 0 || BUFFER_SIZE <= 0 || !(line = malloc(10000)))
		return (NULL);
	while (1)
	{
		if (i >= r)
		{
			i = 0;
			r = read(fd, buf, BUFFER_SIZE);
			if (r <= 0)
				break ;
		}
		line[j++] = buf[i++];
		if (line[j - 1] == '\n')
			break ;
	}
	return (j ? (line[j] = 0, line) : (free(line), NULL));
}

```

### Example Usage
```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;
    
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

### Subject Link
[Get Next Line Subject](./get_next_line/subject.en.txt)

---

## ft_printf

### Description
`ft_printf` is a custom implementation of the standard `printf` function. It supports only the following conversions:
- `%s` for strings
- `%d` for decimal integers
- `%x` for hexadecimal (lowercase) integers

### Function Prototype
```c
int ft_printf(const char *, ...);
```

### Allowed Functions
- `write`
- `malloc`
- `free`
- `va_start`, `va_arg`, `va_copy`, `va_end`

### Implementation *(Source File)*
```c
#include <stdarg.h>
#include <unistd.h>

int ft_putstr(char *s)
{
    if (!s)
        return (write(1, "(null)", 6));
    int len = 0;
    while (s[len])
        len++;
    return (write(1, s, len));
}

int ft_putnbr(long n, int base)
{
    char *s = "0123456789abcdef";
    char buf[20];
    int i = 0, len = 0;

    if (n < 0 && base == 10)
        len += write(1, "-", 1), n = -n;
    while (n || i == 0)
        buf[i++] = s[n % base], n /= base;
    while (i--)
        len += write(1, &buf[i], 1);
    return (len);
}

int ft_printf(const char *fmt, ...)
{
    va_list ap;
    int i = 0, len = 0;

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
```

### Example Usage
```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hello %s! The number is %d and in hex: %x\n", "World", 42, 42);
    return 0;
}
```

### Expected Output
```
Hello World! The number is 42 and in hex: 2a
```

### Subject Link
[ft_printf Subject](./ft_printf/subject.en.txt)

---
