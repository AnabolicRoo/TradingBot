/*
** EPITECH PROJECT, 2024
** balance.c
** File description:
** balance.c.
*/
#include <stdint.h>

#include "balance.h"

uint8_t convert_asset_quantity(balance_t *balance, double conversion,
    uint8_t direction, double quantity)
{
    double ttc = quantity * (1 + (balance->fees_pct * 0.01));
    double converted = ((direction == SECOND_ASSET) ? (1 / conversion)
    : conversion) * ttc;

    balance->asset_1_balance -= ((direction == SECOND_ASSET) * ttc);
    balance->asset_2_balance -= ((direction == FIRST_ASSET) * ttc);
    balance->asset_1_balance += ((direction == FIRST_ASSET) * converted);
    balance->asset_2_balance += ((direction == SECOND_ASSET) * converted);
    return 0;
}

uint8_t convert_asset_percentage(balance_t *balance, uint8_t direction,
    double percentage)
{
    double ttc = 1 - (percentage + balance->fees_pct);
    double to_add = 1 + percentage;

    balance->asset_1_balance *= (direction == SECOND_ASSET) * ttc;
    balance->asset_2_balance *= (direction == FIRST_ASSET) * ttc;
    balance->asset_1_balance *= (direction == FIRST_ASSET) * to_add;
    balance->asset_2_balance *= (direction == SECOND_ASSET) * to_add;
    return 0;
}
