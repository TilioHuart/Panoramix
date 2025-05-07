/*
** EPITECH PROJECT, 2025
** panoramix
** File description:
** parse_flag.c
*/

#include "macros.h"
#include "village.h"
#include <ctype.h>
#include <pthread.h>
#include <semaphore.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int print_error(char *str)
{
    if (str == NULL)
        return FAILURE;
    write(2, str, strlen(str));
    return FAILURE;
}

static void set_village(char const *argv[], village_t *village)
{
    village->nb_villagers = atoi(argv[1]);
    village->pot_size = atoi(argv[2]);
    village->nb_fights = atoi(argv[3]);
    village->nb_refills = atoi(argv[4]);
    village->thread_villager =
        malloc(sizeof(pthread_t) * village->nb_villagers);
    sem_init(&village->pot, 0, village->pot_size);
    village->druid_call = SLEEPY;
    village->villager_id = 0;
    village->nb_villager_sleeping = 0;
    village->has_fill = 0;
    pthread_mutex_init(&village->lock, NULL);
    for (int i = 0; i < village->pot_size; i += 1) {
        sem_post(&village->pot);
    }
    village->nb_serving_left = village->pot_size;
}

static int handle_negative_number(char const *argv[], size_t *i)
{
    for (size_t y = 0; argv[*i][y] != '\0'; y++)
        if (!isdigit(argv[*i][y]))
            return print_error("USAGE: ./panoramix <nb_villagers> <pot_size> "
                "<nb_fights> <nb_refills>\n");
    return SUCCESS;
}

static int handle_flag_error(char const *argv[])
{
    for (size_t i = 1; argv[i] != NULL; i++) {
        if (atoi(argv[i]) < 0)
            return print_error(
                "USAGE: ./panoramix <nb_villagers> <pot_size> "
                "<nb_fights> <nb_refills>\nValues must be >0.\n");
        if (handle_negative_number(argv, &i) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}

int parse_flag(int const argc, char const *argv[], village_t *village)
{
    if (argc != 5 || argv == NULL || argv[1] == NULL || argv[2] == NULL ||
        argv[3] == NULL || argv[4] == NULL) {
        return FAILURE;
    }
    if (handle_flag_error(argv) == FAILURE) {
        return FAILURE;
    }
    set_village(argv, village);
    if (village->nb_villagers == 0)
        return FAILURE;
    return SUCCESS;
}
