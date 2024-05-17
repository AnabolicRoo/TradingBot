/*
** EPITECH PROJECT, 2024
** decision.h
** File description:
** decision.h.
*/

#pragma once

#include <stdint.h>

#include "chart.h"
#include "loader.h"
#include "wallet.h"

/// Function to take decision for the actual chart state and based on context.
/// @param chart The context array.
/// @param i The index of the chart.
/// @param plugins The indicator plugins.
/// @param wallet The wallet.
void take_decision(const chart_t *chart, uint64_t i, const plugins_t *plugins,
    wallet_t *wallet);
