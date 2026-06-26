#ifndef HUD_H
#define HUD_H

#include <allegro5/allegro.h>
#include "personagem.h"

#define CORACAO_X     40
#define CORACAO_Y     40
#define CORACAO_ESPACO 70

typedef struct {
    ALLEGRO_BITMAP *vida;
    ALLEGRO_BITMAP *vida_extra;
} hud;

void inicializa_hud(hud *h);
void desenha_hud(hud *h, personagem *p);
void destroi_hud(hud *h);

#endif