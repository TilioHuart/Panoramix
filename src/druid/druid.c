/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** druid.c
*/

#include "village.h"
#include <pthread.h>
#include <semaphore.h>
#include <stddef.h>
#include <stdio.h>

static void fill_potion(village_t *village)
{
    if (village->druid_call == CALL && village->nb_refills > 0) {
        pthread_mutex_lock(&village->lock);
        printf("Druid: Ah! Yes, yes, I'm awake! Working on it! Beware I can "
            "only make %d more refills after this one.\n",
            village->nb_refills -= 1);
        for (int i = 0; i < village->pot_size; i += 1) {
            sem_post(&village->pot);
            village->nb_serving_left += 1;
        }
        village->has_fill = 1;
        village->druid_call = SLEEPY;
        pthread_mutex_unlock(&village->lock);
    }
    if (village->nb_refills <= 0) {
        printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
        pthread_mutex_lock(&village->lock);
        village->druid_call = LEAVE;
        pthread_mutex_unlock(&village->lock);
    }
}

static void activate_druid(void)
{
    printf("Druid: I'm ready... but sleepy...\n");
}

void *call_druid(void *tmp_village)
{
    village_t *village = (village_t *)tmp_village;

    activate_druid();
    while (village->druid_call != LEAVE) {
        if (village->nb_villager_sleeping == village->nb_villagers)
            return NULL;
        fill_potion(village);
    }
    return NULL;
}
