#include "draw.h"

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
