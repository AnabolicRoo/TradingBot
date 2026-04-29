/*
** EPITECH PROJECT, 2024
** plugin_test.c
** File description:
** plugin_test.c.
*/
#include "plugin.h"

#include "array_tricks.h"

// 13 TOP
// 7 BETTER
#define PERIOD 7

static double get_average_gain(const double *array, uint64_t len)
{
    double sum = 0;

    for (uint64_t i = 0; i < len; i++)
        sum += (array[i] > 0) ? array[i] : 0;
    return sum / len;
}

static double get_average_loss(const double *array, uint64_t len)
{
    double sum = 0;

    for (uint64_t i = 0; i < len; i++)
        sum += (array[i] < 0) ? array[i] : 0;
    return sum / len;
}

status_t plugin_entry_point(const chart_t *chart, prediction_t *prediction)
{
    double deltas[PERIOD + 1] = {};
    double gain_avg;
    double loss_avg;
    double rs;
    double rsi;

    if (chart->index <= PERIOD)
        return FAILURE;
    get_diffs(deltas, &chart->close[chart->index - PERIOD], PERIOD + 1);
    gain_avg = get_average_gain(&deltas[1], PERIOD);
    loss_avg = get_average_loss(&deltas[1], PERIOD) * -1;
    rs = gain_avg / loss_avg;
    rsi = 100 - (100 / (1 + rs));
    if (rsi > 70) {
        prediction->signal = SELL;
        prediction->strength = 1;
    }
    if (rsi < 30) {
        prediction->signal = BUY;
        prediction->strength = 1;
    }
    return SUCCESS;
}
