/*
** EPITECH PROJECT, 2024
** array.h
** File description:
** array.h.
*/

#pragma once

#include <stdint.h>

typedef struct array_s {
    double *array;
    uint64_t tail;
    uint64_t len;
} array_t;
