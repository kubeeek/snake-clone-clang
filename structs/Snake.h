#ifndef Snake_H
#define Snake_H
#include "Node.h"

enum direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT,
};

struct Snake
{
    short int length;
    enum direction direction;
    struct node *head;
};
#endif