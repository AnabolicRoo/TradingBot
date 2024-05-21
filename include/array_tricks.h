/*
** EPITECH PROJECT, 2024
** array_tricks.h
** File description:
** array_tricks.h.
*/

#pragma once

#include <stdint.h>

/// Get the data interval from a source array.
/// @param dest The destination array.
/// @param src The source array.
/// @param first_bound The first bound of the interval.
/// @param last_bound The last bound of the interval.
void get_array_interval(double *dest, const double *src, uint64_t first_bound,
    uint64_t last_bound);

/// Get the array of differences.
/// @param dest The destination array.
/// @param src The source array.
/// @param len The number of elements to effectuate diffs.
void get_diffs(double *dest, const double *src, uint64_t len);
