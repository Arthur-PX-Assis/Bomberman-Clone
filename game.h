#ifndef GAME_H
#define GAME_H

#include "structs.h"
#include "draw.h"
#include "init.h"

void updateGame(Player p[], Mapa *m, int aux);
void drawGame(Player p[], Mapa *m, Sprites *sprt, int aux);
void updatePlayerSprite(Player *player, char lastKey, int playerNumber);
void obterNomesDosJogadores(Player *jogadores, const char (*mensagens)[40]);

#endif // !GAME_H