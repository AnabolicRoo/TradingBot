/*
** EPITECH PROJECT, 2024
** inputs_utils.c
** File description:
** inputs_utils.c.
*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint8_t get_line(char *line, uint64_t *new_len, int max_len)
{
    if (fgets(line, max_len, stdin) == NULL)
        return 1;
    *new_len = strlen(line);
    if (*new_len == 0)
        return 1;
    line[*new_len - 1] = '\0';
    (*new_len)--;
    return 0;
}
