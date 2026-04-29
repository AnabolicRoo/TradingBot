/*
** EPITECH PROJECT, 2024
** plugin_ichimoku.c
** File description:
** plugin_ichimoku.c.
*/
#include "plugin.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "array_tricks.h"

#define TENKAN_PARAMETER 9
#define KIJUN_PARAMETER 26
#define SSB_PARAMETER 52
#define DISPLACEMENT 26

static double *tenkan;
static double *kijun;
static double *ssa;
static double *ssb;

static double calculate_tenkan(const chart_t *chart)
{
    double max_value = get_max(&chart->high[chart->index -
    TENKAN_PARAMETER + 1], TENKAN_PARAMETER);
    double min_value = get_min(&chart->low[chart->index -
    TENKAN_PARAMETER + 1], TENKAN_PARAMETER);

    return (max_value + min_value) / 2;
}

static double calculate_kijun(const chart_t *chart)
{
    double max_value = get_max(&chart->high[chart->index -
    KIJUN_PARAMETER + 1], KIJUN_PARAMETER);
    double min_value = get_min(&chart->low[chart->index -
    KIJUN_PARAMETER + 1], KIJUN_PARAMETER);

    return (max_value + min_value) / 2;
}

static double calculate_ssb(const chart_t *chart)
{
    double max_value = get_max(&chart->high[chart->index -
    SSB_PARAMETER + 1], SSB_PARAMETER);
    double min_value = get_min(&chart->low[chart->index -
    SSB_PARAMETER + 1], SSB_PARAMETER);

    return (max_value + min_value) / 2;
}

static void allocate_memory(uint64_t len)
{
    tenkan = calloc(len, sizeof(double));
    kijun = calloc(len, sizeof(double));
    ssa = calloc(len + DISPLACEMENT, sizeof(double));
    ssb = calloc(len + DISPLACEMENT, sizeof(double));
}

static uint8_t have_cross(const chart_t *chart)
{
    if ((tenkan[chart->index - 1] - kijun[chart->index - 1] > 0 &&
    tenkan[chart->index] - kijun[chart->index] < 0) ||
    (tenkan[chart->index - 1] - kijun[chart->index - 1] < 0 &&
    tenkan[chart->index] - kijun[chart->index] > 0))
        return 0;
    return 1;
}

static double max(double value1, double value2)
{
    return (value1 > value2) ? value1 : value2;
}

static double min(double value1, double value2)
{
    return (value1 < value2) ? value1 : value2;
}

static status_t predict_up(const chart_t *chart, prediction_t *prediction,
    double max_cloud, double min_cloud)
{
    if ((tenkan[chart->index] + kijun[chart->index]) / 2 > max_cloud) {
        prediction->signal = BUY;
        prediction->strength = 1;
        return SUCCESS;
    }
    if ((tenkan[chart->index] + kijun[chart->index]) / 2 < max_cloud &&
        (tenkan[chart->index] + kijun[chart->index]) / 2 > min_cloud) {
        prediction->signal = BUY;
        prediction->strength = 0.75;
        return SUCCESS;
    }
    if ((tenkan[chart->index] + kijun[chart->index]) / 2 < min_cloud) {
        prediction->signal = BUY;
        prediction->strength = 0.6;
        return SUCCESS;
    }
    return FAILURE;
}

static status_t predict_down(const chart_t *chart, prediction_t *prediction,
    double max_cloud, double min_cloud)
{
    if ((tenkan[chart->index] + kijun[chart->index]) / 2 > max_cloud) {
        prediction->signal = SELL;
        prediction->strength = 1;
        return SUCCESS;
    }
    if ((tenkan[chart->index] + kijun[chart->index]) / 2 < max_cloud &&
        (tenkan[chart->index] + kijun[chart->index]) / 2 > min_cloud) {
        prediction->signal = SELL;
        prediction->strength = 0.75;
        return SUCCESS;
    }
    if ((tenkan[chart->index] + kijun[chart->index]) / 2 < min_cloud) {
        prediction->signal = SELL;
        prediction->strength = 0.6;
        return SUCCESS;
    }
    return FAILURE;
}

static status_t predict(const chart_t *chart, prediction_t *prediction)
{
    double max_cloud = max(ssa[chart->index], ssb[chart->index]);
    double min_cloud = min(ssa[chart->index], ssb[chart->index]);

    if (have_cross(chart) == 1)
        return FAILURE;
    if (chart->close[chart->index] > max_cloud &&
    tenkan[chart->index] > kijun[chart->index] && chart->close[chart->index
    - DISPLACEMENT + 1] > chart->close[chart->index])
        return predict_up(chart, prediction, max_cloud, min_cloud);
    if (chart->close[chart->index] < min_cloud &&
    tenkan[chart->index] < kijun[chart->index] && chart->close[chart->index
    - DISPLACEMENT + 1] < chart->close[chart->index])
        return predict_down(chart, prediction, max_cloud, min_cloud);
    return FAILURE;
}

status_t plugin_entry_point(const chart_t *chart, prediction_t *prediction)
{
    static uint64_t count = 0;

    if (count == 0)
        allocate_memory(chart->len);
    count++;
    tenkan[chart->index] = calculate_tenkan(chart);
    kijun[chart->index] = calculate_kijun(chart);
    ssa[chart->index + DISPLACEMENT] =
        (tenkan[chart->index] + kijun[chart->index]) / 2;
    ssb[chart->index + DISPLACEMENT] = calculate_ssb(chart);
    if (count < SSB_PARAMETER)
        return FAILURE;
    return predict(chart, prediction);
}
