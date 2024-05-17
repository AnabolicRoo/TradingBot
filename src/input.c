/*
** EPITECH PROJECT, 2024
** inputs_utils.c
** File description:
** inputs_utils.c.
*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "chart.h"
#include "wallet.h"
#include "trade.h"
#include "decision.h"

uint8_t get_line(char *line, uint64_t *new_len, int max_len)
{
    if (fgets(line, max_len, stdin) == NULL)
        return 1;
    *new_len = strlen(line);
    if (*new_len == 0)
        return 1;
    line[*new_len - 1] = '\0';
    (*new_len)--;
    return 0;
}

static uint64_t get_offset_to_pair(const char *line)
{
    uint64_t offset = 0;

    for (uint8_t i = 0; i < 3; i++)
        offset += strcspn(line + offset, ", ") + 1;
    while (1) {
        if (memcmp(line + offset, PAIR, sizeof(PAIR) - 1) == 0) {
            offset += strcspn(line + offset, ",") + 1;
            break;
        }
        offset += strcspn(line + offset, ";") + 1;
    }
    return offset;
}

static void add_candle(chart_t *chart, uint64_t index, const char *line)
{
    char *line_ptr = NULL;
    uint64_t offset;

    offset = get_offset_to_pair(line);
    chart->date[index] = strtod(line + offset, &line_ptr);
    offset += strcspn(line + offset, ",") + 1;
    chart->high[index] = strtod(line + offset, &line_ptr);
    offset += strcspn(line + offset, ",") + 1;
    chart->low[index] = strtod(line + offset, &line_ptr);
    offset += strcspn(line + offset, ",") + 1;
    chart->open[index] = strtod(line + offset, &line_ptr);
    offset += strcspn(line + offset, ",") + 1;
    chart->close[index] = strtod(line + offset, &line_ptr);
    offset += strcspn(line + offset, ",") + 1;
    chart->volume[index] = strtod(line + offset, &line_ptr);
}

static void update_wallet(wallet_t *wallet, const char *line)
{
    uint64_t offset = 0;

    for (uint8_t i = 0; i < 2; i++) {
        if (memcmp(line, ASSET_1, sizeof(ASSET_1) - 1) == 0)
            wallet->asset_1_balance = strtod(line + offset + sizeof(ASSET_1),
            NULL);
        if (memcmp(line, ASSET_2, sizeof(ASSET_2) - 1) == 0)
            wallet->asset_2_balance = strtod(line + offset + sizeof(ASSET_2),
            NULL);
        offset += strcspn(line, ",") + 1;
    }
}

static void update_wallet_command(wallet_t *wallet, const char *line,
    uint64_t len)
{
    const char *ptr = line;
    uint64_t offset = 0;

    while (1) {
        if (offset >= len)
            return;
        if (strncmp(ptr, PAIR, sizeof(PAIR) - 1) == 0)
            return update_wallet(wallet, line);
        offset += strcspn(ptr, ",") + 1;
    }
}

void interpreter(chart_t *chart, const plugins_t *plugins, wallet_t *wallet)
{
    char line[500];
    uint64_t len = 0;

    get_line(line, &len, sizeof(line));
    if (strncmp(line, "update game next_candles ", 25) == 0) {
        chart->index++;
        return add_candle(chart, chart->index, line);
    }
    if (strncmp(line, "update game stacks ", 19) == 0)
        return update_wallet_command(wallet, line + 19, len);
    if (strncmp(line, "action order ", 13) == 0)
        take_decision(chart, chart->index, plugins, wallet);
}
