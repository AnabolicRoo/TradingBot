/*
** EPITECH PROJECT, 2024
** settings_utils.c
** File description:
** settings_utils.c.
*/
#include <stdlib.h>
#include <string.h>

#include "trade.h"
#include "utils.h"
#include "settings.h"

static uint8_t set_str_setting(char *dest, const char *offset_2,
    uint64_t limit_size)
{
    uint64_t len = strlen(offset_2);

    if (len > limit_size)
        return 1;
    memcpy(dest, offset_2, len);
    return 0;
}

static uint8_t set_uint_setting(uint64_t *dest, const char *offset_2)
{
    *dest = strtol(offset_2, NULL, 10);
    return 0;
}

static uint8_t set_double_setting(double *dest, const char *offset_2)
{
    *dest = strtod(offset_2, NULL);
    return 0;
}

static uint8_t set_setting_2(settings_t *settings, const char *offset_1)
{
    if (strncmp(offset_1, CANDLE_FORMAT, sizeof(CANDLE_FORMAT)) == 0)
        return set_str_setting(settings->candle_format, offset_1 + sizeof
        (CANDLE_FORMAT) + 1, sizeof(settings->candle_format));
    if (strncmp(offset_1, CANDLES_TOTAL, sizeof(CANDLES_TOTAL)) == 0)
        return set_uint_setting(&settings->candles_total, offset_1 + sizeof
        (CANDLES_TOTAL) + 1);
    if (strncmp(offset_1, CANDLES_GIVEN, sizeof(CANDLES_GIVEN)) == 0)
        return set_uint_setting(&settings->candles_given, offset_1 + sizeof
        (CANDLES_GIVEN) + 1);
    if (strncmp(offset_1, INITIAL_STACK, sizeof(INITIAL_STACK)) == 0)
        return set_double_setting(&settings->initial_stack, offset_1 + sizeof
        (INITIAL_STACK) + 1);
    if (strncmp(offset_1, TRANSACTION_FEE_PRCT, sizeof(TRANSACTION_FEE_PRCT))
    == 0)
        return set_double_setting(&settings->transaction_fees_prct, offset_1 +
        sizeof(TRANSACTION_FEE_PRCT) + 1);
    return 1;
}

static uint8_t set_setting(settings_t *settings, const char *line)
{
    const char *offset = line + SETTING_OFFSET;

    if (strncmp(line, SETTINGS, sizeof(SETTINGS)) != 0)
        return 1;
    if (strncmp(offset, PLAYER_NAMES, sizeof(PLAYER_NAMES)) == 0)
        return set_str_setting(settings->players_name, offset +
        sizeof(PLAYER_NAMES) + 1, sizeof(settings->players_name));
    if (strncmp(offset, BOT_NAME, sizeof(BOT_NAME)) == 0)
        return set_str_setting(settings->bot_name, offset + sizeof(BOT_NAME)
        + 1, sizeof(settings->bot_name));
    if (strncmp(offset, TIMEBANK, sizeof(TIMEBANK)) == 0)
        return set_uint_setting(&settings->timebank, offset + sizeof
        (TIMEBANK) + 1);
    if (strncmp(offset, TIME_PER_MOVE, sizeof(TIME_PER_MOVE)) == 0)
        return set_uint_setting(&settings->time_per_move, offset + sizeof
        (TIME_PER_MOVE) + 1);
    if (strncmp(offset, CANDLE_INTERVAL, sizeof(CANDLE_INTERVAL)) == 0)
        return set_uint_setting(&settings->candle_interval, offset + sizeof
        (CANDLE_INTERVAL) + 1);
    return set_setting_2(settings, offset);
}

uint8_t get_settings(settings_t *settings)
{
    char line[500] = {};
    uint64_t len;

    for (uint64_t i = 0; i < NB_OF_SETTINGS; i++) {
        get_line(line, &len, sizeof(line));
        if (len <= sizeof(SETTINGS))
            return 1;
        set_setting(settings, line);
    }
    return 0;
}
