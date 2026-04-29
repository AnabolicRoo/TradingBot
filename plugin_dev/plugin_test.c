/*
** EPITECH PROJECT, 2024
** plugin_test.c
** File description:
** plugin_test.c.
*/
#include "plugin.h"

#include <stdlib.h>

status_t plugin_entry_point(const chart_t *chart, prediction_t *prediction)
{
    prediction->signal = rand() % 3;
    prediction->strength = 1;
    return SUCCESS;
}
