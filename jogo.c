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

void initMap(Mapa *m, int aux)
{
    // Limits
    m[aux].limits[0].pos_size = (Rectangle){100, 0, 600, 40};
    m[aux].limits[1].pos_size = (Rectangle){100, 40, 40, 560};
    m[aux].limits[2].pos_size = (Rectangle){140, 560, 560, 40};
    m[aux].limits[3].pos_size = (Rectangle){660, 40, 40, 520};

    // Obstacles
    int numRows = 6;
    int numCols = 6;
    int yOffset[] = {80, 160, 240, 320, 400, 480};
    int xOffset[] = {180, 260, 340, 420, 500, 580};
    int count = 0;

    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            m[aux].obstacles[count].pos_size.y = yOffset[row];
            m[aux].obstacles[count].pos_size.x = xOffset[col];
            m[aux].obstacles[count].pos_size.height = CONST_MAP_ITENS_SIZE;
            m[aux].obstacles[count].pos_size.width = CONST_MAP_ITENS_SIZE;

            m[aux].obstacles[count].sprite = LoadTexture("sprite/cloud.png");

            count++;
        }
    }

    // Boxes
    if (aux == 1)
    {
        m[1].boxes[10][8].drawed = 0;
        m[1].boxes[9][5].drawed = 0;
        m[1].boxes[8][8].drawed = 0;
    }

    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            m[aux].boxes[i][j].pos_size.x = 140 + (j * 40);
            m[aux].boxes[i][j].pos_size.y = 40 + (i * 40);
            m[aux].boxes[i][j].pos_size.width = HERO_BOMB_HEIGHT_WIDTH;
            m[aux].boxes[i][j].pos_size.height = HERO_BOMB_HEIGHT_WIDTH;

            if (aux == 0)
            {
                if (i == 2)
                {
                    if (j == 9 || j == 10 || j == 11)
                        m[aux].boxes[i][j].drawed = 1;
                }
                if (i == 3)
                {
                    if (j == 10 || j == 12)
                        m[aux].boxes[i][j].drawed = 1;
                }
                if (i == 4)
                {
                    if (j == 0 || j == 1 || j == 2 || j == 3 || j == 4 || j == 6 || j == 7)
                        m[aux].boxes[i][j].drawed = 1;
                }
                if (i == 5)
                {
                    if (j == 4 || j == 6 || j == 8 || j == 10 || j == 12)
                        m[aux].boxes[i][j].drawed = 1;
                }
                if (i == 6)
                {
                    if (j == 1 || j == 3 || j == 4 || j == 8 || j == 9 || j == 11)
                        m[aux].boxes[i][j].drawed = 1;
                }
                if (i == 7)
                {
                    if (j == 4 || j == 12)
                        m[aux].boxes[i][j].drawed = 1;
                }
                if (i == 8)
                {
                    if (j == 0 || j == 1 || j == 2 || j == 5 || j == 7 || j == 8 || j == 9 || j == 10 || j == 11)
                        m[aux].boxes[i][j].drawed = 1;
                }
                if (i == 9)
                {
                    if (j == 10 || j == 12)
                        m[aux].boxes[i][j].drawed = 1;
                }
                if (i == 10 && j == 1)
                    m[aux].boxes[i][j].drawed = 1;
                if (i == 11 && j == 8)
                    m[aux].boxes[i][j].drawed = 1;
                if (i == 12)
                {
                    if (j == 9 || j == 10)
                        m[aux].boxes[i][j].drawed = 1;
                }
            }

            if (aux == 1)
            {
                if (i == 2)
                {
                    if (j == 9 || j == 12)
                        m[aux].boxes[i][j].drawed = 1;
                }
                if (i == 3)
                {
                    if (j == 2 || j == 4 || j == 10)
                        m[aux].boxes[i][j].drawed = 1;
                }
                if (i == 4)
                {
                    if (j == 3 || j == 4 || j == 5 || j == 7 || j == 9 || j == 11 || j == 12)
                        m[aux].boxes[i][j].drawed = 1;
                }
                if (i == 5)
                {
                    if (j == 2 || j == 8 || j == 10)
                        m[aux].boxes[i][j].drawed = 1;
                }
                if (i == 6)
                {
                    if (j == 1 || j == 7)
                        m[aux].boxes[i][j].drawed = 1;
                }
                if (i == 7)
                {
                    if (j == 2 || j == 6 || j == 8)
                        m[aux].boxes[i][j].drawed = 1;
                }
                if (i == 8)
                {
                    if (j == 0 || j == 7 || j == 10 || j == 11)
                        m[aux].boxes[i][j].drawed = 1;
                }
                if (i == 9)
                {
                    if (j == 2 || j == 8)
                        m[aux].boxes[i][j].drawed = 1;
                }
                if (i == 10)
                {
                    if (j == 0 || j == 2 || j == 3 || j == 8 || j == 9)
                        m[aux].boxes[i][j].drawed = 1;
                }
                if (i == 11)
                {
                    if (j == 0 || j == 4 || j == 10)
                        m[aux].boxes[i][j].drawed = 1;
                }
                if (i == 12)
                {
                    if (j == 0 || j == 1 || j == 2 || j == 4 || j == 5 || j == 7)
                        m[aux].boxes[i][j].drawed = 1;
                }
            }

            // Items
            if (m[aux].boxes[i][j].drawed == 1)
            {
                m[aux].items[i][j].pos_size = m[aux].boxes[i][j].pos_size;
                m[aux].items[i][j].auxDraw = 0;
            }
        }
    }
}

void drawLimits(Mapa *m)
{
    for (int i = 0; i < 4; i++)
    {
        DrawRectangleRec(m->limits[i].pos_size, BLACK);
    }
}

