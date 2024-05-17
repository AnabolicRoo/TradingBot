/*
** EPITECH PROJECT, 2024
** utils.h
** File description:
** utils.h.
*/

#pragma once

#include <stdint.h>

#include "chart.h"
#include "wallet.h"
#include "loader.h"

// Input utils

// Get macro size.
#define MACRO_SIZE(macro) sizeof(macro) - 1

/// Get a new line from stdin.
/// @param line The pointer on a buffer.
/// @param new_len The len of the line read.
/// @param max_len The maximum len we can write in the buffer.
/// @return 0 on success, 1 on failure or EOF.
uint8_t get_line(char *line, uint64_t *new_len, int max_len);

/// Interpret input of the program.
/// @param chart The chart structure.
/// @param plugins The loaded plugins.
/// @param wallet The wallet structure.
/// @return The action to realize.
void interpreter(chart_t *chart, const plugins_t *plugins, wallet_t *wallet);
