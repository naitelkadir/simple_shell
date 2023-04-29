#include "main.h"

/**
 * num_to_string - ...
 * @num: ...
 * @s: ...
 * @base: ...
 * Return: ...
 */
void num_to_string(long num, char *s, int base)
{
	int i = 0, c = 0;
	long m = num;
	char alpha[] = {"0123456789abcdef"};
	
	if (m == 0)
	{
		s[i++] = '0';
	}
	if (s[0] == '-')
	{
		c = 1;
	}
	while (m)
	{
		if (m < 0)
		{
			s[i++] = alpha[-(m % base)];
		}
		else
		{
			s[i++] = alpha[m % base];
		}
		m /= base;
	}
	if (c)
	{
		s[i++] = '-';
	}
	s[i] = '\0';
	str_reverse(s);
}

/**
 * myAtoi - ...
 * @s: ...
 * Return: ...
 */
int myAtoi(char *s)
{
	int sign = 1;
	unsigned int num = 0;
	
	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
		{
			sign *= -1;
		}
		if (*s == '+')
		{
			sign *= +1;
		}
		s++;
	}
	while ('0' <= *s && *s <= '9' && *s != '\0')
	{
		num = (num * 10) + (*s - '0');
		s++;
	}
	return (num * sign);
}

/**
 * counter - ...
 * @s: ...
 * @caract: ...
 * Return: ...
 */
int counter(char *s, char *caract)
{
	int i = 0, c = 0;
	
	for (; s[i]; i++)
	{
		if (s[i] == caract[0])
		{
			c++;
		}
	}
	return (c);
}
