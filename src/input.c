/*
** EPITECH PROJECT, 2024
** inputs_utils.c
** File description:
** inputs_utils.c.
*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "chart.h"

uint8_t get_line(char *line, uint64_t *new_len, int max_len)
{
    if (fgets(line, max_len, stdin) == NULL)
        return 1;
    *new_len = strlen(line);
    if (*new_len == 0)
        return 1;
    line[*new_len - 1] = '\0';
    (*new_len)--;
    return 0;
}

uint64_t ignore_first_columns(const char *line)
{
    uint64_t offset = 0;

    for (uint8_t i = 0; i < 3; i++)
        offset += strcspn(line + offset, ",");
    return offset;
}

void add_candle(chart_t *chart, uint64_t index)
{
    char line[500];
    char *line_ptr = NULL;
    uint64_t offset;
    uint64_t len;

    get_line(line, &len, sizeof(line));
    offset = ignore_first_columns(line);
    chart->date[index] = strtod(line + offset, &line_ptr);
    offset += strcspn(line + offset, ",") + 1;
    chart->high[index] = strtod(line + offset, &line_ptr);
    offset += strcspn(line + offset, ",") + 1;
    chart->low[index] = strtod(line + offset, &line_ptr);
    offset += strcspn(line + offset, ",") + 1;
    chart->open[index] = strtod(line + offset, &line_ptr);
    offset += strcspn(line + offset, ",") + 1;
    chart->close[index] = strtod(line + offset, &line_ptr);
    offset += strcspn(line + offset, ",") + 1;
    chart->volume[index] = strtod(line + offset, &line_ptr);
}
