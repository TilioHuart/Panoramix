/*
** EPITECH PROJECT, 2025
** panoramix
** File description:
** village
*/

#ifndef VILLAGE_H_
    #define VILLAGE_H_

    #include <pthread.h>

typedef struct village {
    int nb_villagers;
    int pot_size;
    int nb_fights;
    int nb_refills;
    pthread_t *thread_villager;
    pthread_t thread_druid;
} village_t;

#endif
