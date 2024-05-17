/*
** EPITECH PROJECT, 2024
** balance.c
** File description:
** balance.c.
*/
#include <stdint.h>

#include "wallet.h"
#include "trade.h"

double convert_asset_1_to_2(wallet_t *balance, double conversion,
    double quantity)
{
    double asset_2_as_1 = quantity * (1 / conversion);
    double asset_2_as_1_with_taxes = asset_2_as_1 * (1 - balance->fees_pct);

    balance->asset_1_balance -= quantity;
    balance->asset_2_balance += asset_2_as_1_with_taxes;
    return asset_2_as_1_with_taxes;
}

double convert_asset_2_to_1(wallet_t *balance, double conversion,
    double quantity)
{
    double asset_1_as_2 = quantity * conversion;
    double asset_1_as_2_with_taxes = asset_1_as_2 * (1 - balance->fees_pct);

    balance->asset_1_balance += asset_1_as_2_with_taxes;
    balance->asset_2_balance -= quantity;
    return asset_1_as_2_with_taxes;
}

double convert_asset_quantity(wallet_t *balance, double conversion,
    uint8_t direction, double quantity)
{
    if (direction == SECOND_ASSET)
        return convert_asset_1_to_2(balance, conversion, quantity);
    if (direction == FIRST_ASSET)
        return convert_asset_2_to_1(balance, conversion, quantity);
    return 0;
}

double convert_asset_percentage(wallet_t *balance, double conversion,
    uint8_t direction, double percentage)
{
    if (direction == SECOND_ASSET)
        return convert_asset_1_to_2(balance, conversion,
        balance->asset_1_balance * percentage * PRECISION_ERROR);
    if (direction == FIRST_ASSET)
        return convert_asset_2_to_1(balance, conversion,
        balance->asset_2_balance * percentage * PRECISION_ERROR);
    return 0;
}

double convert_percent_to_quantity(const wallet_t *balance, double conversion,
    uint8_t direction, double percentage)
{
    if (direction == SECOND_ASSET && balance->asset_1_balance >
    MIN_ACTION_VALUE)
        return (((balance->asset_1_balance * PRECISION_ERROR) * percentage) *
        (1 / conversion));
    if (direction == FIRST_ASSET && balance->asset_2_balance > ((1 /
    conversion) * 5))
        return ((balance->asset_2_balance * PRECISION_ERROR) * percentage);
    return 0;
}
