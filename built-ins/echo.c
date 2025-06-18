//le int param sert si l'option -n est requise, dans ce cas la, le param devra etre different de 0

void    echo(char **str, int param)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (param == 0)
            printf("%s\n", str[i]);
        else
            printf("%s", str[i]);
        i++;
    }
}