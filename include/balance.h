/*
** EPITECH PROJECT, 2024
** balance.h
** File description:
** balance.h.
*/

#pragma once

// Structures.

typedef struct balance_s {
    double asset_1_balance; // USDT
    double asset_2_balance; // BTC
    double fees_pct;
} balance_t;

enum Asset {
    FIRST_ASSET,
    SECOND_ASSET
};

// Function prototypes.

/// Convert an asset to the other.
/// @param balance The balance to modify.
/// @param conversion Asset 1 for asset 2.
/// @param direction The direction of the conversion (for
// example SECOND_ASSET to convert quantity of asset 1 to asset 2).
/// @param quantity The quantity to convert.
/// @return The allocated chart.
uint8_t convert_asset_quantity(balance_t *balance,
    double conversion, uint8_t direction, double quantity);

/// Convert an asset to the other.
/// @param balance The balance to modify.
/// @param direction The direction of the conversion (for
// example SECOND_ASSET to convert percentage of asset 1 to asset 2).
/// @param percentage The percentage to convert.
/// @return The allocated chart.
uint8_t convert_asset_percentage(balance_t *balance, uint8_t direction,
    double percentage);