void drawBoxes(Mapa *m)
{
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            if (m->boxes[i][j].drawed == 1)
            {
                DrawRectangleRec(m->boxes[i][j].pos_size, BLUE);
            }
            else
            {
                m->boxes[i][j].pos_size = (Rectangle){0, 0, 0, 0};
            }
        }
    }
}

void drawItems(Mapa *m)
{
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            if (m->items[i][j].auxDraw != 0)
            {
                DrawRectangleRec(m->items[i][j].pos_size, m->items[i][j].typeItem);
            }
        }
    }
}

void initPlayer(Player p[])
{
    p[0].sprite = LoadTexture("sprite/aviaop1_olhando_direit.png");
    p[0].pos_size = (Rectangle){140, 40, HERO_BOMB_HEIGHT_WIDTH, HERO_BOMB_HEIGHT_WIDTH};
    p[0].deadOrAlive = 1;
    p[0].qtdBombas = 1;
    p[0].bomba.raio = 100;
    p[0].bomba.timer = 3;
    p[0].dropedBomb = 0;
    p[0].life = 1;
    p[0].velocidade = 2;
    p[0].bomba.tempoAtual = 0;
    p[0].bomba.tempoDecorrido = 0;

    p[1].sprite = LoadTexture("sprite/aviaop2_olhando_esq.png");
    p[1].pos_size = (Rectangle){660 - HERO_BOMB_HEIGHT_WIDTH, 560 - HERO_BOMB_HEIGHT_WIDTH, HERO_BOMB_HEIGHT_WIDTH, HERO_BOMB_HEIGHT_WIDTH};
    p[1].deadOrAlive = 1;
    p[1].qtdBombas = 1;
    p[1].bomba.raio = 100;
    p[1].bomba.timer = 3;
    p[1].dropedBomb = 0;
    p[1].life = 1;
    p[1].velocidade = 2;
    p[1].bomba.tempoAtual = 0;
    p[1].bomba.tempoDecorrido = 0;
}

void initExplosion(Player p[], int aux)
{
    p[aux].bomba.explosionL = (Rectangle){p[aux].pos_size.x, p[aux].pos_size.y, 0, HERO_BOMB_HEIGHT_WIDTH};
    p[aux].bomba.explosionLBox = (Rectangle){p[aux].pos_size.x - 1, p[aux].pos_size.y, 1, HERO_BOMB_HEIGHT_WIDTH};
    p[aux].bomba.stopL = 0;
    p[aux].bomba.explosionR = (Rectangle){p[aux].pos_size.x + HERO_BOMB_HEIGHT_WIDTH, p[aux].pos_size.y, 0, HERO_BOMB_HEIGHT_WIDTH};
    p[aux].bomba.explosionRBox = (Rectangle){p[aux].pos_size.x + HERO_BOMB_HEIGHT_WIDTH, p[aux].pos_size.y, 1, HERO_BOMB_HEIGHT_WIDTH};
    p[aux].bomba.stopR = 0;
    p[aux].bomba.explosionU = (Rectangle){p[aux].pos_size.x, p[aux].pos_size.y, HERO_BOMB_HEIGHT_WIDTH, 0};
    p[aux].bomba.explosionUBox = (Rectangle){p[aux].pos_size.x, p[aux].pos_size.y - 1, HERO_BOMB_HEIGHT_WIDTH, 1};
    p[aux].bomba.stopU = 0;
    p[aux].bomba.explosionD = (Rectangle){p[aux].pos_size.x, p[aux].pos_size.y + HERO_BOMB_HEIGHT_WIDTH, HERO_BOMB_HEIGHT_WIDTH, 0};
    p[aux].bomba.explosionDBox = (Rectangle){p[aux].pos_size.x, p[aux].pos_size.y + HERO_BOMB_HEIGHT_WIDTH, HERO_BOMB_HEIGHT_WIDTH, 1};
    p[aux].bomba.stopD = 0;
}

void drawObstacles(Mapa *m)
{
    for (int i = 0; i < 36; i++)
    {
        DrawTexture(m->obstacles[i].sprite, m->obstacles[i].pos_size.x, m->obstacles[i].pos_size.y, WHITE);
    }
}

void drawBomb(Player p[], int aux, Color cor, Sprites sprt)
{
    DrawTexture(sprt.bombSprite, (int)p[aux].bomba.bombBody.x, (int)p[aux].bomba.bombBody.y, WHITE);
}

