#include "../includes/parsing.h"

void	symbol_handler(int *i, char *line)
{
	if (is_double_symbol(line, *i))
		*i += 2;
	else
		(*i)++;
}
