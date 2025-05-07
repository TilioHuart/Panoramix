/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** villager.c
*/

#include "macros.h"
#include "village.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

static int setup_villager(village_t *village)
{
    int id = 0;

    printf("Villager %d: Going into battle!\n", village->villager_id);
    id = village->villager_id;
    village->villager_id += 1;
    return id;
}

void handle_simple_drink(village_t *village, int id)
{
    printf("Villager %d: I need a drink... I see %d servings left.\n", id,
        village->nb_serving_left);
    sem_wait(&village->pot);
    village->nb_serving_left -= 1;
}

void handle_particular_drink(village_t *village)
{
    village->has_fill = 0;
}

static int drink(village_t *village, int id)
{
    pthread_mutex_lock(&village->lock);
    if (village->has_fill == 1 && village->nb_serving_left > 0) {
        handle_particular_drink(village);
        return pthread_mutex_unlock(&village->lock), SUCCESS;
    }
    if (village->nb_serving_left > 0) {
        handle_simple_drink(village, id);
        return pthread_mutex_unlock(&village->lock), SUCCESS;
    }
    if (village->nb_serving_left == 0 && village->druid_call == SLEEPY) {
        printf("Villager %d: I need a drink... I see %d servings left.\n", id,
            village->nb_serving_left);
        printf("Villager %d: Hey Pano wake up! We need more potion.\n", id);
        village->druid_call = CALL;
        return pthread_mutex_unlock(&village->lock), FAILURE;
    }
    return pthread_mutex_unlock(&village->lock), FAILURE;
}

static void figth(int id, int *nb_figths)
{
    if (*nb_figths > 0) {
        *nb_figths -= 1;
        printf("Villager %d: Take that roman scum! Only %d left.\n", id,
            *nb_figths);
    }
}

void *call_villager(void *tmp_village)
{
    village_t *village = (village_t *)tmp_village;
    int nb_figths = village->nb_fights;
    int id = setup_villager(village);

    while (nb_figths > 0) {
        if (drink(village, id) == SUCCESS) {
            figth(id, &nb_figths);
        }
    }
    printf("Villager %d: I'm going to sleep now.\n", id);
    village->nb_villager_sleeping += 1;
    return NULL;
}
