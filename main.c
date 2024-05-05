#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define GRIDX 80
#define GRIDY 24

typedef enum
{
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
} DIRECTION;

char grid[GRIDY][GRIDX];

int snakeLen = 4;
int score = 0;
DIRECTION snakeDir = RIGHT;

int snake[GRIDX * GRIDY][2];
int food[2];

void setGrid();
void setSnake();
void printGrid();
void moveSnake();
void resetGame();
void setFood();
void genFood();
void checkCatch();
int main()
{

    resetGame();
    bool gameloop = true;
    int loopDelay = 300;
    genFood();

    while (gameloop)
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 'w':
                snakeDir = TOP;
                break;
            case 'a':
                snakeDir = LEFT;
                break;
            case 'd':
                snakeDir = RIGHT;
                break;
            case 's':
                snakeDir = BOTTOM;
                break;
            default:
                break;
            }
        }
        setGrid();
        setSnake();
        setFood();
        printGrid();
        moveSnake();
        checkCatch();
        Sleep(loopDelay);
    }

    return 0;
}

void setGrid()
{
    for (int y = 0; y < GRIDY; y++)
    {
        for (int x = 0; x < GRIDX; x++)
        {
            if (x == 0 || x == GRIDX - 1 || y == 0 || y == GRIDY - 1)
                grid[y][x] = '*';
            else
                grid[y][x] = ' ';
        }
    }
}

void setSnake()
{
    char snakeHead = '>';

    if (snakeDir == LEFT)
        snakeHead = '<';
    else if (snakeDir == TOP)
        snakeHead = '^';
    else if (snakeDir == BOTTOM)
        snakeHead = 'v';

    for (int len = 0; len < snakeLen; len++)
    {

        grid[snake[len][1]][snake[len][0]] = len == 0 ? snakeHead : 'o';
    }
}

void printGrid()
{
    system("cls");
    printf("\n Score: %d \n", score);

    for (int y = 0; y < GRIDY; y++)
    {
        putchar(' ');
        for (int x = 0; x < GRIDX; x++)
        {
            putchar(grid[y][x]);
        }
        putchar('\n');
    }
}

void moveSnake()
{
    int prevHeadX = snake[0][0];
    int prevHeadY = snake[0][1];

    switch (snakeDir)
    {
    case TOP:
        snake[0][1]--;

        if (snake[0][1] < 1)
            snake[0][1] = GRIDY - 2;

        break;
    case RIGHT:
        snake[0][0]++;

        if (snake[0][0] >= GRIDX - 2)
            snake[0][0] = 1;

        break;
    case BOTTOM:
        snake[0][1]++;

        if (snake[0][1] >= GRIDY - 1)
            snake[0][1] = 1;
        break;
    case LEFT:
        snake[0][0]--;

        if (snake[0][0] <= 1)
            snake[0][0] = GRIDX - 2;

        break;
    default:
        break;
    }

    int tempX;
    int tempY;
    for (int i = 1; i < snakeLen; i++)
    {
        tempX = snake[i][0];
        tempY = snake[i][1];
        snake[i][0] = prevHeadX;
        snake[i][1] = prevHeadY;
        prevHeadX = tempX;
        prevHeadY = tempY;
    }
}

void genFood()
{
    srand((unsigned int)time(NULL));
    food[0] = rand() % (GRIDX - 3) + 1;
    food[1] = rand() % (GRIDY - 3) + 1;
}

void setFood()
{
    grid[food[1]][food[0]] = 'O';
}

void checkCatch()
{
    if (snake[0][0] == food[0] && snake[0][1] == food[1])
    {
        score += 5;        
        snakeLen += 1;
        genFood();
    }
}

void resetGame()
{
    score = 0;
    for (int i = 0; i < GRIDX * GRIDY; i++)
    {
        snake[i][0] = -1;
        snake[i][1] = -1;
    }

    snake[0][0] = 58;
    snake[0][1] = 12;
    for (int i = 1; i < snakeLen; i++)
    {
        snake[i][0] = snake[i - 1][0] - 1;
        snake[i][1] = snake[i - 1][1];
    }
}
