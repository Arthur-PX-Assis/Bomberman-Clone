#include "game.h"

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