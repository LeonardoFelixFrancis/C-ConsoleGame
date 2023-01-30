#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"

typedef struct {
    int x, y;
}entity;

typedef struct 
{
    int size;
    int score;
}map;

typedef struct
{
    entity* enemyArr;
    int enemyQuantity;
}enemies;


int input(entity* p, int* gamestate, map* m)
{
    switch (getch())
    {
    case 'd':
        p->x++;
        if(p->x > m->size-1)
        {
            p->x = 0;
        }
        break;
    case 'a': 
        p->x--;
        if(p->x < 0)
        {
            p->x = m->size-1;
        }
        break;
    case 'w':
        p->y--;
        if(p->y < 0)
        {
            p->y = m->size-1;
        }
        break;
    case 's':
        p->y++;
        if(p->y > m->size-1)
        {
            p->y = 0;
        }
        break;
    case 'o':
        *gamestate = 1;
    default:
        break;
    }

    return 0;
}

void drawMap(entity *p, map* m, enemies* e)
{
    for (int i = 0; i < m->size; i++)
    {
        for (int j = 0; j < m->size; j++)
        {
            int flag = 0;
            if (p->x == j && p->y == i){
                printf(ANSI_COLOR_GREEN);
                printf("P ");
                printf(ANSI_COLOR_RESET);
                flag = 1;
            }


            for(int z = 0; z < e->enemyQuantity; z++){
                if(e->enemyArr[z].x == j && e->enemyArr[z].y == i){
                    printf(ANSI_COLOR_RED "E " ANSI_COLOR_RESET);
                    flag = 1;
                }
            }
            
            if (flag == 0)
                printf(ANSI_COLOR_YELLOW "0 " ANSI_COLOR_RESET);
            
        }
        printf("\n");
    }

}

void enemyIA(enemies* e, entity* player){
    
    for (int i = 0; i < e->enemyQuantity; i++)
    {
        if(player->x > e->enemyArr[i].x)
        {
            e->enemyArr[i].x++;
        }else if(player->x < e->enemyArr[i].x)
        {
            e->enemyArr[i].x--;
        }

        if(player->y > e->enemyArr[i].y)
        {
            e->enemyArr[i].y++;
        }
        else if(player->y < e->enemyArr[i].y)
        {
            e->enemyArr[i].y--;
        }
    }
}

int main()
{
    entity myPlayer;
    enemies enemyControl;
    map myMap;

    myMap.size = 30;
    myMap.score = 0;

    myPlayer.x = 15;
    myPlayer.y = 10;

    enemyControl.enemyArr = (entity*)malloc(sizeof(entity));
    enemyControl.enemyQuantity = 1;
    printf("Enemy Quantity: %d\n", enemyControl.enemyQuantity);
    enemyControl.enemyArr[0].x = 0;
    enemyControl.enemyArr[0].y = 0;

    int gameState = 0;

    while(gameState == 0)
    {
       system("cls");
       drawMap(&myPlayer, &myMap, &enemyControl);
       printf("\n SCORE: %d\n Player pos | X: %d | Y: %d\n", myMap.score, myPlayer.x, myPlayer.y);
       input(&myPlayer, &gameState, &myMap);
       enemyIA(&enemyControl, &myPlayer);
       myMap.score++;
       for (int i = 0; i < enemyControl.enemyQuantity; i++)
       {
            if(enemyControl.enemyArr[i].x == myPlayer.x && enemyControl.enemyArr[i].y == myPlayer.y)
            {
                    gameState = 1;
            }
       }

       if(myMap.score == 50)
       {
        enemyControl.enemyArr = (enemies*)realloc(enemyControl.enemyArr, 
        sizeof(enemies) * enemyControl.enemyQuantity+1);
        enemyControl.enemyArr[1].x = 10;
        enemyControl.enemyArr[1].y = 10;
        enemyControl.enemyQuantity++;
       }
    }
    system("cls");
    printf("YOU LOSE\n");
    printf("Your score: %d", myMap.score);
    
    return 0;
}
