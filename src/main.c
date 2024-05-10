/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** Main file
*/
#include "chart.h"

int main(void)
{
    settings_t settings = {};
    chart_t *chart;

    if (get_settings(&settings) == 1)
        return 84;
    chart = create_chart(&settings);
    destroy_chart(chart);
    return 0;
}
