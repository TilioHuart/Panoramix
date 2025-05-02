/*
** EPITECH PROJECT, 2025
** panoramix
** File description:
** village
*/

#ifndef VILLAGE_H_
    #define VILLAGE_H_

    #include <pthread.h>
    #include <semaphore.h>
    #include <stddef.h>

enum druid_state {
    CALL = 0,
    SLEEPY = 1,
    LEAVE = 2
};

typedef struct village {
    int nb_villagers;
    int pot_size;
    int nb_serving_left;
    int nb_fights;
    int nb_refills;
    pthread_t *thread_villager;
    pthread_t thread_druid;
    enum druid_state druid_call;
    int villager_id;
    sem_t pot;
    pthread_mutex_t lock;
} village_t;

#endif
