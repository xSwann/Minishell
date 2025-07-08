#include "../includes/parsing.h"

int sanitize_tokens(int nb_of_token, char **tokens, t_env **env)
{
    int i;
    int j;
    int start;
    int end;
    int single;
    int dubble;

    i = 0;
    j = 0;
    start = 0;
    end = 0;
    single = 0;
    dubble = 0;
    while(tokens[i])
    {
        while(tokens[i][j])
        {
            if (tokens[i][j] == 39 && !dubble)
            {
                single = single * -1;
                if (!single)
                    start = i;
                else
                    tokens[i][j] = skip_quote(tokens);
            }
            else if (tokens[i][j] == '"' && !single)
            {
                dubble = dubble * -1;
                if (!dubble)
                    start = i;
                else
                    end = i;
            }
            j++;
        }
        i++;
    }
}