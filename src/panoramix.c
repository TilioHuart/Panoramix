/*
** EPITECH PROJECT, 2025
** panoramix
** File description:
** panoramix.c
*/

#include "macros.h"
#include "village.h"
#include "parser.h"
#include <stdlib.h>
#include <stdio.h>

int panoramix(int const argc, char const *argv[])
{
    village_t *village = (village_t *)malloc(sizeof(village_t));

    if (parse_flag(argc, argv, village) == FAILURE)
        return EPITECH_FAILURE;
    printf("village : %d %d %d %d\n", village->nv_villagers, village->pot_size, village->nb_fights, village->nb_refills);
    free(village);
    return SUCCESS;
}