void drawExplosion(Player p[], Mapa *m, int aux, int auxMap)
{
    srand(time(NULL));

    p[aux].bomba.tempoAtual = GetTime();
    p[aux].bomba.tempoDecorrido = p[aux].bomba.tempoAtual - p[aux].bomba.tempoInicial;

    if (p[aux].bomba.tempoDecorrido > p[aux].bomba.timer)
    {

        int checkU = 0;
        int checkUBox = 0;

        for (int i = 0; i < 36; i++)
        {
            if (!CheckCollisionRecs(p[aux].bomba.explosionUBox, m[auxMap].obstacles[i].pos_size))
            {
                checkU++;
            }
        }

        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                if (!CheckCollisionRecs(p[aux].bomba.explosionUBox, m[auxMap].boxes[i][j].pos_size) && m[auxMap].boxes[i][j].drawed == 1)
                {
                    checkUBox++;
                }
            }
        }

        if (checkU == 36 && checkUBox == 40 && p[aux].bomba.stopU == 0)
        {
            if (p[aux].bomba.explosionUBox.height + 5 < p[aux].bomba.raio)
            {
                p[aux].bomba.explosionU.y -= 6;
                p[aux].bomba.explosionU.height += 6;
                p[aux].bomba.explosionUBox.y -= 6;
                p[aux].bomba.explosionUBox.height += 6;
            }
        }

        if (checkUBox != 40)
        {
            int i = 0;
            int j = 0;
            int dropChanceU = (rand() % 5) + 1;
            int dropU = 0;
            if (dropChanceU == 1)
                dropU = (rand() % 3) + 1;
            while (p[aux].bomba.stopU == 0 && i < 13)
            {
                if (CheckCollisionRecs(p[aux].bomba.explosionUBox, m[auxMap].boxes[i][j].pos_size))
                {
                    m[auxMap].boxes[i][j].pos_size = (Rectangle){0, 0, 0, 0};
                    if (dropU == 1)
                    {
                        m[auxMap].items[i][j].auxDraw = 1;
                        m[auxMap].items[i][j].typeItem = BLACK;
                    }
                    else if (dropU == 2)
                    {
                        m[auxMap].items[i][j].auxDraw = 2;
                        m[auxMap].items[i][j].typeItem = ORANGE;
                    }
                    else if (dropU == 3)
                    {
                        m[auxMap].items[i][j].auxDraw = 3;
                        m[auxMap].items[i][j].typeItem = GREEN;
                    }
                    p[aux].bomba.stopU++;
                }
                j++;
                if (j == 13)
                {
                    j = 0;
                    i++;
                }
            }
        }

        int checkL = 0;
        int checkLBox = 0;

        for (int i = 0; i < 36; i++)
        {
            if (!CheckCollisionRecs(p[aux].bomba.explosionLBox, m[auxMap].obstacles[i].pos_size))
            {
                checkL++;
            }
        }

        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                if (!CheckCollisionRecs(p[aux].bomba.explosionLBox, m[auxMap].boxes[i][j].pos_size) && m[auxMap].boxes[i][j].drawed == 1)
                {
                    checkLBox++;
                }
            }
        }

        if (checkL == 36 && checkLBox == 40 && p[aux].bomba.stopL == 0)
        {
            if (p[aux].bomba.explosionLBox.width + 5 < p[aux].bomba.raio)
            {
                p[aux].bomba.explosionL.x -= 6;
                p[aux].bomba.explosionL.width += 6;
                p[aux].bomba.explosionLBox.x -= 6;
                p[aux].bomba.explosionLBox.width += 6;
            }
        }

        if (checkLBox != 40)
        {
            int i = 0;
            int j = 0;
            int dropChanceL = (rand() % 5) + 1;
            int dropL = 0;
            if (dropChanceL == 1)
                dropL = (rand() % 3) + 1;
            while (p[aux].bomba.stopL == 0 && i < 13)
            {
                if (CheckCollisionRecs(p[aux].bomba.explosionLBox, m[auxMap].boxes[i][j].pos_size))
                {
                    m[auxMap].boxes[i][j].pos_size = (Rectangle){0, 0, 0, 0};
                    if (dropL == 1)
                    {
                        m[auxMap].items[i][j].auxDraw = 1;
                        m[auxMap].items[i][j].typeItem = BLACK;
                    }
                    else if (dropL == 2)
                    {
                        m[auxMap].items[i][j].auxDraw = 2;
                        m[auxMap].items[i][j].typeItem = ORANGE;
                    }
                    else if (dropL == 3)
                    {
                        m[auxMap].items[i][j].auxDraw = 3;
                        m[auxMap].items[i][j].typeItem = GREEN;
                    }
                    p[aux].bomba.stopL++;
                }
                j++;
                if (j == 13)
                {
                    j = 0;
                    i++;
                }
            }
        }

        int checkD = 0;
        int checkDBox = 0;

        for (int i = 0; i < 36; i++)
        {
            if (!CheckCollisionRecs(p[aux].bomba.explosionDBox, m[auxMap].obstacles[i].pos_size))
            {
                checkD++;
            }
        }

        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                if (!CheckCollisionRecs(p[aux].bomba.explosionDBox, m[auxMap].boxes[i][j].pos_size) && m[auxMap].boxes[i][j].drawed == 1)
                {
                    checkDBox++;
                }
            }
        }

        if (checkD == 36 && checkDBox == 40 && p[aux].bomba.stopD == 0)
        {
            if (p[aux].bomba.explosionDBox.height + 5 < p[aux].bomba.raio)
            {
                p[aux].bomba.explosionD.height += 6;
                p[aux].bomba.explosionDBox.height += 6;
            }
        }

        if (checkDBox != 40)
        {
            int i = 0;
            int j = 0;
            int dropChanceD = (rand() % 5) + 1;
            int dropD = 0;
            if (dropChanceD == 1)
                dropD = (rand() % 3) + 1;
            while (p[aux].bomba.stopD == 0 && i < 13)
            {
                if (CheckCollisionRecs(p[aux].bomba.explosionDBox, m[auxMap].boxes[i][j].pos_size))
                {
                    m[auxMap].boxes[i][j].pos_size = (Rectangle){0, 0, 0, 0};
                    if (dropD == 1)
                    {
                        m[auxMap].items[i][j].auxDraw = 1;
                        m[auxMap].items[i][j].typeItem = BLACK;
                    }
                    else if (dropD == 2)
                    {
                        m[auxMap].items[i][j].auxDraw = 2;
                        m[auxMap].items[i][j].typeItem = ORANGE;
                    }
                    else if (dropD == 3)
                    {
                        m[auxMap].items[i][j].auxDraw = 3;
                        m[auxMap].items[i][j].typeItem = GREEN;
                    }
                    p[aux].bomba.stopD++;
                }
                j++;
                if (j == 13)
                {
                    j = 0;
                    i++;
                }
            }
        }

        int checkR = 0;
        int checkRBox = 0;

        for (int i = 0; i < 36; i++)
        {
            if (!CheckCollisionRecs(p[aux].bomba.explosionRBox, m[auxMap].obstacles[i].pos_size))
            {
                checkR++;
            }
        }

        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                if (!CheckCollisionRecs(p[aux].bomba.explosionRBox, m[auxMap].boxes[i][j].pos_size) && m[auxMap].boxes[i][j].drawed == 1)
                {
                    checkRBox++;
                }
            }
        }

        if (checkR == 36 && checkRBox == 40 && p[aux].bomba.stopR == 0)
        {
            if (p[aux].bomba.explosionRBox.width + 5 < p[aux].bomba.raio)
            {
                p[aux].bomba.explosionR.width += 6;
                p[aux].bomba.explosionRBox.width += 6;
            }
        }

        if (checkRBox != 40)
        {
            int i = 0;
            int j = 0;
            int dropChanceR = (rand() % 5) + 1;
            int dropR = 0;
            if (dropChanceR == 1)
                dropR = (rand() % 3) + 1;

            while (p[aux].bomba.stopR == 0 && i < 13)
            {
                if (CheckCollisionRecs(p[aux].bomba.explosionRBox, m[auxMap].boxes[i][j].pos_size))
                {
                    m[auxMap].boxes[i][j].pos_size = (Rectangle){0, 0, 0, 0};

                    if (dropR == 1)
                    {
                        m[auxMap].items[i][j].auxDraw = 1;
                        m[auxMap].items[i][j].typeItem = BLACK;
                    }
                    else if (dropR == 2)
                    {
                        m[auxMap].items[i][j].auxDraw = 2;
                        m[auxMap].items[i][j].typeItem = ORANGE;
                    }
                    else if (dropR == 3)
                    {
                        m[auxMap].items[i][j].auxDraw = 3;
                        m[auxMap].items[i][j].typeItem = GREEN;
                    }

                    p[aux].bomba.stopR++;
                }
                j++;
                if (j == 13)
                {
                    j = 0;
                    i++;
                }
            }
        }

        if (CheckCollisionRecs(p[aux].bomba.explosionL, m[auxMap].limits[1].pos_size))
        {
            p[aux].bomba.explosionL.x = m[auxMap].limits[1].pos_size.width + m[auxMap].limits[1].pos_size.x;
            p[aux].bomba.explosionL.width = (p[aux].bomba.bombBody.x - (m[auxMap].limits[1].pos_size.width + m[auxMap].limits[1].pos_size.x));
        }

        p[aux].bomba.deathV = (Rectangle){p[aux].bomba.bombBody.x, p[aux].bomba.explosionU.y, HERO_BOMB_HEIGHT_WIDTH,
                                          p[aux].bomba.explosionU.height + HERO_BOMB_HEIGHT_WIDTH + p[aux].bomba.explosionD.height};

        p[aux].bomba.deathH = (Rectangle){p[aux].bomba.explosionL.x, p[aux].bomba.bombBody.y,
                                          p[aux].bomba.explosionL.width + HERO_BOMB_HEIGHT_WIDTH + p[aux].bomba.explosionR.width, HERO_BOMB_HEIGHT_WIDTH};

        if (CheckCollisionRecs(p[aux].pos_size, p[aux].bomba.deathV) || CheckCollisionRecs(p[aux].pos_size, p[aux].bomba.deathH))
        {
            p[aux].life--;
        }

        if (CheckCollisionRecs(p[!aux].pos_size, p[aux].bomba.deathV) || CheckCollisionRecs(p[!aux].pos_size, p[aux].bomba.deathH))
        {
            p[!aux].life--;
        }

        if (CheckCollisionRecs(p[aux].bomba.explosionR, m[auxMap].limits[3].pos_size))
        {
            p[aux].bomba.explosionR.width = m[auxMap].limits[3].pos_size.x - (p[aux].bomba.bombBody.x + p[aux].bomba.bombBody.width);
        }

        if (CheckCollisionRecs(p[aux].bomba.explosionU, m[auxMap].limits[0].pos_size))
        {
            p[aux].bomba.explosionU.y = m[auxMap].limits[0].pos_size.height;
            p[aux].bomba.explosionU.height = (p[aux].bomba.bombBody.y - m[auxMap].limits[0].pos_size.height);
        }

        if (CheckCollisionRecs(p[aux].bomba.explosionD, m[auxMap].limits[2].pos_size))
        {
            p[aux].bomba.explosionD.height = m[auxMap].limits[2].pos_size.y - (p[aux].bomba.bombBody.y + p[aux].bomba.bombBody.height);
        }

        DrawRectangleRec(p[aux].bomba.bombBody, RED);
    }

    DrawRectangleRec(p[aux].bomba.explosionU, RED);
    DrawRectangleRec(p[aux].bomba.explosionL, RED);
    DrawRectangleRec(p[aux].bomba.explosionD, RED);
    DrawRectangleRec(p[aux].bomba.explosionR, RED);

    if (p[aux].bomba.tempoDecorrido > p[aux].bomba.timer + 2)
    {
        p[aux].dropedBomb--;
        p[aux].qtdBombas++;

        p[aux].bomba.bombBody = (Rectangle){0, 0, 0, 0};
        p[aux].bomba.stopR = 0;
        p[aux].bomba.stopD = 0;
        p[aux].bomba.stopU = 0;
        p[aux].bomba.stopL = 0;
    }
}

