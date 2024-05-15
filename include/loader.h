/*
** EPITECH PROJECT, 2024
** loader.h
** File description:
** loader.h.
*/

#pragma once

#include <stdint.h>

#include "plugin.h"

#define PLUGIN_PATH "plugins/"
#define PLUGIN_ALIAS "trade_plugin_"
#define PLUGIN_FUNCTION_NAME "plugin_entry_point"
#define PLUGIN_MAX_NAME_LEN 50

typedef struct plugins_s {
    uint64_t len;
    plugin_entry_point_t *functions;
    void **dyn_objs;
} plugins_t;

/// Load the plugins.
/// @param plugins The plugin structure to fill.
/// @return Success (0) or Failure (1).
uint8_t load_plugins(plugins_t *plugins);

/// Free the plugins.
/// @param plugins The plugin structure to destroy.
/// @return Success (0) or Failure (1).
void destroy_plugins(const plugins_t *plugins);
