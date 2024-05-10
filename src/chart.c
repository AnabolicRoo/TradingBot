/*
** EPITECH PROJECT, 2024
** chart_utils.c
** File description:
** chart_utils.c.
*/
#include <stdint.h>
#include <malloc.h>
#include <math.h>

#include "chart.h"
#include "settings.h"

static void set_nan_array(double *array, uint64_t len)
{
    for (uint64_t i = 0; i < len; i++)
        array[i] = NAN;
}

void apply_settings_to_chart(chart_t *chart, const settings_t *settings)
{
    chart->len = settings->candles_total;
    chart->fees = settings->transaction_fees_prct;
}

chart_t *create_chart(const settings_t *settings)
{
    uint64_t len = settings->candles_given;
    chart_t *chart = malloc(sizeof(chart_t) + (sizeof(double) *
    NB_OF_CANDLE_PARAMETER * len));
    uint64_t data_off = (uint64_t)((void *)chart + sizeof(chart_t));

    apply_settings_to_chart(chart, settings);
    chart->date = (void *)data_off + (sizeof(double) * (len * DATE_IDX));
    chart->high = (void *)data_off + (sizeof(double) * (len * HIGH_IDX));
    chart->low = (void *)data_off + (sizeof(double) * (len * LOW_IDX));
    chart->open = (void *)data_off + (sizeof(double) * (len * OPEN_IDX));
    chart->close = (void *)data_off + (sizeof(double) * (len * CLOSE_IDX));
    chart->volume = (void *)data_off + (sizeof(double) * (len * VOLUME_IDX));
    set_nan_array((void *)data_off, sizeof(double) * (len *
    NB_OF_CANDLE_PARAMETER));
    return chart;
}

void destroy_chart(chart_t *chart)
{
    free(chart);
}
