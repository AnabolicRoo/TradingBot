/*
** EPITECH PROJECT, 2024
** array_macro.h
** File description:
** array_macro.h.
*/

#pragma once

#include "context.h"

#include <alloca.h>

#define CREATE_CTX_STACK(arr, size) \
({ \
    arr.contexts = alloca((size) * sizeof(context_data_t)); \
    memset(arr.contexts, 0, (size) * sizeof(context_data_t)); \
    arr.tail = 0; \
    arr.len = (size); \
    arr.loop = 0; \
})
