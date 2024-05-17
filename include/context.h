/*
** EPITECH PROJECT, 2024
** context.h
** File description:
** context.h.
*/

#pragma once

#include <stdint.h>

#include "prediction.h"

// Number of maximum number of periods into context. 10 by defaults.
#define CTX_LENGHT 10

typedef struct context_data_s {
    signal_t signal;
    double cursor;
    double quantity;
    double price;
    double date;
} context_data_t;

typedef struct context_s {
    context_data_t *contexts;
    uint64_t tail;
    uint64_t len;
    uint8_t loop;
} context_t;

/// Add context data to contexts.
/// @param arr The context array.
/// @param element The context data to add.
void add_to_contexts(context_t *arr, const context_data_t *element);

/// Copy context array ordered.
/// @param src The context array.
/// @param dest The destination array.
/// @param offset The offset (0 by default).
void copy_contexts_ordered(const context_t *src, context_t *dest,
    uint64_t offset);

/// Get the last context data.
/// @param src The context array.
/// @param context_data_t The structure to fill with last context data.
/// @return Success 0, or Failure 1.
uint8_t get_last_context(const context_t *src, context_data_t *context);
