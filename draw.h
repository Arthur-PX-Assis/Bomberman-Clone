#ifndef DRAW_H
#define DRAW_H

#include "game.h"

void drawLimits(Mapa *m);
void drawBoxes(Mapa *m);
void drawItems(Mapa *m);
void drawObstacles(Mapa *m);
void drawBomb(Player p[], int aux, Color cor, Sprites sprt);
void drawExplosion(Player p[], Mapa *m, int aux, int auxMap);

#endif // !DRAW_H