void updateGame(Player p[], Mapa *m, int aux)
{
    // PERSONAGEM 1

    if (IsKeyDown(KEY_W))
    {
        p[0].pos_size.y -= p[0].velocidade;

        if (CheckCollisionRecs(p[0].pos_size, m[aux].limits[0].pos_size))
        {
            p[0].pos_size.y = m[aux].limits[0].pos_size.y + m[aux].limits[0].pos_size.height;
        }

        for (int i = 0; i < 36; i++)
        {
            if (CheckCollisionRecs(p[0].pos_size, m[aux].obstacles[i].pos_size))
            {
                p[0].pos_size.y = m[aux].obstacles[i].pos_size.y + m[aux].obstacles[i].pos_size.height;
            }
        }

        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                if (CheckCollisionRecs(p[0].pos_size, m[aux].boxes[i][j].pos_size) && m[aux].boxes[i][j].drawed == 1)
                {
                    p[0].pos_size.y = m[aux].boxes[i][j].pos_size.y + m[aux].boxes[i][j].pos_size.height;
                }
            }
        }

        if (CheckCollisionRecs(p[0].pos_size, p[0].bomba.bombBody) && p[0].pos_size.y > p[0].bomba.bombBody.y)
        {
            p[0].pos_size.y = p[0].bomba.bombBody.y + p[0].bomba.bombBody.height;
        }

        if (CheckCollisionRecs(p[0].pos_size, p[1].bomba.bombBody) && p[0].pos_size.y > p[1].bomba.bombBody.y)
        {
            p[0].pos_size.y = p[1].bomba.bombBody.y + p[1].bomba.bombBody.height;
        }
    }

    if (IsKeyDown(KEY_S))
    {
        p[0].pos_size.y += p[0].velocidade;

        if (CheckCollisionRecs(p[0].pos_size, m[aux].limits[2].pos_size))
        {
            p[0].pos_size.y = m[aux].limits[2].pos_size.y - HERO_BOMB_HEIGHT_WIDTH;
        }

        for (int i = 0; i < 36; i++)
        {
            if (CheckCollisionRecs(p[0].pos_size, m[aux].obstacles[i].pos_size))
            {
                p[0].pos_size.y = m[aux].obstacles[i].pos_size.y - HERO_BOMB_HEIGHT_WIDTH;
            }
        }

        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                if (CheckCollisionRecs(p[0].pos_size, m[aux].boxes[i][j].pos_size) && m[aux].boxes[i][j].drawed == 1)
                {
                    p[0].pos_size.y = m[aux].boxes[i][j].pos_size.y - m[aux].boxes[i][j].pos_size.height - (HERO_BOMB_HEIGHT_WIDTH - m[aux].boxes[i][j].pos_size.height);
                }
            }
        }

        if (CheckCollisionRecs(p[0].pos_size, p[0].bomba.bombBody) && p[0].pos_size.y < p[0].bomba.bombBody.y)
        {
            p[0].pos_size.y = p[0].bomba.bombBody.y - p[0].bomba.bombBody.height;
        }

        if (CheckCollisionRecs(p[0].pos_size, p[1].bomba.bombBody) && p[0].pos_size.y < p[1].bomba.bombBody.y)
        {
            p[0].pos_size.y = p[1].bomba.bombBody.y - p[1].bomba.bombBody.height;
        }
    }

    if (IsKeyDown(KEY_A))
    {
        p[0].pos_size.x -= p[0].velocidade;

        if (CheckCollisionRecs(p[0].pos_size, m[aux].limits[1].pos_size))
        {
            p[0].pos_size.x = m[aux].limits[1].pos_size.x + m[aux].limits[1].pos_size.width;
        }

        for (int i = 0; i < 36; i++)
        {
            if (CheckCollisionRecs(p[0].pos_size, m[aux].obstacles[i].pos_size))
            {
                p[0].pos_size.x = m[aux].obstacles[i].pos_size.x + m[aux].obstacles[i].pos_size.width;
            }
        }

        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                if (CheckCollisionRecs(p[0].pos_size, m[aux].boxes[i][j].pos_size) && m[aux].boxes[i][j].drawed == 1)
                {
                    p[0].pos_size.x = m[aux].boxes[i][j].pos_size.x + m[aux].boxes[i][j].pos_size.width;
                }
            }
        }

        if (CheckCollisionRecs(p[0].pos_size, p[0].bomba.bombBody) && p[0].pos_size.x > p[0].bomba.bombBody.x)
        {
            p[0].pos_size.x = p[0].bomba.bombBody.x + p[0].bomba.bombBody.width;
        }

        if (CheckCollisionRecs(p[0].pos_size, p[1].bomba.bombBody) && p[0].pos_size.x > p[1].bomba.bombBody.x)
        {
            p[0].pos_size.x = p[1].bomba.bombBody.x + p[1].bomba.bombBody.width;
        }
    }

    if (IsKeyDown(KEY_D))
    {
        p[0].pos_size.x += p[0].velocidade;

        if (CheckCollisionRecs(p[0].pos_size, m[aux].limits[3].pos_size))
        {
            p[0].pos_size.x = m[aux].limits[3].pos_size.x - HERO_BOMB_HEIGHT_WIDTH;
        }

        for (int i = 0; i < 36; i++)
        {
            if (CheckCollisionRecs(p[0].pos_size, m[aux].obstacles[i].pos_size))
            {
                p[0].pos_size.x = m[aux].obstacles[i].pos_size.x - m[aux].obstacles[i].pos_size.width - (HERO_BOMB_HEIGHT_WIDTH - m[aux].obstacles[i].pos_size.width);
            }
        }

        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                if (CheckCollisionRecs(p[0].pos_size, m[aux].boxes[i][j].pos_size) && m[aux].boxes[i][j].drawed == 1)
                {
                    p[0].pos_size.x = m[aux].boxes[i][j].pos_size.x - m[aux].boxes[i][j].pos_size.width - (HERO_BOMB_HEIGHT_WIDTH - m[aux].boxes[i][j].pos_size.width);
                }
            }
        }

        if (CheckCollisionRecs(p[0].pos_size, p[0].bomba.bombBody) && p[0].pos_size.x < p[0].bomba.bombBody.x)
        {
            p[0].pos_size.x = p[0].bomba.bombBody.x - p[0].bomba.bombBody.width;
        }

        if (CheckCollisionRecs(p[0].pos_size, p[1].bomba.bombBody) && p[0].pos_size.x < p[1].bomba.bombBody.x)
        {
            p[0].pos_size.x = p[1].bomba.bombBody.x - p[1].bomba.bombBody.width;
        }
    }

    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            if (CheckCollisionRecs(p[0].pos_size, m[aux].items[i][j].pos_size) && m[aux].items[i][j].auxDraw != 0)
            {
                if (m[aux].items[i][j].auxDraw == 1)
                {
                    p[0].life+=1;
                }
                else if (m[aux].items[i][j].auxDraw == 2)
                {
                    p[0].bomba.raio += 40;
                }
                else if (m[aux].items[i][j].auxDraw == 3)
                {
                    if (p[0].velocidade == 5)
                        p[0].velocidade = 8;
                    if (p[0].velocidade == 4)
                        p[0].velocidade = 5;
                    if (p[0].velocidade == 2)
                        p[0].velocidade = 4;
                }
                m[aux].items[i][j].auxDraw = 0;
                m[aux].items[i][j].pos_size = (Rectangle){0, 0, 0, 0};
            }
        }
    }

    if (IsKeyDown(KEY_SPACE) && p[0].qtdBombas > 0)
    {
        p[0].bomba.tempoInicial = GetTime();
        p[0].dropedBomb++;
        p[0].qtdBombas--;

        p[0].bomba.bombBody.x = p[0].pos_size.x;
        p[0].bomba.bombBody.y = p[0].pos_size.y;
        p[0].bomba.bombBody.height = HERO_BOMB_HEIGHT_WIDTH;
        p[0].bomba.bombBody.width = HERO_BOMB_HEIGHT_WIDTH;

        initExplosion(p, 0);
    }

    // PERSONAGEM 2

    if (IsKeyDown(KEY_UP))
    {
        p[1].pos_size.y -= p[1].velocidade;

        if (CheckCollisionRecs(p[1].pos_size, m[aux].limits[0].pos_size))
        {
            p[1].pos_size.y = m[aux].limits[0].pos_size.y + m[aux].limits[0].pos_size.height;
        }

        for (int i = 0; i < 36; i++)
        {
            if (CheckCollisionRecs(p[1].pos_size, m[aux].obstacles[i].pos_size))
            {
                p[1].pos_size.y = m[aux].obstacles[i].pos_size.y + m[aux].obstacles[i].pos_size.height;
            }
        }

        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                if (CheckCollisionRecs(p[1].pos_size, m[aux].boxes[i][j].pos_size) && m[aux].boxes[i][j].drawed == 1)
                {
                    p[1].pos_size.y = m[aux].boxes[i][j].pos_size.y + m[aux].boxes[i][j].pos_size.height;
                }
            }
        }

        if (CheckCollisionRecs(p[1].pos_size, p[1].bomba.bombBody) && p[1].pos_size.y > p[1].bomba.bombBody.y)
        {
            p[1].pos_size.y = p[1].bomba.bombBody.y + p[1].bomba.bombBody.height;
        }

        if (CheckCollisionRecs(p[1].pos_size, p[0].bomba.bombBody) && p[1].pos_size.y > p[0].bomba.bombBody.y)
        {
            p[1].pos_size.y = p[0].bomba.bombBody.y + p[0].bomba.bombBody.height;
        }
    }

    if (IsKeyDown(KEY_DOWN))
    {
        p[1].pos_size.y += p[1].velocidade;

        if (CheckCollisionRecs(p[1].pos_size, m[aux].limits[2].pos_size))
        {
            p[1].pos_size.y = m[aux].limits[2].pos_size.y - HERO_BOMB_HEIGHT_WIDTH;
        }

        for (int i = 0; i < 36; i++)
        {
            if (CheckCollisionRecs(p[1].pos_size, m[aux].obstacles[i].pos_size))
            {
                p[1].pos_size.y = m[aux].obstacles[i].pos_size.y - HERO_BOMB_HEIGHT_WIDTH;
            }
        }

        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                if (CheckCollisionRecs(p[1].pos_size, m[aux].boxes[i][j].pos_size) && m[aux].boxes[i][j].drawed == 1)
                {
                    p[1].pos_size.y = m[aux].boxes[i][j].pos_size.y - m[aux].boxes[i][j].pos_size.height - (HERO_BOMB_HEIGHT_WIDTH - m[aux].boxes[i][j].pos_size.height);
                }
            }
        }

        if (CheckCollisionRecs(p[1].pos_size, p[1].bomba.bombBody) && p[1].pos_size.y < p[1].bomba.bombBody.y)
        {
            p[1].pos_size.y = p[1].bomba.bombBody.y - p[1].bomba.bombBody.height;
        }

        if (CheckCollisionRecs(p[1].pos_size, p[0].bomba.bombBody) && p[1].pos_size.y < p[0].bomba.bombBody.y)
        {
            p[1].pos_size.y = p[0].bomba.bombBody.y - p[0].bomba.bombBody.height;
        }
    }

    if (IsKeyDown(KEY_LEFT))
    {
        p[1].pos_size.x -= p[1].velocidade;

        if (CheckCollisionRecs(p[1].pos_size, m[aux].limits[1].pos_size))
        {
            p[1].pos_size.x = m[aux].limits[1].pos_size.x + m[aux].limits[1].pos_size.width;
        }

        for (int i = 0; i < 36; i++)
        {
            if (CheckCollisionRecs(p[1].pos_size, m[aux].obstacles[i].pos_size))
            {
                p[1].pos_size.x = m[aux].obstacles[i].pos_size.x + m[aux].obstacles[i].pos_size.width;
            }
        }

        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                if (CheckCollisionRecs(p[1].pos_size, m[aux].boxes[i][j].pos_size) && m[aux].boxes[i][j].drawed == 1)
                {
                    p[1].pos_size.x = m[aux].boxes[i][j].pos_size.x + m[aux].boxes[i][j].pos_size.width;
                }
            }
        }

        if (CheckCollisionRecs(p[1].pos_size, p[1].bomba.bombBody) && p[1].pos_size.x > p[1].bomba.bombBody.x)
        {
            p[1].pos_size.x = p[1].bomba.bombBody.x + p[1].bomba.bombBody.width;
        }

        if (CheckCollisionRecs(p[1].pos_size, p[0].bomba.bombBody) && p[1].pos_size.x > p[0].bomba.bombBody.x)
        {
            p[1].pos_size.x = p[0].bomba.bombBody.x + p[0].bomba.bombBody.width;
        }
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        p[1].pos_size.x += p[1].velocidade;

        if (CheckCollisionRecs(p[1].pos_size, m[aux].limits[3].pos_size))
        {
            p[1].pos_size.x = m[aux].limits[3].pos_size.x - HERO_BOMB_HEIGHT_WIDTH;
        }

        for (int i = 0; i < 36; i++)
        {
            if (CheckCollisionRecs(p[1].pos_size, m[aux].obstacles[i].pos_size))
            {
                p[1].pos_size.x = m[aux].obstacles[i].pos_size.x - m[aux].obstacles[i].pos_size.width - (HERO_BOMB_HEIGHT_WIDTH - m[aux].obstacles[i].pos_size.width);
            }
        }

        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                if (CheckCollisionRecs(p[1].pos_size, m[aux].boxes[i][j].pos_size) && m[aux].boxes[i][j].drawed == 1)
                {
                    p[1].pos_size.x = m[aux].boxes[i][j].pos_size.x - m[aux].boxes[i][j].pos_size.width - (HERO_BOMB_HEIGHT_WIDTH - m[aux].boxes[i][j].pos_size.width);
                }
            }
        }

        if (CheckCollisionRecs(p[1].pos_size, p[1].bomba.bombBody) && p[1].pos_size.x < p[1].bomba.bombBody.x)
        {
            p[1].pos_size.x = p[1].bomba.bombBody.x - p[1].bomba.bombBody.width;
        }

        if (CheckCollisionRecs(p[1].pos_size, p[0].bomba.bombBody) && p[1].pos_size.x < p[0].bomba.bombBody.x)
        {
            p[1].pos_size.x = p[0].bomba.bombBody.x - p[0].bomba.bombBody.width;
        }
    }

    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            if (CheckCollisionRecs(p[1].pos_size, m[aux].items[i][j].pos_size) && m[aux].items[i][j].auxDraw != 0)
            {
                if (m[aux].items[i][j].auxDraw == 1)
                {
                    p[1].life+=1;
                }
                else if (m[aux].items[i][j].auxDraw == 2)
                {
                    p[1].bomba.raio += 40;
                }
                else if (m[aux].items[i][j].auxDraw == 3)
                {
                    if (p[1].velocidade == 5)
                        p[1].velocidade = 8;
                    if (p[1].velocidade == 4)
                        p[1].velocidade = 5;
                    if (p[1].velocidade == 2)
                        p[1].velocidade = 4;
                }
                m[aux].items[i][j].auxDraw = 0;
                m[aux].items[i][j].pos_size = (Rectangle){0, 0, 0, 0};
            }
        }
    }

    if (IsKeyDown(KEY_KP_ENTER) && p[1].qtdBombas > 0)
    {
        p[1].bomba.tempoInicial = GetTime();
        p[1].dropedBomb++;
        p[1].qtdBombas--;

        p[1].bomba.bombBody.x = p[1].pos_size.x;
        p[1].bomba.bombBody.y = p[1].pos_size.y;
        p[1].bomba.bombBody.height = HERO_BOMB_HEIGHT_WIDTH;
        p[1].bomba.bombBody.width = HERO_BOMB_HEIGHT_WIDTH;

        initExplosion(p, 1);
    }
}

