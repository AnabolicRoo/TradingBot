/*
** EPITECH PROJECT, 2024
** chart.h
** File description:
** chart.h.
*/

#pragma once

#include <stdint.h>

#include "settings.h"

// Structures.

typedef struct chart_s {
    char pair[10];
    uint64_t len;
    double fees;
    double *date;
    double *high;
    double *low;
    double *open;
    double *close;
    double *volume;
} chart_t;

enum CandleIndexes {
    DATE_IDX,
    HIGH_IDX,
    LOW_IDX,
    OPEN_IDX,
    CLOSE_IDX,
    VOLUME_IDX,
    NB_OF_CANDLE_PARAMETER
};

// Function prototypes.

/// Create a new chart (and init arrays to NAN).
/// @param settings The settings required to create the chart.
/// @return The allocated chart.
chart_t *create_chart(const settings_t *settings);

/// Destroy a chart.
/// @param pair The pair name (10 bytes max and fully initialized to zero).
/// @param len The maximum number of candle.
/// @return The allocated chart.
void destroy_chart(chart_t *chart);
