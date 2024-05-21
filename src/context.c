/*
** EPITECH PROJECT, 2024
** context.c
** File description:
** context.c.
*/
#include <stdint.h>
#include <string.h>

#include "context.h"

void add_to_contexts(context_t *arr, const context_data_t *element)
{
    arr->contexts[arr->tail] = *element;
    arr->tail = (arr->tail + 1) % arr->len;
}

uint64_t copy_contexts_ordered(const context_t *src, context_data_t *dest,
    uint64_t offset)
{
    uint64_t i_src = (src->tail + offset) % src->len;
    uint64_t nb_of_copy = 0;

    if (src->loop == 0)
        i_src = 0;
    for (uint64_t i = 0; i < src->len; i++) {
        dest[i] = src->contexts[i_src];
        i_src = (i_src + 1) % src->len;
        if (i_src == src->tail)
            return nb_of_copy;
        nb_of_copy++;
    }
    return nb_of_copy;
}

uint8_t get_last_context(const context_t *src, context_data_t *context)
{
    if (src->loop == 0 && src->tail == 0)
        return 1;
    memcpy(context, &src->contexts[(src->tail - 1) % src->len],
    sizeof(context_data_t));
    return 0;
}