void drawGame(Player p[], Mapa *m, Sprites *sprt, int aux)
{
    ClearBackground(DARKGRAY);
    drawLimits(&m[aux]);
    drawObstacles(&m[aux]);
    drawBoxes(&m[aux]);
    drawItems(&m[aux]);

    DrawTexture(p[0].sprite, (int)p[0].pos_size.x, (int)p[0].pos_size.y, WHITE);
    DrawTexture(p[1].sprite, (int)p[1].pos_size.x, (int)p[1].pos_size.y, WHITE);
    for (int i = 0; i < 36; i++)
    {
        DrawTexture(m[aux].obstacles[i].sprite, (int)m[aux].obstacles[i].pos_size.x, (int)m[aux].obstacles[i].pos_size.y, WHITE);
    }

    if (p[0].dropedBomb > 0)
    {
        drawBomb(p, 0, BLACK, *sprt);
        drawExplosion(p, m, 0, aux);
    }

    if (p[1].dropedBomb > 0)
    {
        drawBomb(p, 1, BLACK, *sprt);
        drawExplosion(p, m, 1, aux);
    }
}

void updatePlayerSprite(Player *player, char lastKey, int playerNumber)
{
    if (playerNumber == 1)
    {
        if (lastKey == 'a')
        {
            player->sprite = LoadTexture("sprite/aviaop1_olhando_esq.png");
        }
        else if (lastKey == 'd')
        {
            player->sprite = LoadTexture("sprite/aviaop1_olhando_direit.png");
        }
    }
    else if (playerNumber == 2)
    {
        if (IsKeyDown(KEY_LEFT))
        {
            player->sprite = LoadTexture("sprite/aviaop2_olhando_esq.png");
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            player->sprite = LoadTexture("sprite/aviaop2_olhando_direit.png");
        }
    }
}

