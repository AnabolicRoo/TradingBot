/*
** EPITECH PROJECT, 2024
** prediction.h
** File description:
** prediction.h.
*/

#pragma once

#include <stdint.h>

#define PACKED __attribute__ ((packed))

typedef enum signal_s {
    BUY,
    SELL,
    PASS
} PACKED signal_t;

typedef struct prediction_s {
    signal_t signal;
    double strength; // [0; 1]
} prediction_t;
