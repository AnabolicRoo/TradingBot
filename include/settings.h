/*
** EPITECH PROJECT, 2024
** settings.h
** File description:
** settings.h.
*/

#pragma once

#include <stdint.h>

// Game settings structure.
typedef struct settings_s {
    char players_name[20];
    char bot_name[20];
    uint64_t timebank;
    uint64_t time_per_move;
    uint64_t candle_interval;
    char candle_format[100];
    uint64_t candles_total;
    uint64_t candles_given;
    double initial_stack;
    double transaction_fees_prct;
} settings_t;

// Commands.
#define SETTINGS "settings"

// Settings.
#define SETTING_OFFSET sizeof(SETTINGS) + 1
#define PLAYER_NAMES "player_names"
#define BOT_NAME "your_bot"
#define TIMEBANK "timebank"
#define TIME_PER_MOVE "time_per_move"
#define CANDLE_INTERVAL "candle_interval"
#define CANDLE_FORMAT "candle_format"
#define CANDLES_TOTAL "candles_total"
#define CANDLES_GIVEN "candles_given"
#define INITIAL_STACK "initial_stack"
#define TRANSACTION_FEE_PRCT "transaction_fee_percent"
#define NB_OF_SETTINGS 10

// Function prototypes.
uint8_t get_settings(settings_t *settings);
