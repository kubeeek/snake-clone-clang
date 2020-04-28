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
            printf("######## HELP ####### \n");
            printf("Command line arguments: \n\n");
            printf("** -h -> pokazuje pomoc \n");
            printf("** -x [integer] -> defines width of the game board (default 30) \n");
            printf("** -y [integer] -> defines the height of the game board (default 30) \n");
            printf("** -l [easy/normal/hard] -> defines difficulty level (the harder, the snake moves faster) \n");

            printf("When the board renders with any artifacts or error, it means the terminal window is too small.\n");

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