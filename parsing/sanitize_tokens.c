#include "../includes/parsing.h"
#include "../includes/built_ins.h"

static void strip_quotes(char **p)
{
    char *old = *p;
    size_t len = ft_strlen(old);
    char *new = malloc(len + 1);
    char q = '\0';
    size_t r = 0, w = 0;

    if (!new)
        return;
    while (r < len)
    {
        if (old[r] == '"' || old[r] == '\'')
        {
            if (q == '\0')
                q = old[r++];
            else if (old[r] == q)
            {
                q = '\0';
                r++;
            }
            else
                new[w++] = old[r++];
        }
        else
            new[w++] = old[r++];
    }
    new[w] = '\0';
    free(old);
    *p = new;
}

void replace_expanded_value(char **str, char *expanded, int len)
{
    int i = 0, j = 0, k = 0;
    int newlen = len + ft_strlen(expanded);
    char *new = malloc(newlen + 1);
    if (!new)
        return;
    while ((*str)[i] && (*str)[i] != '$')
        new[j++] = (*str)[i++];
    i++;
    if ((*str)[i] == '?')
        i++;
    else
        while ((*str)[i] && ft_isalnum((*str)[i]))
            i++;
    while (expanded[k])
        new[j++] = expanded[k++];
    while ((*str)[i])
        new[j++] = (*str)[i++];
    new[j] = '\0';
    free(*str);
    *str = new;
}

void erase_expand(char **str, int len)
{
    int i = 0, j = 0;
    char *new = malloc(len + 1);
    if (!new)
        return;
    while ((*str)[i] && (*str)[i] != '$')
        new[j++] = (*str)[i++];
    i++; // skip '$'
    if (ft_isdigit((*str)[i]))
        i = 2;
    else
        while ((*str)[i] && ft_isalnum((*str)[i]))
            i++;
    while ((*str)[i])
        new[j++] = (*str)[i++];
    new[j] = '\0';
    free(*str);
    *str = new;
}

void clear_space(char *str)
{
    int i = 0, j = 0;
    int in_word = 0;
    while (str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;
    while (str[i])
    {
        if (str[i] != ' ' && str[i] != '\t')
        {
            str[j++] = str[i++];
            in_word = 1;
        }
        else
        {
            if (in_word)
            {
                str[j++] = ' ';
                in_word = 0;
            }
            while (str[i] && (str[i] == ' ' || str[i] == '\t'))
                i++;
        }
    }
    if (j > 0 && str[j - 1] == ' ')
        j--;
    str[j] = '\0';
}

void expand_var(char **str, t_env *env)
{
    int i = 0, start = 0, len = 0;
    char *to_expand;
    char *expanded;
    while ((*str)[i] && (*str)[i] != '$')
        i++;
    start = i++;
    while ((*str)[i] && ft_isalnum((*str)[i]))
        i++;
    if ((*str)[start + 1] == '?')
    {
        to_expand = ft_strdup("EXIT_CODE");
        len = 1;
    }
    else if (ft_isdigit((*str)[start + 1]) || is_quote((*str)[start + 1]))
    {
        to_expand = ft_strdup("9");
        len = 1;
    }
    else
    {
        to_expand = ft_substr(*str, start + 1, i - (start + 1));
        len = ft_strlen(to_expand);
    }
    expanded = get_env(env, to_expand);
    free(to_expand);
    if (!expanded)
        erase_expand(str, ft_strlen(*str) - len);
    else
	{
        replace_expanded_value(str, expanded, ft_strlen(*str) - len);
	}
	free(expanded);
}

void sanitize_tokens(t_tab *tokens, t_env *env)
{
    int i = 0;
    while (tokens[i].str)
    {
        int j = 0;
        char quote = '\0';
        while (tokens[i].str[j])
        {
            if (tokens[i].str[j] == '$'
                && (quote == '\0' || quote == '"')
                && tokens[i].str[j + 1]
                && (ft_isalnum(tokens[i].str[j + 1])
                    || tokens[i].str[j + 1] == '?'
                    || (is_quote(tokens[i].str[j + 1]) && quote == '\0')))
            {
                expand_var(&tokens[i].str, env);
                if (quote == '\0')
                    clear_space(tokens[i].str);
                j = 0;
                continue;
            }
            if (quote == '\0' && is_quote(tokens[i].str[j]))
            {
                quote = tokens[i].str[j++];
                continue;
            }
            if (quote != '\0' && tokens[i].str[j] == quote)
            {
                quote = '\0';
                j++;
                continue;
            }
            j++;
        }
        strip_quotes(&tokens[i].str);
        i++;
    }
}