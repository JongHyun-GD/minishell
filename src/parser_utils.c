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
