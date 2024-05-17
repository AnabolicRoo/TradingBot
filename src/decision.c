/*
** EPITECH PROJECT, 2024
** decision.c
** File description:
** decision.c.
*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "chart.h"
#include "loader.h"
#include "wallet.h"
#include "trade.h"

static uint8_t send_buy_request(const char *pair, double quantity)
{
    char request[200] = {};
    uint64_t len = snprintf(request, sizeof(request), "buy %s %lf\n",
    pair, quantity);

    write(1, request, len);
    return 0;
}

static uint8_t send_sell_request(const char *pair, double quantity)
{
    char request[200] = {};
    uint64_t len = snprintf(request, sizeof(request), "sell %s %lf\n",
    pair, quantity);

    write(1, request, len);
    return 0;
}

static uint8_t send_pass_request(void)
{
    write(1, "pass\n", 5);
    return 1;
}

double get_decision_cursor(const chart_t *chart, const plugins_t *plugins)
{
    uint64_t count = 0;
    double cursor = 0;
    prediction_t prediction;

    for (uint64_t i = 0; i < plugins->len; i++) {
        memset(&prediction, 0, sizeof(prediction_t));
        if (plugins->functions[i](chart, &prediction) == SUCCESS &&
        prediction.signal != PASS) {
            cursor += (prediction.signal == BUY) ? (1 * prediction.strength)
            : 0;
            cursor += (prediction.signal == SELL) ? (-1 * prediction
            .strength) : 0;
            count++;
        }
    }
    if (count == 0)
        return 0;
    cursor /= (double)count;
    return cursor;
}

signal_t get_signal_from_cursor(double cursor)
{
    signal_t decision = PASS;

    decision = (cursor > 0 + SIGNAL_LIMIT) ? BUY : decision;
    decision = (cursor < 0 - SIGNAL_LIMIT) ? SELL : decision;
    return decision;
}

static uint8_t buy_decision(const wallet_t *wallet,
    const context_data_t *actual_ctx)
{
    context_data_t last_decision;

    if (get_last_context(&wallet->context, &last_decision) == 1)
        return 0;
    if ((actual_ctx->price * (1 + MIN_PRICE_DIFF)) < last_decision.price)
        return 0;
    return 1;
}

static uint8_t buy_action(const chart_t *chart, context_data_t *ctx,
    wallet_t *wallet)
{
    ctx->quantity = convert_percent_to_quantity(wallet,
    chart->close[chart->index], SECOND_ASSET, ctx->cursor);
    if (ctx->quantity == 0 || buy_decision(wallet, ctx) == 1)
        return send_pass_request();
    convert_asset_percentage(wallet, chart->close[chart->index],
    SECOND_ASSET, ctx->cursor);
    send_buy_request(chart->pair, ctx->quantity);
    return 0;
}

static uint8_t sell_decision(const wallet_t *wallet,
    const context_data_t *actual_ctx)
{
    context_data_t last_decision;

    if (get_last_context(&wallet->context, &last_decision) == 1)
        return 1;
    if ((actual_ctx->price) > last_decision.price * (1 + MIN_PRICE_DIFF))
        return 0;
    return 1;
}

static uint8_t sell_action(const chart_t *chart, context_data_t *ctx,
    wallet_t *wallet)
{
    ctx->quantity = convert_percent_to_quantity(wallet,
    chart->close[chart->index], FIRST_ASSET, ctx->cursor);
    if (ctx->quantity == 0 || sell_decision(wallet, ctx) == 1)
        return send_pass_request();
    convert_asset_percentage(wallet, chart->close[chart->index], FIRST_ASSET,
    ctx->cursor);
    send_sell_request(chart->pair, ctx->quantity);
    return 0;
}

void take_decision(const chart_t *chart, uint64_t i, const plugins_t *plugins,
    wallet_t *wallet)
{
    double cursor = get_decision_cursor(chart, plugins);
    signal_t signal = get_signal_from_cursor(cursor);
    context_data_t ctx = {signal, ((cursor < 0) ? cursor * -1 : cursor), 0,
    chart->close[i], chart->date[i]};
    uint8_t action;

    switch (ctx.signal) {
        case BUY:
            action = buy_action(chart, &ctx, wallet);
            break;
        case SELL:
            action = sell_action(chart, &ctx, wallet);
            break;
        default:
            action = send_pass_request();
    }
    return (action == 0) ? add_to_contexts(&wallet->context, &ctx) : 0;
}
