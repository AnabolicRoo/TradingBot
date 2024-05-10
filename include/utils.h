/*
** EPITECH PROJECT, 2024
** utils.h
** File description:
** utils.h.
*/

#pragma once

#include <stdint.h>

// Input utils

/// Get a new line from stdin.
/// @param line The pointer on a buffer.
/// @param new_len The len of the line read.
/// @param max_len The maximum len we can write in the buffer.
/// @return 0 on success, 1 on failure or EOF.
uint8_t get_line(char *line, uint64_t *new_len, int max_len);
