/*
** EPITECH PROJECT, 2024
** utils.h
** File description:
** utils.h.
*/

#pragma once

#include <stdint.h>

#include "chart.h"

// Input utils

// Get macro size.
#define MACRO_SIZE(macro) sizeof(macro) - 1

/// Get a new line from stdin.
/// @param line The pointer on a buffer.
/// @param new_len The len of the line read.
/// @param max_len The maximum len we can write in the buffer.
/// @return 0 on success, 1 on failure or EOF.
uint8_t get_line(char *line, uint64_t *new_len, int max_len);

/// Get offset ignoring the first columns.
/// @param line The pointer on a buffer.
/// @return The offset.
uint64_t ignore_first_columns(const char *line);

/// Add a candle to the chart (at index).
/// @param chart The chart structure.
/// @param index The index of the candle.
void add_candle(chart_t *chart, uint64_t index);