void obterNomesDosJogadores(Player *jogadores, const char (*mensagens)[40])
{
    int jogadorAtual = 0;
    int contador = 0;
    int nomeCapturado = 0;

    while (!nomeCapturado && !WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(VIOLET);

        DrawText(mensagens[jogadorAtual], GetScreenWidth() / 2 - MeasureText(mensagens[jogadorAtual], 20) / 2, GetScreenHeight() / 2 - 20, 20, DARKGRAY);

        if (contador == 0)
        {
            DrawText("Digite o nome", GetScreenWidth() / 2 - MeasureText("Digite o nome", 20) / 2, GetScreenHeight() / 2 + 40, 20, DARKGRAY);
        }
        else
        {
            DrawTextEx(GetFontDefault(), jogadores[jogadorAtual].nome, (Vector2){GetScreenWidth() / 2 - MeasureText(jogadores[jogadorAtual].nome, 20) / 2, GetScreenHeight() / 2 + 40}, 20, 1, DARKGRAY);
        }

        EndDrawing();

        int tecla = GetKeyPressed();

        if (tecla != 0)
        {
            if (tecla == KEY_BACKSPACE)
            {
                if (contador > 0)
                {
                    contador--;
                    jogadores[jogadorAtual].nome[contador] = '\0';
                }
            }
            else if ((tecla >= 32) && (tecla <= 126) && (contador < 19))
            {
                jogadores[jogadorAtual].nome[contador] = (char)tecla;
                contador++;
                jogadores[jogadorAtual].nome[contador] = '\0';
            }
            else if (tecla == KEY_ENTER && contador > 0)
            {
                jogadorAtual++;

                if (jogadorAtual == 2)
                {
                    nomeCapturado = 1;
                }

                contador = 0;
            }
            else if (tecla == KEY_ESCAPE)
            {
                CloseWindow();
                return;
            }
        }
    }

    BeginDrawing();
    ClearBackground(VIOLET);
    EndDrawing();
}

