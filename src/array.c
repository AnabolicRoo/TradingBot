/*
** EPITECH PROJECT, 2024
** array_utils.c
** File description:
** array_utils.c.
*/
#include <stdint.h>
#include <math.h>

#include "array.h"

void add_to_array(array_t *arr, double element)
{
    arr->array[arr->tail] = element;
    arr->tail = (arr->tail + 1) % arr->len;
}

void copy_array_ordered(const array_t *src, array_t *dest, uint64_t offset)
{
    uint64_t i_src = (src->tail + offset) % src->len;

    if (isnan(src->array[i_src]))
        i_src = 0;
    for (uint64_t i = 0; i < src->len; i++) {
        dest->array[i] = src->array[i_src];
        i_src = (i_src + 1) % src->len;
        if (i_src == src->tail)
            return;
    }
}

void apply_fct_to_array(array_t *array, double (*fct)(double element))
{
    for (uint64_t i = 0; i < array->len; i++)
        array->array[i] = fct(array->array[i]);
}
