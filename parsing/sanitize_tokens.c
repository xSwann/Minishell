#include "../includes/parsing.h"
#include "../includes/built_ins.h"

void remove_quote(char **str, int first, int last)
{
    int i;
    int j;
    int len;
    char *new;

    i = 0;
    j = 0;
    len = ft_strlen(*str);
    new = malloc(sizeof(char) * (len - 2 + 1)); 
    if (!new)
        return ;
    while (j < first)
        new[i++] = (*str)[j++];
    j++;
    while (j < last)
        new[i++] = (*str)[j++];
    j++;
    while ((*str)[j])
        new[i++] = (*str)[j++];
    new[i] = '\0';
    free(*str);
    *str = new;
}

void    replace_expanded_value(char **str, char *expanded, int len)
{
    int i;
    int j;
    int k;
    char *new;
    
    i = 0;
    j = 0;
    k = 0;
    new = malloc(sizeof(char) * len + 1);
    (void)str;
    (void)(expanded);
    while ((*str)[i] && (*str)[i] != '$')
    {
        new[j] = (*str)[i];
        j++;
        i++;
    }
    i++;
    if ((*str)[i] != '?')
    {
        while((*str)[i] && (ft_isalpha((*str)[i])))
            i++;
    }
    else
        i++;
    while (expanded[k])
    {
        new[j] = expanded[k];
        j++;
        k++;
    }
    while((*str)[i])
    {
        new[j] = (*str)[i];
        j++;
        i++;
    }
    new[j] = '\0';
    *str = new;
}

void    erase_expand(char **str, int len)
{
    int i;
    int j;
    int k;
    char *new;
    
    i = 0;
    j = 0;
    k = 0;
    new = malloc(sizeof(char) * len + 1);
    while ((*str)[i] && (*str)[i] != '$')
    {
        new[j] = (*str)[i];
        j++;
        i++;
    }
    i++;
    while((*str)[i] && ft_isalpha((*str)[i]))
        i++;
    while((*str)[i])
    {
        new[j] = (*str)[i];
        j++;
        i++;
    }
    new[j] = '\0';
    *str = new;
}

void    expand_var(char **str, t_env **env)
{
    int i;
    int len;
    int start;
    char *expanded;
    char *to_expand;

    i = 0;
    len = 0;
    start = 0;
    to_expand = NULL;
    while ((*str)[i] && (*str)[i] != '$')
        i++;
    start = i;
    i++;
    while ((*str)[i] && ft_isalpha((*str)[i]))
        i++;
    if ((*str)[i] == '?')
    {
        to_expand = ft_strdup("EXIT_CODE");
        len = 1;
    }
    else
    {
        to_expand = ft_substr(*str, start + 1, i - (start + 1));
        len = ft_strlen(to_expand);
    }
    expanded = get_env(*env, to_expand);
    if (!expanded)
        erase_expand(str, ft_strlen(*str) - ft_strlen(to_expand));
    else
        replace_expanded_value(str, expanded, ft_strlen(*str) - len + ft_strlen(expanded));
}


void sanitize_tokens(char **tokens, t_env **env)
{
    int  i;
    int j;
    int first;
    char quote;
    int len;

    i = 0;
    while (tokens[i])
    {
        j = 0;
        quote = '\0';
        len = ft_strlen(tokens[i]);
        while (tokens[i][j])
        {
            if (tokens[i][j] == '$' && len != 1 && (ft_isalpha(tokens[i][j+1]) || tokens[i][j+1] == '?')
             && (quote == '\0' || quote == '"'))
            {
                expand_var(&tokens[i], env);
                continue ;
            }
            else if (quote == '\0' && is_quote(tokens[i][j]))
            {
                quote = tokens[i][j++];
                continue ;
            }
            else if (quote != '\0' && tokens[i][j] == quote)
            {
                quote = '\0';
                j++;
                continue ;
            }
            j++;
        }

        j     = 0;
        quote = '\0';
        while (tokens[i][j])
        {
            if (quote == '\0' && is_quote(tokens[i][j]))
            {
                quote = tokens[i][j];
                first = j;
                j++;
                continue;
            }
            if (quote != '\0' && tokens[i][j] == quote)
            {
                remove_quote(&tokens[i], first, j);
                quote = '\0';
                j     = first;
                continue;
            }
            j++;
        }
        i++;
    }
}
