
#include "../includes/libft.h"

char    *ft_itoa(int nbr)
{
    int len;
    int tmp;
    char *result;
    int i;
    int signe;

    signe = 0;
    len = 0;
    i = 0;
    if (nbr == -2147483648)
        return ("-2147483648");
    if (nbr < 0)
    {
        nbr = nbr * -1;
        signe = 1;
        len = 1;
    }
    tmp = nbr;
    while(tmp >= 10)
    {
        tmp = tmp / 10;
        len++;
    }
    result = malloc(sizeof(char) * len + 1);
    result[len + 1] = '\0';
    if (signe == 1)
        result[0] = '-';
    while (len >= signe)
    {
        result[len] = nbr % 10 + '0';
        nbr = nbr / 10;
        len--;
    }
    return (result);
}
