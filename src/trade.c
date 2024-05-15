/*
** EPITECH PROJECT, 2024
** trade.c
** File description:
** trade.c.
*/
#include "settings.h"
#include "chart.h"
#include "loader.h"
#include "utils.h"

#include <stdint.h>

uint8_t trade(const plugins_t *plugins, const settings_t *settings,
    chart_t *chart)
{
    for (uint64_t i = 0; i < settings->candles_given; i++)
        add_candle(chart, i);
    return 0;
}
