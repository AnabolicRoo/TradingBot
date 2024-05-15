/*
** EPITECH PROJECT, 2024
** loader.c
** File description:
** loader.c.
*/
#include <stdint.h>
#include <malloc.h>
#include <dirent.h>
#include <string.h>
#include <dlfcn.h>

#include "loader.h"
#include "utils.h"

static uint64_t get_nb_of_file(void)
{
    uint64_t count = 0;
    DIR *dp = opendir(PLUGIN_PATH);
    const struct dirent *entry;

    if (dp == NULL)
        return 0;
    entry = readdir(dp);
    while (entry) {
        count++;
        entry = readdir(dp);
    }
    closedir(dp);
    return count;
}

void loop_on_files(DIR *dp, plugins_t *plugins, uint64_t *i)
{
    char path[sizeof(PLUGIN_PATH) + PLUGIN_MAX_NAME_LEN] = {PLUGIN_PATH};
    uint64_t filename_len;
    const struct dirent *entry = readdir(dp);

    while (entry) {
        if (strncmp(entry->d_name, PLUGIN_ALIAS, MACRO_SIZE(PLUGIN_ALIAS)) ==
            0) {
            filename_len = strlen(entry->d_name);
            memcpy(path + MACRO_SIZE(PLUGIN_PATH), entry->d_name,
            filename_len);
            path[MACRO_SIZE(PLUGIN_PATH) + filename_len] = '\0';
            plugins->dyn_objs[*i] = dlopen(path, RTLD_LAZY);
            plugins->functions[*i] = dlsym(plugins->dyn_objs[*i],
            PLUGIN_FUNCTION_NAME);
            (*i)++;
        }
        entry = readdir(dp);
    }
}

uint8_t load_plugins(plugins_t *plugins)
{
    uint64_t count = get_nb_of_file();
    DIR *dp = opendir(PLUGIN_PATH);
    uint64_t i = 0;

    if (count == 0 || dp == NULL)
        return 1;
    plugins->functions = malloc(sizeof(void *) * count);
    plugins->dyn_objs = malloc(sizeof(void *) * count);
    loop_on_files(dp, plugins, &i);
    plugins->len = i;
    closedir(dp);
    return 0;
}

void destroy_plugins(const plugins_t *plugins)
{
    free(plugins->functions);
    for (uint64_t i = 0; i < plugins->len; i++)
        dlclose(plugins->dyn_objs[i]);
    free(plugins->dyn_objs);
}