void togglePause()
{
    jogoPausado = !jogoPausado;
}

int main(void)
{
    InitWindow(800, 600, "Jogo");
    SetTargetFPS(60);

    int jogoIniciado = 0;
    int jogoPausado = 0;
    MenuItem selecionado = MENU_INICIAR_JOGO;

    Mapa map[2];
    initMap(map, 0);
    initMap(map, 1);

    Player p[2];
    initPlayer(p);

    Sprites sprt;
    sprt.bombSprite = LoadTexture("sprite/bomb.png");

    const int numJogadores = 2;
    Player jogadores[numJogadores];
    int nomesJogadoresCapturados = 0;

    Texture2D background = LoadTexture("sprite/menu.png");
    Texture2D mapBackground = LoadTexture("sprite/sunset.png");

    char lastKey = '\0';

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(background, 0, 0, WHITE);

        if (jogoIniciado == 0 && !nomesJogadoresCapturados)
        {
            DrawRectangle(GetScreenWidth() / 2 - 120, 180, 240, 40, LIGHTGRAY);
            DrawRectangle(GetScreenWidth() / 2 - 120, 240, 240, 40, LIGHTGRAY);
            DrawRectangle(GetScreenWidth() / 2 - 120, 300, 240, 40, LIGHTGRAY);

            DrawText("Menu", GetScreenWidth() / 2 - 40, 80, 30, RAYWHITE);

            DrawTextEx(GetFontDefault(), "Iniciar Jogo", (Vector2){GetScreenWidth() / 2 - 100, 190}, 20, 1, (selecionado == MENU_INICIAR_JOGO) ? RAYWHITE : GRAY);
            DrawTextEx(GetFontDefault(), "Opções", (Vector2){GetScreenWidth() / 2 - 100, 250}, 20, 1, (selecionado == MENU_OPCOES) ? RAYWHITE : GRAY);
            DrawTextEx(GetFontDefault(), "Sair", (Vector2){GetScreenWidth() / 2 - 100, 310}, 20, 1, (selecionado == MENU_SAIR) ? RAYWHITE : GRAY);

            if (IsKeyPressed(KEY_ENTER))
            {
                switch (selecionado)
                {
                case MENU_INICIAR_JOGO:;
                    char mensagens[2][40];
                    for (int i = 0; i < 2; i++)
                    {
                        sprintf(mensagens[i], "Jogador %d:", i + 1);
                    }
                    obterNomesDosJogadores(jogadores, mensagens);
                    nomesJogadoresCapturados = 1;

                    for (int i = 0; i < numJogadores; i++)
                    {
                        printf("Nome do Jogador %d: %s\n", i + 1, jogadores[i].nome);
                    }
                    jogoIniciado = 1;
                    break;
                case MENU_OPCOES:
                    // Alguma coisa?
                    break;
                case MENU_SAIR:
                    CloseWindow();
                    break;
                }
            }
        }

        if (!jogoPausado && jogoIniciado && p[0].life != 0 && p[1].life != 0)
        {
            DrawTexture(mapBackground, 0, 0, WHITE);

            updatePlayerSprite(&p[0], lastKey, 1);
            updatePlayerSprite(&p[1], lastKey, 2);
            updateGame(p, &map, 1);
            drawGame(p, &map, &sprt, 1);
        }

        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D))
        {
            if (!jogoPausado)
            {
                lastKey = (IsKeyDown(KEY_A)) ? 'a' : 'd';
            }
        }
        else
        {
            lastKey = '\0';
        }

        if (IsKeyPressed(KEY_P))
        {
            jogoPausado = !jogoPausado;
        }

        EndDrawing();
    }

    UnloadTexture(background);
    UnloadTexture(p[0].sprite);
    UnloadTexture(p[1].sprite);
    UnloadTexture(sprt.bombSprite);

    for (int i = 0; i < 36; i++)
    {
        UnloadTexture(map->obstacles[i].sprite);
    }

    CloseWindow();

    return 0;
}