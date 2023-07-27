#include "main.h"
/**
 * handle_print - Prints an argument based on its type.
 *
 * This function takes a formatted string (@fmt) and a list of arguments (@list)
 * and prints the corresponding argument based on its type. The function uses
 * the provided buffer array (@buffer) to handle the print operation. It also
 * calculates the active flags (@flags), width (@width), precision (@precision),
 * and size (@size) specified in the formatted string.
 *
 * Syntax:
 * int handle_print(const char *fmt, va_list list, int ind, char buffer[],
 *                  int flags, int width, int precision, int size);
 *
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: Index.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Width specifier.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: 1 or 2, depending on the success of the print operation.
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unknow_len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}

