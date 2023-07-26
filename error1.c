#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - Prints an error message.
 * @info: A structure containing parameter and return information.
 * @estr: A string containing the specified error type.
 *
 * This function is responsible for printing an error message related to the given
 * error type, which is specified in the @estr parameter. The error message is output
 * based on the context of the program's execution or any encountered errors.
 * 
 * The function takes the @info argument, which is a structure containing information
 * related to function parameters and return values, although it may not be directly
 * used in this implementation.
 *
 * Return: 0 if no specific numbers are in the error message string,
 *         or a converted number if relevant to the error message.
 *         Returns -1 on error or failure to print the message.
 */

void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - Prints a decimal (integer) number in base 10.
 * @input: The input integer to be printed.
 * @fd: The file descriptor to write the output to.
 *
 * This function is responsible for printing the decimal (integer) number @input
 * in base 10 to the specified file descriptor @fd. The function uses the standard
 * base 10 representation for printing the number.
 *
 * Return: The number of characters printed on success, or -1 on failure.
 */

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - Converts a number to a string representation.
 * @num: The number to convert.
 * @base: The base for the conversion (e.g., decimal, binary, hexadecimal).
 * @flags: Additional argument flags (if applicable).
 *
 * This function is responsible for converting the integer @num to a string representation,
 * using the specified @base. The function takes into account the base value to perform the
 * appropriate conversion (e.g., base 10 for decimal, base 2 for binary, base 16 for hexadecimal).
 * The result is returned as a dynamically allocated string.
 *
 * If needed, the function may take additional @flags to customize the conversion behavior
 * (e.g., for formatting options or special handling). In this implementation, the @flags
 * argument is optional and may not be used.
 *
 * Return: A dynamically allocated string representing the converted number.
 *         The caller is responsible for freeing the allocated memory when done using the string.
 */

char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - Replaces the first instance of '#' with '\0'.
 * @buf: The address of the string to modify.
 *
 * This function is responsible for searching the input string pointed to by @buf
 * for the first occurrence of the '#' character. When the '#' character is found,
 * it is replaced with the null terminator '\0', effectively removing the remaining
 * content from that point onward.
 * 
 * The function modifies the input string in-place, terminating it at the first '#' found.
 * It does not remove '#' characters occurring after the first occurrence.
 * 
 * Return: Always 0
 */

void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

