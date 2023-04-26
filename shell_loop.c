#include "main.h"

/**
 * without_comment - deletes comments from the input to the program.
 *
 * @inptstr: input string
 * Return: input without comments from the program
 */
char *without_comment(char *inptstr)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; inptstr[i]; i++)
	{
		if (inptstr[i] == '#')
		{
			if (i == 0)
			{
				free(inptstr);
				return (NULL);
			}

			if (inptstr[i - 1] == ' ' || inptstr[i - 1] == '\t' || inptstr[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		inptstr = _realloc(inptstr, i, up_to + 1);
		inptstr[up_to] = '\0';
	}

	return (inptstr);
}

/**
 * shell_loop - Loop of shell
 * @datash: data relevant (av, input, args)
 *
 * Return: no return.
 */
void shell_loop(data_shell *datash)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, datash);
			loop = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}