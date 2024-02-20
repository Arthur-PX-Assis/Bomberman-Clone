#ifndef STRUCTS_H
#define STRUCTS_H

#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define HERO_BOMB_HEIGHT_WIDTH 40
#define CONST_MAP_ITENS_SIZE 40

typedef struct
{
    Texture2D bombSprite;
} Sprites;

typedef enum
{
    MENU_INICIAR_JOGO,
    MENU_OPCOES,
    MENU_SAIR
} MenuItem;

typedef struct
{
    Rectangle pos_size;
} Limit;

typedef struct
{
    Rectangle pos_size;
    Texture2D sprite;
} Obstacle;

typedef struct
{
    Rectangle pos_size;
    int drawed;
    Texture2D sprite;
} Box;

typedef struct
{
    Rectangle pos_size;
    Color typeItem;
    int auxDraw;
} Item;

typedef struct
{
    int raio;
    int timer;
    double tempoAtual;
    double tempoDecorrido;
    double tempoInicial;
    Rectangle explosionR;
    Rectangle explosionRBox;
    int stopR;
    Rectangle explosionL;
    Rectangle explosionLBox;
    int stopL;
    Rectangle explosionU;
    Rectangle explosionUBox;
    int stopU;
    Rectangle explosionD;
    Rectangle explosionDBox;
    int stopD;
    Rectangle bombBody;
    Rectangle deathV;
    Rectangle deathH;
} Bomb;

typedef struct
{
    int pos_x;
    int pos_y;
    int deadOrAlive;
    int qtdBombas;
    int dropedBomb;
    int life;
    int velocidade;
    Rectangle pos_size;
    Bomb bomba;
    Texture2D sprite;
    char nome[21];
} Player;

typedef struct
{
    Limit limits[4];
    Obstacle obstacles[36];
    Box boxes[13][13];
    Item items[13][13];
} Mapa;

int jogoPausado = 0;

#endif // STRUCTS_H