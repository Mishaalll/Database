#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

int mystrcmp(const char* s1, const char* s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return *s1 - *s2;
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

void mystrcpy(char* dest, const char* src)
{
    while (*src)
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}



int myatoi(const char *str) 
{
    int res = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') 
    {
        sign = -1;
        i++;
    }

    for (; str[i] != '\0'; i++) 
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            res = res * 10 + (str[i] - '0');
        }
        else
        {
            break;
        }
    }

    return res * sign;
}



int mystrlen(const char *str) 
{
    int len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}
