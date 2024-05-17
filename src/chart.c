/*
** EPITECH PROJECT, 2024
** chart_utils.c
** File description:
** chart_utils.c.
*/
#include <stdint.h>
#include <malloc.h>
#include <string.h>

#include "chart.h"
#include "settings.h"
#include "trade.h"

void apply_settings_to_chart(chart_t *chart, const settings_t *settings)
{
    memcpy(chart->pair, PAIR, sizeof(PAIR));
    chart->len = settings->candles_total + 1;
    chart->fees = settings->transaction_fees_prct / 100;
    chart->index = 0;
}

chart_t *create_chart(const settings_t *settings)
{
    uint64_t len = settings->candles_total + 1;
    chart_t *chart = malloc(sizeof(chart_t));

    apply_settings_to_chart(chart, settings);
    chart->date = malloc(sizeof(double) * len);
    chart->high = malloc(sizeof(double) * len);
    chart->low = malloc(sizeof(double) * len);
    chart->open = malloc(sizeof(double) * len);
    chart->close = malloc(sizeof(double) * len);
    chart->volume = malloc(sizeof(double) * len);
    return chart;
}

void destroy_chart(chart_t *chart)
{
    free(chart);
}
