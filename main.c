#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "utils.h"
#include "structs/Event.h"
#include "structs/Options.h"
#include "structs/Snake.h"
#include "structs/Node.h"

#define SNAKE "@"
#define WALL "#"
#define APPLE "$"

int SCORE = 0;

int HEIGHT = 30;
int WIDTH = 30;

struct Options OPTIONS = {
    .x = 0,
    .y = 0,
    .level = 2};

void render(int board[HEIGHT][WIDTH])
{
    int x, y = 0;

    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            switch (board[y][x])
            {
            case 3:
            {
                printw(APPLE);
                break;
            }
            case 2:
            {
                printw(SNAKE);
                break;
            }
            case 1:
            {
                printw(WALL);
                break;
            }
            default:
                printw(" ");
                break;
            }
        }
        printw("\n");
    }
}

void createSnake(struct Snake *player)
{
    player->head->x = WIDTH / 2 - 1;
    player->head->y = HEIGHT / 2 - 1;
    player->head->next = NULL;
}
void createRandomApple(int board[HEIGHT][WIDTH])
{
    int x = getRandomInteger(1, WIDTH - 2);
    int y = getRandomInteger(1, HEIGHT - 2);

    board[y][x] = 3;
}
int fireEvent(struct Event event, int board[HEIGHT][WIDTH], struct Snake player)
{
    switch (event.type)
    {
    case DEATH:

        return -1;
        break;
    case DINNER:
        createRandomApple(board);
        return 1;
    default:
        break;
    }
}

void changeDirection(struct Snake *player, enum direction new)
{
    short int current = player->direction;

    if (new == UP && current == DOWN)
        return;
    if (new == DOWN && current == UP)
        return;
    if (new == RIGHT && current == LEFT)
        return;
    if (new == LEFT && current == RIGHT)
        return;
    player->direction = new;
}

void handleInput(int c, struct Snake *player, int board[HEIGHT][WIDTH])
{
    switch (c)
    {
    case KEY_UP:
        changeDirection(player, UP);
        break;
    case KEY_DOWN:
        changeDirection(player, DOWN);
        break;
    case KEY_RIGHT:
        changeDirection(player, RIGHT);
        break;
    case KEY_LEFT:
        changeDirection(player, LEFT);
        break;
    }
}

int checkForObstacle(int board[HEIGHT][WIDTH], struct Snake *player)
{
    int direction = player->direction;
    switch (direction)
    {
    case UP:
        if (board[player->head->y - 1][player->head->x] == 3)
        {
            player->length++;
            SCORE++;
            createRandomApple(board);

            return 1;
        }
        else if (board[player->head->y - 1][player->head->x] == 2)
        {
            return -1;
        }
        break;
    case DOWN:
        if (board[player->head->y + 1][player->head->x] == 3)
        {
            SCORE++;
            player->length++;
            createRandomApple(board);

            return 1;
        }
        else if (board[player->head->y + 1][player->head->x] == 2)
        {
            return -1;
        }
        break;
    case LEFT:
        if (board[player->head->y][player->head->x - 1] == 3)
        {
            SCORE++;
            player->length++;
            createRandomApple(board);

            return 1;
        }
        else if (board[player->head->y][player->head->x - 1] == 2)
        {
            return -1;
        }
        break;
    case RIGHT:
        if (board[player->head->y][player->head->x + 1] == 3)
        {
            SCORE++;
            player->length++;
            createRandomApple(board);

            return 1;
        }
        else if (board[player->head->y][player->head->x + 1] == 2)
        {
            return -1;
        }
        break;
    default:
        return 1;
        break;
    }

    return 0;
}

int moveSnake(int board[HEIGHT][WIDTH], struct Snake *player)
{
    int direction = player->direction;
    int x = player->head->x;
    int y = player->head->y;

    int obstacle = checkForObstacle(board, player);

    switch (direction)
    {
    case UP:
        y -= 1;
        break;
    case DOWN:
        y += 1;
        break;
    case RIGHT:
        x += 1;
        break;
    case LEFT:
        x -= 1;
        break;
    default:
        break;
    }

    struct node *oldHead = NULL;
    oldHead = player->head;

    if (obstacle == 1)
    {
        player->head = (struct node *)malloc(sizeof(struct node));
        player->head->next = oldHead;
        player->head->x = x;
        player->head->y = y;
    }
    else if (obstacle == -1)
    {
        return -1;
    }
    else
    {
        /* dokladamy +1 z przodu */
        player->head = (struct node *)malloc(sizeof(struct node));
        player->head->next = oldHead;
        player->head->x = x;
        player->head->y = y;
        if (player->head->next == NULL)
        {
        }
        /* przesuwamy snejka (usuwamy ogon) */

        struct node *current = player->head;
        while (current->next->next != NULL)
        {
            current = current->next;
        }

        board[current->next->y][current->next->x] = 0;
        free(current->next);
        current->next = NULL;
    }

    struct node *element = player->head;

    while (element != NULL)
    {
        board[element->y][element->x] = 2;

        element = element->next;
    }
}

int checkForCollision(struct Snake player, int board[HEIGHT][WIDTH])
{
    if (player.direction == UP || player.direction == DOWN)
    {
        if (player.head->y >= HEIGHT - 1 || player.head->y <= 0)
        {
            return 1;
        }
    }

    if (player.direction == LEFT || player.direction == RIGHT)
    {
        if (player.head->x >= WIDTH - 1 || player.head->x <= 0)
        {
            return 1;
        }
    }
    return 0;
}

int initBoard(int board[HEIGHT][WIDTH], struct Snake player)
{
    int x, y;

    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            board[y][x] = 0;
        }

        if (y == 0 || y == HEIGHT - 1)
        {
            for (x = 0; x < WIDTH; x++)
            {
                board[y][x] = 1;
            }
        }
        else
        {
            board[y][0] = 1;
            board[y][WIDTH - 1] = 1;
        }
    }

    createRandomApple(board);

    createSnake(&player);
}

int main(int argc, char *argv[])
{
    if (!parseOptions(argc, argv, &OPTIONS))
    {
        return 1;
    }

    int TIMEOUT = 100;
    char* level = malloc(sizeof(char)*10);
    level = "normal";
    WIDTH = OPTIONS.x ? OPTIONS.x : WIDTH;
    HEIGHT = OPTIONS.y ? OPTIONS.y : HEIGHT;
    switch (OPTIONS.level)
    {
    case 1:
        TIMEOUT = 500;
        level = "easy";
        break;
    case 2:
        TIMEOUT = 150;
        level = "normal";
        break;
    case 3:
        TIMEOUT = 75;
        level = "hard";
        break;
    }

    srand((unsigned int)time(NULL));

    initscr();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    timeout(TIMEOUT);
    curs_set(0);

    int board[HEIGHT][WIDTH];
    short int game = 1;

    struct Snake player = {
        .length = 1,
        .direction = UP,
        .head = (struct node *)malloc(sizeof(struct node))};

    initBoard(board, player);

    while (1)
    {
        clear();

        if (moveSnake(board, &player))
            break;
        printw("Score: %i \n\n", SCORE);
        render(board);
        printw("X: %i, Y: %i, difficulty level: %s", player.head->x, player.head->y, level);
        refresh();
        if (checkForCollision(player, board))
            break;
        handleInput(getch(), &player, board);
    }

    endwin();
    printf("\n\n Your score is: %i ", SCORE);

    return 1;
}