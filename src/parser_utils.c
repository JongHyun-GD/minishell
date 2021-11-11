#include "../includes/parser.h"

int     get_num_of_c(char *s, char c)
{
        int             index;
        int             count;

        count = 0;
        index = -1;
        while (s[++index])
        {
                if (s[index] == c)
                        count++;
        }
        return (count);
}

int     check_l_type(char *s)
{
        if (*s == '|')
                return (LTYPE_PIPE);
        if (*s == ';')
                return (LTYPE_SEMI_COLON);
        if (*s == '<')
                return (LTYPE_REDIRECT);
        if (*s == '>')
                return (LTYPE_REDIRECT);
        if (*s == '<' && *(s + 1) == '<')
                return (LTYPE_REDIRECT);
        if (*s == '>' && *(s + 1) == '>')
                return (LTYPE_REDIRECT);
        return (0);
}
