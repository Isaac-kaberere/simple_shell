#include "shell.h"

/**
 * _strncpy - Copies a string up to a given number of characters.
 * @dest: The destination string where the copy will be placed.
 * @src: The source string to be copied from.
 * @n: The maximum number of characters to be copied.
 *
 * This function copies at most @n characters from the @src string to the @dest string.
 * If @src is shorter than @n characters, the remaining characters in @dest are filled with
 * null bytes to pad the @dest string.
 *
 * If @src is longer than @n characters, the @dest string is not null-terminated by default
 * (unless @n is greater than the length of @src and the null terminator is included in @n).
 * Ensure that @dest has enough space to accommodate the copy and null terminator if required.
 *
 * Return: A pointer to the resulting destination string (@dest).
 */
`
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strncat - Concatenates two strings.
 * @dest: The destination string where the concatenation will occur.
 * @src: The source string to be appended to the destination.
 * @n: The maximum number of bytes to be used from the source.
 *
 * This function appends the first @n characters of the @src string to the end of
 * the @dest string, overwriting the null terminator at the end of @dest, and then
 * adds a new null terminator. The concatenation is limited to a maximum of @n bytes
 * from the @src string.
 * 
 * The @dest buffer must have enough space to accommodate the concatenated result.
 *
 * Return: A pointer to the resulting concatenated string (same as @dest).
 */

char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 * _strchr - Locates a character in a string.
 * @s: The string to be searched.
 * @c: The character to look for.
 *
 * This function searches for the first occurrence of the character @c in the
 * string @s. If the character is found, a pointer to the memory area containing
 * the character is returned. If the character is not found, the function returns NULL.
 * 
 * Return: A pointer to the memory area @s where the character @c is found,
 *         or NULL if the character is not present in the string.
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

