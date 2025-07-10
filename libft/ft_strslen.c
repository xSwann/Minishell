
#include "../includes/libft.h"

int  ft_strslen(char **tab)
{
    size_t  i;

    if (!tab)
        return (0);
    i = 0;
    while (tab[i])
        i++;
    return (i);
}
