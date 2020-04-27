#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs/Options.h"
#include "structs/Node.h"
#include "structs/Snake.h"

int parseOptions(int argc, char *argv[], struct Options *options)
{
    int option;
    while ((option = getopt(argc, argv, "hx:y:l:")) != -1)
    {
        switch (option)
        {
        case 'h':
            printf("######## POMOC ####### \n");
            printf("Dostepne parametry: \n\n");
            printf("** -h -> pokazuje pomoc \n");
            printf("** -x [liczba] -> definiuje rozmiar planszy planszy w szerokosci (standardowo 30) \n");
            printf("** -y [liczba] -> definiuje rozmiar planszy planszy w wysokosci(tandardowo 30) \n");
            printf("** -l [easy/normal/hard] -> ustawia poziom trudnosci (waz porusza sie wolniej, domyslnie normal)\n");

            printf("Gdy plansza pojawia się niepoprawnie, oznacza to, ze okno terminala jest za male.\n");

            return 0;
        case 'x':
            options->x = atoi(optarg);
            break;
        case 'y':
            options->y = atoi(optarg);
            break;
        case 'l':
            if (strcmp(optarg, "hard") == 0)
            {
                options->level = 3;
            } else if (strcmp(optarg, "easy") == 0) {
                options->level = 1;
            } else {
                options->level = 2;
            }
            break;
        default:
            return 0;
        }
    }

    printf("\n\n");

    return 1;
}

int getRandomInteger(int lower, int upper)
{
    int num = (rand() %
               (upper - lower + 1)) +
              lower;
    return num;
}