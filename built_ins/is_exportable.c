#include "../includes/built_ins.h"

int is_exportable(char *arg)
{
    int i;

    i = 0;
    if (!arg)
        return (0);
    if (!( (arg[0] >= 'a' && arg[0] <= 'z')
        || (arg[0] >= 'A' && arg[0] <= 'Z')
        ||  arg[0] == '_'))
        return 0;

    while (arg[i] && arg[i] != '=')
    {
        if (arg[i] >= 'a' && arg[i] <= 'z')
            i++;
        else if (arg[i] >= 'A' && arg[i] <= 'Z')
            i++;
        else if (arg[i] >= '0' && arg[i] <= '9')
            i++;
        else if (arg[i] == '_')
            i++;
        else
            return (0);
    }
    return (1);
}
