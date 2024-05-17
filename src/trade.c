/*
** EPITECH PROJECT, 2024
** trade.c
** File description:
** trade.c.
*/
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "settings.h"
#include "chart.h"
#include "loader.h"
#include "utils.h"
#include "trade.h"
#include "wallet.h"
#include "context.h"
#include "context_macro.h"

static void print_debug(const wallet_t *wallet)
{
    char line[200];
    uint64_t len = snprintf(line, sizeof(line), "[WALLET]\nASSET 1 : "
    "%lf\nASSET 2 : %lf\n\n", wallet->asset_1_balance,
    wallet->asset_2_balance);

    write(2, line, len);
}

uint8_t trade(const plugins_t *plugins, const settings_t *settings,
    chart_t *chart)
{
    wallet_t wallet = {settings->initial_stack, 0, chart->fees, {}};
    prediction_t prediction;

    plugins->functions[0](chart, &prediction);
    CREATE_CTX_STACK(wallet.context, CTX_LENGHT);
    for (uint64_t i = 0; i < settings->candles_given; i++)
        interpreter(chart, plugins, &wallet);
    while (chart->index < settings->candles_total + 1) {
        interpreter(chart, plugins, &wallet);
        print_debug(&wallet);
    }
    return 0;
}
