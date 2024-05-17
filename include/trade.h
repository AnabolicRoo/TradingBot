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

// Set the current pair
#define PAIR "USDT_BTC"
#define ASSET_1 "USDT"
#define ASSET_2 "BTC"

// Precision error
#define PRECISION_ERROR 0.9999

// Min buy/sell value
#define MIN_ACTION_VALUE 5

// The limit signal to buy or sell.
#define SIGNAL_LIMIT 0.1

// The minimum difference of cursor with the last same action.
#define CURSOR_DIFF 0.05

// The minimum percentage of diff with the last opposite action.
#define MIN_PRICE_DIFF 0.005

uint8_t trade(const plugins_t *plugins, const settings_t *settings,
    chart_t *chart);
