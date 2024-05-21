/*
** EPITECH PROJECT, 2024
** array_tricks.c
** File description:
** array_tricks.c.
*/
#include <stdint.h>

void get_array_interval(double *dest, const double *src, uint64_t first_bound,
    uint64_t last_bound)
{
    for (uint64_t i = 0; i < last_bound - first_bound; i++)
        dest[i] = src[i + first_bound];
}

void get_diffs(double *dest, const double *src, uint64_t len)
{
    for (uint64_t i = 1; i < len; i++)
        dest[i] = src[i - 1] - src[i];
}
