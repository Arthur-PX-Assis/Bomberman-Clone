#include "game.h"

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