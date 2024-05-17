/*
** EPITECH PROJECT, 2024
** array_macro.h
** File description:
** array_macro.h.
*/

#pragma once

#include <math.h>

#define CREATE_ARRAY(arr, size) \
({ \
    if ((size) > STACK_LIMIT) { \
        arr.array = malloc((size) * sizeof(double)); \
        arr.area_of_memory = HEAP; \
    } else { \
        arr.array = alloca((size) * sizeof(double)); \
        arr.area_of_memory = STACK; \
    } \
    memset(arr.array, 0, (size) * sizeof(double)); \
    for (uint64_t i = 0; i < size; i++) \
        arr.array[i] = NAN; \
    arr.tail = 0; \
    arr.len = (size); \
})

#define CREATE_ARRAY_STACK(arr, size) \
({ \
    arr.array = alloca((size) * sizeof(double)); \
    arr.area_of_memory = STACK; \
    memset(arr.array, 0, (size) * sizeof(double)); \
    for (uint64_t i = 0; i < size; i++) \
        arr.array[i] = NAN; \
    arr.tail = 0; \
    arr.len = (size); \
})

