/*
** EPITECH PROJECT, 2024
** trade.h
** File description:
** trade.h.
*/

#pragma once

#include <stdint.h>

#include "loader.h"
#include "chart.h"

uint8_t trade(const plugins_t *plugins, const settings_t *settings,
    chart_t *chart);
