/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** Main file
*/
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#include "settings.h"
#include "chart.h"
#include "loader.h"
#include "trade.h"

int main(void)
{
    settings_t settings = {};
    chart_t *chart;
    plugins_t plugins = {};

    srand((uint32_t)time(NULL));
    if (get_settings(&settings) == 1)
        return 84;
    if (load_plugins(&plugins) == 1) {
        write(2, "No plugin loaded.\n", 18);
        return 84;
    }
    chart = create_chart(&settings);
    trade(&plugins, &settings, chart);
    destroy_chart(chart);
    destroy_plugins(&plugins);
    return 0;
}
