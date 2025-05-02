/*
** EPITECH PROJECT, 2025
** panoramix
** File description:
** panoramix.c
*/

#include "druid.h"
#include "macros.h"
#include "parser.h"
#include "village.h"
#include "villager.h"
#include <pthread.h>
#include <semaphore.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int wake_up_village(village_t *village)
{
    int ret = 0;

    ret = pthread_create(
        &village->thread_druid, NULL, &call_druid, (void *)village);
    if (!ret) {
        for (int i = 0; i < village->nb_villagers; i += 1) {
            ret = pthread_create(&village->thread_villager[i], NULL,
                &call_villager, (void *)village);
        }
    }
    pthread_join(village->thread_druid, NULL);
    for (int i = 0; i < village->nb_villagers; i += 1) {
        pthread_join(village->thread_villager[i], NULL);
    }
    return SUCCESS;
}

static void destroy_village(village_t *village)
{
    pthread_mutex_destroy(&village->lock);
    sem_destroy(&village->pot);
    if (village != NULL) {
        if (village->thread_villager != NULL)
            free(village->thread_villager);
        free(village);
    }
}

int panoramix(int const argc, char const *argv[])
{
    village_t *village = (village_t *)malloc(sizeof(village_t));

    if (parse_flag(argc, argv, village) == FAILURE)
        return EPITECH_FAILURE;
    wake_up_village(village);
    destroy_village(village);
    return SUCCESS;
}
