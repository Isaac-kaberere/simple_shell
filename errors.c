#include "shell.h"

/**
 * _eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *ser)
{
	int z = 0;

	if (!ser)
		return;
	while (ser[z] != '\0')
	{
		_eputchar(ser[z]);
		z++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int z;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || z >= WRITE_BUF_SIZE)
	{
		write(2, buf, z);
		z = 0;
	}
	if (c != BUF_FLUSH)
		buf[z++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int z;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || z >= WRITE_BUF_SIZE)
	{
		write(fd, buf, z);
		z = 0;
	}
	if (c != BUF_FLUSH)
		buf[z++] = c;
	return (1);
}


int _putsfd(char *ser, int fd)
{
	int z = 0;

	if (!ser)
		return (0);
	while (*ser)
	{
		z += _putfd(*ser++, fd);
	}
	return (z);
}

