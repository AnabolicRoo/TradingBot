/*
** EPITECH PROJECT, 2024
** plugin.h
** File description:
** plugin.h.
*/

#pragma once

#include <stdint.h>

#include "prediction.h"
#include "chart.h"
#include "array_tricks.h"

#define PACKED __attribute__ ((packed))

// Enumeration for success or failure.
typedef enum {
    SUCCESS,
    FAILURE,
} PACKED status_t;

/// Function prototype for plugin creation.
/// @param chart The chart (base of prediction).
/// @param prediction The prediction made.
/// @return Success or Failure.
typedef status_t (*plugin_entry_point_t)(const chart_t *chart,
    prediction_t *prediction);
