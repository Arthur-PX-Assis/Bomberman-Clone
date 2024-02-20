#include "init.h"

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
